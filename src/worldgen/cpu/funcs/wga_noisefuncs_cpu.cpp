#include "wga_noisefuncs_cpu.h"

#include <cmath>

#include <FastNoise/FastNoise.h>

#include "util/tracyutils.h"

// So that things aren't screwed up when transitioning from negative to positive numbers
static constexpr auto ofst = std::numeric_limits<int32_t>::max();

void WGA_NoiseFuncs_CPU::valueNoisePC(WGA_Funcs_CPU::Api api, Key key, DH <VT::Float> result, V <VT::Float> octaveSizev, V <VT::Float> seedv, V <VT::Float> value) {
	const uint32_t octaveSize = static_cast<uint32_t>(octaveSizev.constValue());
	const Seed seed = api->seed() ^ static_cast<Seed>(seedv.constValue());

	const Vector2U32 chunkPos = adjustOrigin(key.origin, seed).chunkPosition().to<uint32_t>() + ofst;
	const Vector2U32 nodeOrigin = chunkPos / octaveSize;
	const Vector2F originProgress = (chunkPos % octaveSize).to<float>() / octaveSize;
	const Vector2F originProgressInv = Vector2F(1) - originProgress;

	float nodes[4];
	for(uint32_t i = 0; i < 4; i++)
		nodes[i] = value.chunkValue(((nodeOrigin + Vector2U32(i % 2, i / 2)) * octaveSize - ofst).to<ChunkWorldPos_T>());

	result[0] =
		(
			(nodes[0] * originProgressInv.x() + nodes[1] * originProgress.x()) * originProgressInv.y()
			+ (nodes[2] * originProgressInv.x() + nodes[3] * originProgress.x()) * originProgress.y()
		);
}

void WGA_NoiseFuncs_CPU::valueNoise2D(WGA_Funcs_CPU::Api api, Key key, DH <VT::Float> result, V <VT::Float> octaveSizev, V <VT::Float> seedv, V <VT::Float> value) {
	const uint32_t octaveSize = static_cast<uint32_t>(octaveSizev.constValue());
	const Seed seed = api->seed() ^ static_cast<Seed>(seedv.constValue());

	const Vector2U32 chunkPos = adjustOrigin(key.origin, seed).chunkPosition().to<uint32_t>() + ofst;
	const Vector2U32 nodeOrigin = chunkPos / octaveSize;
	const Vector2F originProgress = (chunkPos % octaveSize).to<float>() / octaveSize;
	const float progressCoef = 1.0f / (octaveSize * chunkSize);

	float nodes[4];
	for(uint32_t i = 0; i < 4; i++)
		nodes[i] = value.chunkValue(((nodeOrigin + Vector2U32(i % 2, i / 2)) * octaveSize - ofst).to<ChunkWorldPos_T>());

	for(int i = 0; i < chunkSurface; i++) {
		const Vector2F prog = originProgress + Vector2F(i % chunkSize, i / chunkSize) * progressCoef;
		const Vector2F progInv = Vector2F(1) - prog;

		result[i] =
			(
				(nodes[0] * progInv.x() + nodes[1] * prog.x()) * progInv.y()
				+ (nodes[2] * progInv.x() + nodes[3] * prog.x()) * prog.y()
			);
	}
}

void WGA_NoiseFuncs_CPU::perlin2D(WGA_Funcs_CPU::Api api, Key key, DH <VT::Float> result, V <VT::Float> octaveSizev, V <VT::Float> seedv) {
	const uint32_t octaveSize = static_cast<uint32_t>(octaveSizev.constValue());
	const Seed seed = WorldGen_CPU_Utils::hash(static_cast<Seed>(seedv.constValue()), api->seed());

	const Vector2U32 chunkPos = adjustOrigin(key.origin, seed).chunkPosition().to<uint32_t>() + ofst;
	const Vector2U32 nodeOrigin = chunkPos / octaveSize;
	const Vector2F originProgress = (chunkPos % octaveSize).to<float>() / octaveSize;
	const float progressCoef = 1.0f / (octaveSize * chunkSize);

	Vector2F gradients[4];
	for(uint32_t g = 0; g < 4; g++) {
		const Vector2U32 nodePos = nodeOrigin + Vector2U32(g % 2, g / 2);
		const uint32_t angleBase = WorldGen_CPU_Utils::hash(nodePos.to<uint32_t>(), seed);
		const float angle = static_cast<float>(angleBase & 0xffff) / 65535 * M_PI * 2;

		gradients[g] = Vector2F(sin(angle), cos(-angle));
	}

	float dotData[4][2][chunkSize];
	for(int g = 0; g < 4; g++) {
		for(int dim = 0; dim < 2; dim++) {
			const float grad = gradients[g][dim];
			const float nodePos = (g >> dim) & 1;

			const float c1 = (originProgress[dim] - nodePos) * grad;
			const float c2 = progressCoef * grad;

			for(int i = 0; i < chunkSize; i++)
				dotData[g][dim][i] = c1 + i * c2;
		}
	}

	const auto ipol = [](float v) {
		const float v2 = v * v;
		const float v4 = v2 * v2;

		return 6 * v4 * v - 15 * v4 + 10 * v2 * v;
	};

	float xCoefs[chunkSize];
	for(int x = 0; x < chunkSize; x++)
		xCoefs[x] = ipol(originProgress.x() + x * progressCoef);

	for(int y = 0; y < chunkSize; y++) {
		const float yCoef = ipol(originProgress.y() + y * progressCoef);
		const float yInvCoef = 1 - yCoef;

		for(int x = 0; x < chunkSize; x++) {
			const int i = y * chunkSize + x;

			float coefs[4];
			for(int ci = 0; ci < 4; ci++)
				coefs[ci] = dotData[ci][0][x] + dotData[ci][1][y];

			const float xCoef = xCoefs[x];
			const float xInvCoef = 1 - xCoef;

			result[i] =
				(
					(coefs[0] * xInvCoef + coefs[1] * xCoef) * yInvCoef
					+ (coefs[2] * xInvCoef + coefs[3] * xCoef) * yCoef
				);
		}
	}
}

void WGA_NoiseFuncs_CPU::perlin3D(WGA_Funcs_CPU::Api api, WGA_Funcs_CPU::Key key, DH <WGA_Value::ValueType::Float> result, V <WGA_Value::ValueType::Float> octaveSizev, V <WGA_Value::ValueType::Float> seedv) {
	const uint32_t octaveSize = static_cast<uint32_t>(octaveSizev.constValue());
	const Seed seed = WorldGen_CPU_Utils::hash(static_cast<Seed>(seedv.constValue()), api->seed());

	const Vector3U32 chunkPos = (adjustOrigin(key.origin, seed) / chunkSize).to<uint32_t>() + ofst;
	const Vector3U32 nodeOrigin = chunkPos / octaveSize;
	const Vector3F originProgress = (chunkPos % octaveSize).to<float>() / octaveSize;
	const float progressCoef = 1.0f / (octaveSize * chunkSize);

	static const std::vector<V3F> graidentVariants = [] {
		std::vector<V3F> r;

		// 12
		for(int zeroD = 0; zeroD < 3; zeroD++) {
			for(int sigs = 0; sigs < 4; sigs++) {
				V3F vec;
				vec[zeroD] = (sigs & 1) ? 1 : -1;
				vec[(zeroD + 1) % 3] = (sigs & 2) ? 1 : -1;

				r.push_back(vec);
			}
		}
		return r;
	}();

	Vector3F gradients[8];
	for(uint32_t g = 0; g < 8; g++) {
		const Vector3U32 nodePos = nodeOrigin + Vector3U32(g & 1, (g >> 1) & 1, (g >> 2) & 1);
		const uint32_t rand = WorldGen_CPU_Utils::hash(nodePos.to<uint32_t>(), seed);
		gradients[g] = graidentVariants[rand % 12];
	}

	float dotData[8][3][chunkSize];
	for(int g = 0; g < 8; g++) {
		for(int dim = 0; dim < 3; dim++) {
			const float grad = gradients[g][dim];
			const float nodePos = (g >> dim) & 1;

			const float c1 = (originProgress[dim] - nodePos) * grad;
			const float c2 = progressCoef * grad;

			for(int i = 0; i < chunkSize; i++)
				dotData[g][dim][i] = c1 + i * c2;
		}
	}

	const auto ipol = [](float v) {
		const float v2 = v * v;
		const float v4 = v2 * v2;

		return 6 * v4 * v - 15 * v4 + 10 * v2 * v;
	};

	float dCoefs[3][chunkSize];
	for(int d = 0; d < 3; d++) {
		for(int i = 0; i < chunkSize; i++)
			dCoefs[d][i] = ipol(originProgress[d] + i * progressCoef);
	}

	int i = 0;
	for(int z = 0; z < chunkSize; z++) {
		const float zCoef = dCoefs[2][z];
		const float zInvCoef = 1 - zCoef;

		for(int y = 0; y < chunkSize; y++) {
			const float yCoef = dCoefs[1][y];
			const float yInvCoef = 1 - yCoef;

			for(int x = 0; x < chunkSize; x++, i++) {
				float coefs[8];
				for(int ci = 0; ci < 8; ci++)
					coefs[ci] = dotData[ci][0][x] + dotData[ci][1][y] + dotData[ci][2][z];

				const float xCoef = dCoefs[0][x];
				const float xInvCoef = 1 - xCoef;

				result[i] =
					(
						(coefs[0] * xInvCoef + coefs[1] * xCoef) * yInvCoef
						+ (coefs[2] * xInvCoef + coefs[3] * xCoef) * yCoef
					) * zInvCoef
					+ (
						  (coefs[4] * xInvCoef + coefs[5] * xCoef) * yInvCoef
						  + (coefs[6] * xInvCoef + coefs[7] * xCoef) * yCoef
					  ) * zCoef;
			}
		}
	}
}

void WGA_NoiseFuncs_CPU::voronoi2D(WGA_Funcs_CPU::Api api, Key key, DH <VT::Float> result, V <VT::Float> octaveSizev, V <VT::Float> seedv, V <VT::Float> resultTypev, V <VT::Float> metricExponentv) {
	return voronoi2DColored(api, key, result, octaveSizev, seedv, resultTypev, metricExponentv, static_cast<WGA_Value_CPU *>(nullptr));
}

void WGA_NoiseFuncs_CPU::voronoi2DColored(WGA_Funcs_CPU::Api api, Key key, DH <VT::Float> result, V <VT::Float> octaveSizev, V <VT::Float> seedv, V <VT::Float> resultTypev, V <VT::Float> metricExponentv, V <VT::Float> coloring) {
	const uint32_t octaveSize = static_cast<uint32_t>(octaveSizev.constValue());
	const Seed seed = WorldGen_CPU_Utils::hash(static_cast<Seed>(seedv.constValue()), api->seed());
	const int resultType = static_cast<int>(resultTypev.constValue());
	const DH <VT::Float> metricExponentHandle = metricExponentv.dataHandle(key.origin, 0);

	const Vector2U32 chunkPos = key.origin.chunkPosition().to<uint32_t>() + ofst;
	const Vector2U32 nodeOrigin = chunkPos / octaveSize;
	const Vector2F originProgress = (chunkPos % octaveSize).to<float>() / octaveSize;
	const float progressCoef = 1.0f / (chunkSize * octaveSize);

	constexpr int maxCnt = 25;
	Vector2F voronoiPoints[maxCnt];
	float voronoiColorings[maxCnt];
	for(int i = 0; i < maxCnt; i++) {
		const Vector2I offset = Vector2I(i % 5, i / 5) - 2;
		const Vector2U32 nodePos = nodeOrigin + offset.to<uint32_t>();
		const Seed localSeed = WorldGen_CPU_Utils::hash(nodePos, seed);
		voronoiPoints[i] = offset.to<float>() + Vector2F(localSeed & 0xffff, (localSeed >> 16) & 0xffff) / 0xffff;
		voronoiColorings[i] = coloring.v ? coloring.chunkValue((nodePos * octaveSize + ofst).to<ChunkWorldPos_T>()) : Vector<float, 1>(0);
	}

	int i = 0;
	for(int y = 0; y < chunkSize; y++) {
		for(int x = 0; x < chunkSize; x++, i++) {
			const Vector2F pos = originProgress + Vector2F(x, y) * progressCoef;
			const float metricExponent = metricExponentHandle[i];
			const float metricExponentInv = 1.0f / metricExponent;

			float distances[maxCnt];
			float dst[3] = {2, 2, 2};
			int ix[3] = {-1, -1, -1};

			for(int j = 0; j < maxCnt; j++) {
				const Vector2F diff = (pos - voronoiPoints[j]).abs();
				float &distance = distances[j];
				distance = pow(pow(diff.x(), metricExponent) + pow(diff.y(), metricExponent), metricExponentInv);

				if(distance < dst[0]) {
					dst[2] = dst[1];
					dst[1] = dst[0];
					dst[0] = distance;

					ix[2] = ix[1];
					ix[1] = ix[0];
					ix[0] = j;
				}
				else if(distance < dst[1]) {
					dst[2] = dst[1];
					dst[1] = distance;

					ix[2] = ix[1];
					ix[1] = j;
				}
				else if(distance < dst[2]) {
					dst[2] = distance;

					ix[2] = j;
				}
			}

			const float c[3] = {
				voronoiColorings[ix[0]], voronoiColorings[ix[1]], voronoiColorings[ix[2]]
			};

			switch(resultType) {

				case 0:
					result[i] = dst[1] - dst[0];
					break;

				case 1:
					result[i] = dst[0];
					break;

				case 2:
					result[i] = dst[0] / dst[1];
					break;

				case 10: {
					// Weighted distance from center

					float weightedSum = 0;
					float weightsSum = 0;
					for(int j = 0; j < maxCnt; j++) {
						const float weight = std::max<float>(0, 1.42f - distances[j]);
						weightedSum += voronoiColorings[j] * weight;
						weightsSum += weight;
					}
					result[i] = weightedSum / weightsSum;
					break;
				}

				case 11:
					result[i] = c[0];
					break;

				case 12: {
					// Weighted distance to border
					const float borderDistance = dst[0] / dst[1];

					float weightedSum = 0;
					float weightsSum = 0;
					for(int j = 0; j < maxCnt; j++) {
						const float weight = std::max<float>(0, 1.42f - distances[j]);
						weightedSum += voronoiColorings[j] * borderDistance * weight;
						weightsSum += weight;
					}
					result[i] = weightedSum / weightsSum;
					break;
				}

				default:
					result[i] = 0;
					break;

			}
		}
	}
}

void
WGA_NoiseFuncs_CPU::voronoi3D(WGA_Funcs_CPU::Api api, WGA_Funcs_CPU::Key key, DH <WGA_Value::ValueType::Float> result, V <WGA_Value::ValueType::Float> octaveSize, V <WGA_Value::ValueType::Float> seed, V <WGA_Value::ValueType::Float> resultType, V <WGA_Value::ValueType::Float> metricExponent) {
	return voronoi3DParam(api, key, result, octaveSize, seed, resultType, metricExponent, static_cast<WGA_Value_CPU *>(nullptr));
}

void WGA_NoiseFuncs_CPU::voronoi3DParam(WGA_Funcs_CPU::Api api, WGA_Funcs_CPU::Key key, DH <WGA_Value::ValueType::Float> result, V <WGA_Value::ValueType::Float> octaveSizev, V <WGA_Value::ValueType::Float> seedv, V <WGA_Value::ValueType::Float> resultTypev, V <WGA_Value::ValueType::Float> metricExponentv, V <WGA_Value::ValueType::Float> paramv) {  /// WIP, SLOW, NOT WORKING
	const uint32_t octaveSize = static_cast<uint32_t>(octaveSizev.constValue()) * chunkSize;
	const Seed seed = WorldGen_CPU_Utils::hash(static_cast<Seed>(seedv.constValue()), api->seed());
	const int resultType = static_cast<int>(resultTypev.constValue());
	const DH <VT::Float> metricExponentHandle = metricExponentv.dataHandle(key.origin, 0);

	const Vector3U32 basePos = key.origin.to<uint32_t>() + ofst;
	const Vector3U32 nodeOrigin = basePos / octaveSize;
	const Vector3F originProgress = (basePos % octaveSize).to<float>() / octaveSize;
	const float progressCoef = 1.0f / (chunkSize * octaveSize);

	constexpr int maxCnt = 5 * 5 * 5;
	V3F voronoiPoints[maxCnt];
	float voronoiParams[maxCnt];
	for(int i = 0; i < maxCnt; i++) {
		const Vector3I offset = Vector3I(i % 25, (i / 5) % 5, i / 25) - 2;
		const Vector3U32 nodePos = nodeOrigin + offset.to<uint32_t>();
		const Seed localSeed = WorldGen_CPU_Utils::hash(nodePos, seed);
		voronoiPoints[i] =
			offset.to<float>() + V3F(localSeed & 0xff, (localSeed >> 8) & 0xff, (localSeed >> 16) & 0xff) / 0xff;
		voronoiParams[i] = paramv.v ? paramv.sampleAt((nodePos * octaveSize - ofst).to<BlockWorldPos_T>())
		                            : Vector<float, 1>(0);
	}

	int i = 0;
	for(int z = 0; z < chunkSize; z++) {
		for(int y = 0; y < chunkSize; y++) {
			for(int x = 0; x < chunkSize; x++, i++) {
				const V3F pos = originProgress + V3F(x, y, z) * progressCoef;
				const float metricExponent = metricExponentHandle[i];
				const float metricExponentInv = 1.0f / metricExponent;

				float distances[maxCnt];
				float dst[3] = {9, 9, 9};
				int ix[3] = {-1, -1, -1};

				for(int j = 0; j < maxCnt; j++) {
					const V3F diff = (pos - voronoiPoints[j]).abs();
					float &distance = distances[j];
					distance = pow(pow(diff.x(), metricExponent) + pow(diff.y(), metricExponent) + pow(diff.z(), metricExponent),
					               metricExponentInv);

					if(distance < dst[0]) {
						dst[2] = dst[1];
						dst[1] = dst[0];
						dst[0] = distance;

						ix[2] = ix[1];
						ix[1] = ix[0];
						ix[0] = j;
					}
					else if(distance < dst[1]) {
						dst[2] = dst[1];
						dst[1] = distance;

						ix[2] = ix[1];
						ix[1] = j;
					}
					else if(distance < dst[2]) {
						dst[2] = distance;

						ix[2] = j;
					}
				}

				const float p[3] = {
					voronoiParams[ix[0]], voronoiParams[ix[1]], voronoiParams[ix[2]]
				};

				switch(resultType) {

					case 0:
						result[i] = dst[1] - dst[0];
						break;

					case 1:
						result[i] = dst[0];
						break;

					case 2:
						result[i] = dst[0] / dst[1];
						break;

					case 10: {
						result[i] = p[0];
						break;
					}

					case 11: {
						const float prog = dst[1] / (dst[0] + dst[1]);
						result[i] = p[1] * prog + p[0] * (1 - prog);
						break;
					}

					default:
						result[i] = 0;
						break;

				}
			}
		}
	}
}

void WGA_NoiseFuncs_CPU::poissonDisc2DBool(WGA_Funcs_CPU::Api api, WGA_Funcs_CPU::Key key, DH <WGA_Value::ValueType::Bool> result, V <WGA_Value::ValueType::Float> seedv, V <WGA_Value::ValueType::Float> radius) {
	const Seed baseSeed = WorldGen_CPU_Utils::hash(static_cast<Seed>(seedv.constValue()), api->seed());

	struct Node {
		Vector2F pos;
		float radius;
	};

	struct Rec {
		std::vector<Node> nodes;
	};

	using RecPtr = WGA_DataRecordT_CPU<Rec>::Ptr;

	/*
	 * Imagine the sub chunk 3x3 grid:
	 *
	 * 1 | 2 | 1
	 * ---------
	 * 2 | 3 | 2
	 * ---------
	 * 1 | 2 | 1
	 *
	 * For keeping the radius working even across subchunk boundaries:
	 * * We first generate the record 3 standalone,
	 * * Then we load 2s that respect distances from nodes from 3
	 * * Then we load 1s that respect distances from both 3s and 2s
	 * */

	const std::function< WGA_DataRecord_CPU::Ptr(Key key)> recCtor = [&api, &radius, &recCtor, baseSeed](Key key) {
		const auto getRecord = [&](int x, int y) {
			auto rec = api->getDataRecord(WGA_DataRecord_CPU::Key{key.symbol, key.origin + BlockWorldPos(x * chunkSize, y * chunkSize, 0), 1}, recCtor);
			return std::static_pointer_cast<WGA_DataRecordT_CPU<Rec>>(rec);
		};


		std::vector<RecPtr> conditionRecs;

		const Vector2<bool> isOdd = ((key.origin.xy().to<uint32_t>() / static_cast<uint32_t>(chunkSize)) % 2).componentEqual(1);

		// 3 - load from diagonal too
		if(isOdd.x() && isOdd.y()) {
			conditionRecs.push_back(getRecord(1, 1));
			conditionRecs.push_back(getRecord(-1, 1));
			conditionRecs.push_back(getRecord(1, -1));
			conditionRecs.push_back(getRecord(-1, -1));
		}

		// Odd Y - load from top and bottom neighbours
		if(isOdd.y()) {
			conditionRecs.push_back(getRecord(0, 1));
			conditionRecs.push_back(getRecord(0, -1));
		}

		// Odd X - load from left and right neighbours
		if(isOdd.x()) {
			conditionRecs.push_back(getRecord(1, 0));
			conditionRecs.push_back(getRecord(-1, 0));
		}

		RecPtr recPtr(new WGA_DataRecordT_CPU<Rec>());
		Rec &rec = recPtr->data;

		conditionRecs.push_back(recPtr);

		const Vector2F originF = key.origin.xy().to<float>();
		Seed seed = WorldGen_CPU_Utils::hash(key.origin.to<uint32_t>(), baseSeed);

		// Flat 512 attempts
		for(int i = 0; i < 512; i++) {
			Node node;
			node.pos = originF;
			seed = WorldGen_CPU_Utils::scramble(seed);
			node.pos.x() += static_cast<float>(seed % 2048) / 2048 * chunkSize;
			seed = WorldGen_CPU_Utils::scramble(seed);
			node.pos.y() += static_cast<float>(seed % 2048) / 2048 * chunkSize;

			const BlockWorldPos blockPos(node.pos.x(), node.pos.y(), key.origin.z());
			node.radius = std::max<float>(1.0f, std::min<float>(radius.sampleAt(blockPos), chunkSize));

			bool collision = false;
			for(const RecPtr &cRec: conditionRecs) {
				for(const Node &other: cRec->data.nodes) {
					const Vector2F diff = node.pos - other.pos;
					const float radiusSum = node.radius + other.radius;

					if(diff.dotProduct(diff) <= radiusSum * radiusSum) {
						collision = true;
						break;
					}
				}

				if(collision)
					break;
			}

			if(collision)
				continue;

			rec.nodes.push_back(node);
		}

		return std::static_pointer_cast<WGA_DataRecord_CPU>(recPtr);
	};

	const RecPtr rec = std::static_pointer_cast<WGA_DataRecordT_CPU<Rec>>(api->getDataRecord(WGA_DataRecord_CPU::Key{key.symbol, key.origin, 1}, recCtor));

	for(int i = 0; i < result.size; i++)
		result[i] = false;

	const Vector2F originF = key.origin.xy().to<float>();
	for(const Node &node: rec->data.nodes)
		result[(node.pos - originF).to<BlockWorldPos_T>()] = true;
}

void WGA_NoiseFuncs_CPU::osimplex2D(WGA_Funcs_CPU::Api api, Key key, DH <VT::Float> result, V <VT::Float> octaveSizev, V <VT::Float> seedv) {
	static const auto node = FastNoise::New<FastNoise::Simplex>();

	const float octaveSize = octaveSizev.constValue();
	const int seed = api->seed() ^ static_cast<int>(seedv.constValue());

	node->GenUniformGrid2D(reinterpret_cast<float *>(result.data), key.origin.x(), key.origin.y(), chunkSize, chunkSize, 1.0f / (octaveSize * chunkSize), seed);
}

void WGA_NoiseFuncs_CPU::osimplex3D(WGA_Funcs_CPU::Api api, Key key, DH <VT::Float> result, V <VT::Float> octaveSizev, V <VT::Float> seedv) {
	static const auto node = FastNoise::New<FastNoise::Simplex>();

	const float octaveSize = octaveSizev.constValue();
	const int seed = api->seed() ^ static_cast<int>(seedv.constValue());

	node->GenUniformGrid3D(reinterpret_cast<float *>(result.data), key.origin.x(), key.origin.y(), key.origin.z(), chunkSize, chunkSize, chunkSize, 1.0f / (octaveSize * chunkSize), seed);
}

void WGA_NoiseFuncs_CPU::rand(WGA_Funcs_CPU::Api api, WGA_Funcs_CPU::Key key, DH <WGA_Value::ValueType::Float> result, V <WGA_Value::ValueType::Float> seedv) {
	const Seed localSeed = WorldGen_CPU_Utils::hashMulti(api->seed(), static_cast<Seed>(seedv.constValue()), key.origin.to<uint32_t>());

	for(int i = 0; i < result.size; i++)
		result[i] = static_cast<float>(WorldGen_CPU_Utils::hash(i, localSeed) & 65535) / 65535.0f;
}

BlockWorldPos WGA_NoiseFuncs_CPU::adjustOrigin(const BlockWorldPos &o, WGA_Funcs_CPU::Seed seed) {
	return o + BlockWorldPos((seed & 65535) * chunkSize, ((seed >> 16) & 65535) * chunkSize, 0);
}
