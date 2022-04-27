#pragma once

#include <functional>
#include <set>
#include <vector>
#include <map>
#include <unordered_map>
#include <unordered_set>

#include "supp/wga_value.h"
#include "supp/wga_biome.h"
#include "supp/wga_grammarsymbol.h"
#include "supp/wga_rule.h"
#include "supp/wga_ruleexpansion.h"
#include "supp/wga_component.h"

// FUNC(functionName, argumentCount, arguments, returnType, returnDimensionality, implementation, description)
// arguments -> (arg1, arg2, arg3, ...)
// argument -> (T, name, Type) | (T_2, name, Type1, Type2) -> argument of type T1 or T2 | (ARG, name, sourceI) -> argument of type of argument sourceI
// returnType -> (T, name, Type) | (ARG, name, sourceArg) -> return value same as of arg sourceArg
// The description is in markdown format

#define WORLDGEN_FUNCTIONS \
  SECTION("Utility functions") \
  FUNC(worldPos, 0, (), (T, pos, Float3), DIM_C(3D), (INLINE, data.worldPos(key.origin, i).to<float>()), "Returns world position of the currently calculated block.") \
  FUNC(select, 3, ((T, cond, Bool), (ANY, thn), (ARG, els, 2)), (ARG, result, 2), DIM_MAX_ARGS_3, (EXT, Utility), "If `cond` is `true`, returns `thn`, else returns `els`.") \
  \
  SECTION("Vector functions") \
  FUNC(float2, 2, ((T, x, Float), (T, y, Float)), (T, r, Float2), DIM_MAX_ARGS_2, (INLINE, Vector2F(arg1, arg2)), "Constructs a 2-dimensional vector.") \
  FUNC(float2, 1, ((T, v, Float)), (T, r, Float2), DIM_MAX_ARGS_1, (INLINE, Vector2F(arg1)), "Constructs a 2-dimensional vector.") \
  FUNC(float3, 3, ((T, x, Float), (T, y, Float), (T, z, Float)), (T, r, Float3), DIM_MAX_ARGS_3, (INLINE, Vector3F(arg1, arg2, arg3)), "Constructs a 3-dimensional vector.") \
  FUNC(float3, 2, ((T, xy, Float2), (T, z, Float)), (T, r, Float3), DIM_MAX_ARGS_2, (INLINE, Vector3F(arg1, arg2)), "Constructs a 3-dimensional vector.") \
  FUNC(float3, 1, ((T, v, Float)), (T, r, Float3), DIM_MAX_ARGS_1, (INLINE, Vector3F(arg1)), "Constructs a 3-dimensional vector.") \
  \
  FUNC(x, 1, ((NUM_VEC, vec)), (T, x, Float), DIM_MAX_ARGS_1, (INLINE, arg1.x()), "Returns the `x` component of a vector.") \
  FUNC(y, 1, ((NUM_VEC, vec)), (T, y, Float), DIM_MAX_ARGS_1, (INLINE, arg1.y()), "Returns the `y` component of a vector.") \
  FUNC(z, 1, ((T, vec, Float3)), (T, x, Float), DIM_MAX_ARGS_1, (INLINE, arg1.z()), "Returns the `z` component of a vector.") \
  FUNC(xy, 1, ((T, vec, Float3)), (T, xy, Float2), DIM_MAX_ARGS_1, (INLINE, arg1.xy()), "Returns the `x` and `y` components of a vector.") \
  \
  FUNC(normalize, 1, ((NUM_VEC, v)), (ARG, r, 1), DIM_MAX_ARGS_1, (INLINE, arg1.normalized()), "Returns the vector normalized.") \
  FUNC(length, 1, ((NUM_VEC, v)), (T, len, Float), DIM_MAX_ARGS_1, (INLINE, arg1.length()), "Returns euclidean length of a vector.") \
  FUNC(lengthExp, 2, ((NUM_VEC, v), (T, exp, Float)), (T, len, Float), DIM_MAX_ARGS_2, (EXT, Utility), "Returns length of a vector with the dimensional exponent being `exp` (1 = manhattan, 2 = euclidean).") \
  FUNC(manhattanLength, 1, ((NUM_VEC, v)), (T, dist, Float), DIM_MAX_ARGS_1, (INLINE, arg1.manhattanLength()), "Returns manhattan length of a vector.") \
  \
  FUNC(distance, 2, ((NUM_VEC, vec1), (ARG, vec2, 1)), (T, dist, Float), DIM_MAX_ARGS_2, (INLINE, (arg1 - arg2).length()), "Returns euclidean distance between two vectors.") \
  FUNC(manhattanDistance, 2, ((NUM_VEC, vec1), (ARG, vec2, 1)), (T, dist, Float), DIM_MAX_ARGS_2, (INLINE, (arg1 - arg2).manhattanLength()), "Returns manhattan distance between two vectors.") \
  \
  FUNC(distanceTo, 1, ((T, targetWorldPos, Float3)), (T, dist, Float), DIM_C(3D), (INLINE, (data.worldPos(key.origin, i).to<float>() - arg1).length()), "Returns distance from the current block to `targetWorldPos` (in world coordinates).") \
  FUNC(distanceTo, 1, ((T, targetWorldPos, Float2)), (T, dist, Float), DIM_C(2D), (INLINE, (data.worldPosXY(key.origin, i).to<float>() - arg1).length()), "Returns distance from the current block to `targetWorldPos` (in world coordinates).") \
  \
  FUNC(distanceTo2D, 1, ((T, targetWorldPos, Float3)), (T, dist, Float), DIM_C(2D), (INLINE, (data.worldPosXY(key.origin, i).to<float>() - arg1.xy()).length()), "Returns distance from the current block to `targetWorldPos` (in world coordinates). Only considers X and Y coordinates.") \
  \
  FUNC(distanceToLine, 3, ((T, p, Float3), (T, a, Float3), (T, b, Float3)), (T, dist, Float), DIM_MAX_ARGS_3, (EXT, Utility), "Returns distance of the point `p` to a line defined by points `a` and `b`.") \
  \
  SECTION("Sampling functions") \
  FUNC(sampleOffset, 2, ((ANY, variable), (T, offset, Float3)), (ARG, valueAtOffset, 1), DIM_MAX_2(DIM_C(2D), DIM_ARG(1)), (EXT, Sampling), "Returns value of `variable` sampled on a world position of (`worldPos() + offset`).") \
  FUNC(sampleAt, 2, ((ANY, variable), (T, worldPos, Float3)), (ARG, valueAtPos, 1), DIM_ARG(2), (EXT, Sampling), "Returns value of `variable` sampled on the given world position. The position doesn't have to be constant.") \
  FUNC(sampleAt, 2, ((ANY, variable), (T, worldPos, Float2)), (ARG, valueAtPos, 1), DIM_ARG(2), (EXT, Sampling), "Returns value of `variable` sampled on the given world position. The position doesn't have to be constant.") \
  \
  FUNC(sampleGradient2D, 2, ((T, value, Float), (T, dist, Float)), (T, gradient, Float2), DIM_MAX_2(DIM_C(2D), DIM_ARG(1)), (EXT, Sampling), "Returns 2D gradient of `value`, calculated as `float2(val[x + dist] - val[x - dist], val[y + dist] - val[y - dist]) / (1 + dist * 2)`") \
  FUNC(sampleAvg2D, 2, ((NUM, value), (T, dist, Float)), (ARG, avg, 1), DIM_MAX_2(DIM_C(2D), DIM_ARG(1)), (EXT, Sampling), "Samples at offsets (0,0), (dist,0), (-dist,0), (0,dist) and (0,-dist) and returns the average.`") \
  \
  SECTION("Biome functions") \
  FUNC(biomeParam_nearest, 1, ((ANY, var)), (ARG, var, 1), DIM_MAX_2(DIM_C(2D), DIM_ARG(1)), (EXT, Biome), "**This function cannot be used in the WOGLAC language. There is a special syntax construct for biome params.**\n\nReturns value of variable $var of the nearest biome.") \
  FUNC(biomeParam_nearestSet, 1, ((ANY, var)), (ARG, var, 1), DIM_MAX_2(DIM_C(2D), DIM_ARG(1)), (EXT, Biome), "**This function cannot be used in the WOGLAC language. There is a special syntax construct for biome params.**\n\nReturns value of variable $var of the nearest biome that has the variable set.") \
  FUNC(biomeParam_weighted, 2, ((NUM, var), (T, exp, Float)), (ARG, var, 1), DIM_MAX_2(DIM_C(2D), DIM_ARG(1)), (EXT, Biome), "**This function cannot be used in the WOGLAC language. There is a special syntax construct for biome params.**\n\nReturns value of variable $var weighted across surrounding biomes. The $exp adjusts exponent for the individual weights (1 = linear interpolation).") \
  \
  SECTION("Structure functions") \
  FUNC(spawn2D, 5, ((T, entryRule, Rule), (T, maxRadius, Float), (T, seed, Float), (T, spawnZ, Float), (T, spawnCondition, Bool)), (T, result, Block), DIM_C(3D), (EXT, Structure), "Creates a structure procgen pass and returns generated blocks (block.undefined on places where nothing was generated to differentiate from generated block.air). Structures can expand up to `maxRadius` chunks from the entry chunk. For each (x, y, `spawnZ`) point in space, the `entryRule` is expanded if `spawnCondition` is `true`.") \
  \
  FUNC(worldPos, 1, ((T, node, ComponentNode)), (T, worldPos, Float3), DIM_ARG(1), (EXT_CONTEXTUAL, Structure), "Returns position of the provided component node in global world coordinates (only usable in structure generation).")                \
  FUNC(worldPos, 1, ((T, localPos, Float3)), (T, worldPos, Float3), DIM_ARG(1), (EXT_CONTEXTUAL, Structure), "Transforms world component-local position to world position.") \
  FUNC(localPos, 0, (), (T, localPos, Float3), DIM_C(3D), (EXT_CONTEXTUAL, Structure), "Returns component-local position.") \
  FUNC(localPos, 1, ((T, worldPos, Float3)), (T, localPos, Float3), DIM_ARG(1), (EXT_CONTEXTUAL, Structure), "Transforms world position to component-local position.") \
	FUNC(localSeed, 0, (), (T, seed, Float), DIM_C(Const), (EXT_CONTEXTUAL, Structure), "Returns component-local seed.") \
  \
  FUNC(distanceTo, 1, ((T, node, ComponentNode)), (T, dist, Float), DIM_C(3D), (EXT_CONTEXTUAL, Structure), "Returns distance from the current block to the provided component node.") \
  FUNC(sampleAt, 2, ((ANY, variable), (T, node, ComponentNode)), (ARG, valueAtNodePos, 1), DIM_MIN_ARGS_2, (EXT_CONTEXTUAL, Structure), "Returns value of `variable` sampled on position of the given node.") \
  \
  SECTION("Noise functions") \
  FUNC(randC, 1, ((T, seed, Float)), (T, result, Float), DIM_C(Const), (EXT, Noise), "Returns random value in range [0,1], constant everywhere.")                              \
  FUNC(randL, 1, ((T, seed, Float)), (T, result, Float), DIM_C(Const), (EXT_CONTEXTUAL, Structure), "Returns random value in range [0,1], constant everywhere. Incorporates local seed of the currently generated structure (works similarly to `randC(localSeed() + seed)`).") \
  FUNC(randPC, 1, ((T, seed, Float)), (T, result, Float), DIM_C(PerChunk), (EXT, Noise), "Returns random value in range [0,1], different for each chunk.") \
  FUNC(rand2D, 1, ((T, seed, Float)), (T, result, Float), DIM_C(2D), (EXT, Noise), "Returns random value in range [0,1], different for every column.") \
  FUNC(rand3D, 1, ((T, seed, Float)), (T, result, Float), DIM_C(3D), (EXT, Noise), "Returns random value in range [0,1], different for every block.") \
  FUNC(valueNoisePC, 3, ((T, octaveSize, Float), (T, seed, Float), (T, nodeValue, Float)), (T, result, Float), DIM_C(PerChunk), (EXT, Noise), "Linearly interpolates between values at node points that are determined by `nodeValue`.") \
  FUNC(valueNoise2D, 3, ((T, octaveSize, Float), (T, seed, Float), (T, nodeValue, Float)), (T, result, Float), DIM_C(2D), (EXT, Noise), "Linearly interpolates between values at node points that are determined by `nodeValue`.") \
  FUNC(perlin2D, 2, ((T, octaveSize, Float), (T, seed, Float)), (T, result, Float), DIM_C(2D), (EXT, Noise), "Returns 2D Perlin noise value in range [-1,1].") \
  FUNC(perlin3D, 2, ((T, octaveSize, Float), (T, seed, Float)), (T, result, Float), DIM_C(3D), (EXT, Noise), "Returns 3D Perlin noise value in range [-1,1].") \
  FUNC(voronoi2D, 4, ((T, octaveSize, Float), (T, seed, Float), (T, resultType, Float), (T, metricExponent, Float)), (T, result, Float), DIM_C(2D), (EXT, Noise), "Returns 2D Voronoi-diagram based value. Use `metricExponent = 2` for standard euclidean metric.\n* `resultType=0` -> distance to the edge (2ndDist-1stDist)\n* `resultType=1` -> distance to the nearest point (1stDist)\n* `resultType=2` -> 1stDist / 2ndDist") \
  FUNC(voronoi2DColored, 5, ((T, octaveSize, Float), (T, seed, Float), (T, resultType, Float), (T, metricExponent, Float), (T, coloring, Float)), (T, result, Float), DIM_C(2D), (EXT, Noise), "Same as voronoi2D, except each node now accepts `coloring`; there are no edges between nodes of the same color. For that to work, there are special `resultType` values:\n* `resultType=10` -> weighted distance from center\n* `resultType=11` -> nearest point coloring\n* `resultType=12` -> weighted distance from border") \
  /*FUNC(voronoi3D, 4, ((T, octaveSize, Float), (T, seed, Float), (T, resultType, Float), (T, metricExponent, Float)), (T, result, Float), DIM_C(3D), (EXT, Noise), "Returns 3D Voronoi-diagram based value. \n* `resultType=0` -> distance to the edge (2ndDist-1stDist)\n* `resultType=1` -> distance to the nearest point (1stDist)\n* `resultType=2` -> 1stDist / 2ndDist") \
	FUNC(voronoi3DParam, 5, ((T, octaveSize, Float), (T, seed, Float), (T, resultType, Float), (T, metricExponent, Float), (T, coloring, Float)), (T, result, Float), DIM_C(3D), (EXT, Noise), "Same as voronoi3D, but supports more `resultType` values:\n* `resultType=10` -> nearest `param`\n* `resultType=11` -> interpolated `param` between the two nearest points")*/ \
  FUNC(poissonDisc2DBool, 2, ((T, seed, Float), (T, radius, Float)), (T, isNode, Bool), DIM_C(2D), (EXT, Noise), "Spreads points pseudorandomly on the 2D plane. Each point has a `radius` (2D dimensionality) that can be between 1 and 16. Distance of any two points is not less than sum of their radii. Returns true if there is a point on the current position or false if there isn't.") \
  FUNC(osimplex2D, 2, ((T, octaveSize, Float), (T, seed, Float)), (T, result, Float), DIM_C(2D), (EXT, Noise), "Returns 2D Open Simples 2 noise value in range [-1,1].") \
  FUNC(osimplex3D, 2, ((T, octaveSize, Float), (T, seed, Float)), (T, result, Float), DIM_C(3D), (EXT, Noise), "Returns 3D Open Simples 2 noise value in range [-1,1].") \
  \
  SECTION("Aggregation functions") \
  FUNC(minPC, 1, ((T, val, Float)), (T, minVal, Float), DIM_C(PerChunk), (EXT, Utility), "Returns minimum value of `val` across the entire chunk. Expects `val` to have `2D` dimensionality.") \
  FUNC(maxPC, 1, ((T, val, Float)), (T, maxVal, Float), DIM_C(PerChunk), (EXT, Utility), "Returns maximum value of `val` across the entire chunk. Expects `val` to have `2D` dimensionality.") \
  \
  SECTION("Math functions") \
  FUNC(min, 2, ((NUM, a), (ARG, b, 1)), (ARG, r, 1), DIM_MAX_ARGS_2, (INLINE, arg1.min(arg2)), "Returns minimum of the two values.") \
  FUNC(max, 2, ((NUM, a), (ARG, b, 1)), (ARG, r, 1), DIM_MAX_ARGS_2, (INLINE, arg1.max(arg2)), "Returns maximum of the two values.") \
  FUNC(smoothMin, 3, ((T, a, Float), (T, b, Float), (T, k, Float)), (T, r, Float), DIM_MAX_ARGS_3, (EXT, Utility), "Returns smoothed minimum of the two values with smoothing radius `k`.") \
  FUNC(smoothMax, 3, ((T, a, Float), (T, b, Float), (T, k, Float)), (T, r, Float), DIM_MAX_ARGS_3, (EXT, Utility), "Returns smoothed maximum of the two values with smoothing radius `k .") \
  FUNC(clamp, 3, ((NUM, v), (ARG, min, 1), (ARG, max, 1)), (ARG, r, 1), DIM_MAX_ARGS_3, (INLINE, arg1.clamp(arg2, arg3)), "Returns value `v` limited to bounds [`min–max`].") \
  FUNC(clamp01, 1, ((NUM, v)), (ARG, r, 1), DIM_ARG(1), (INLINE, arg1.clamp(0, 1)), "Returns value `v` limited to bounds [0-1].") \
  FUNC(mix, 3, ((NUM, a), (ARG, b, 1), (ARG, p, 1)), (ARG, r, 1), DIM_MAX_ARGS_3, (INLINE, arg1 * (Arg1::T(1.0f) - arg3) + arg2 * arg3), "Returns `a * (1 - p) + b * p`.") \
  FUNC(abs, 1, ((NUM, v)), (ARG, r, 1), DIM_MAX_ARGS_1, (INLINE, arg1.abs()), "Returns absolute value of the parameter") \
  \
  FUNC(floor, 1, ((NUM, v)), (ARG, r, 1), DIM_ARG(1), (INLINE, arg1.floor()), "") \
  FUNC(ceil, 1, ((NUM, v)), (ARG, r, 1), DIM_ARG(1), (INLINE, arg1.ceil()), "") \
  FUNC(round, 1, ((NUM, v)), (ARG, r, 1), DIM_ARG(1), (INLINE, arg1.round()), "") \
  FUNC(fract, 1, ((NUM, v)), (ARG, r, 1), DIM_ARG(1), (INLINE, arg1.componentUnary([] (float f) { return f - trunc(f); })), "Returns fractional part of the number `x - trunc(x)`.") \
  FUNC(ffract, 1, ((NUM, v)), (ARG, r, 1), DIM_ARG(1), (INLINE, arg1.componentUnary([] (float f) { return f - floor(f); })), "Returns fractional part of the number `x - floor(x)`.") \
  FUNC(pow, 2, ((T, v, Float), (T, e, Float)), (T, r, Float), DIM_MAX_ARGS_2, (INLINE, pow(arg1, arg2)), "Returns power of `v` to the exponent `e`.") \
  \
  FUNC(sin, 1, ((T, x, Float)), (T, r, Float), DIM_MAX_ARGS_1, (INLINE, sin(arg1)), "Returns `sin(x)`, `x` is in radians.") \
  FUNC(cos, 1, ((T, x, Float)), (T, r, Float), DIM_MAX_ARGS_1, (INLINE, cos(arg1)), "Returns `cos(x)`, `x` is in radians.") \
  \
  SECTION("Basic math functions") \
  FUNC(inverse, 1, ((NUM, a)), (ARG, r, 1), DIM_MAX_ARGS_1, (INLINE, -arg1), "Returns negative value of the argument (`-a`).") \
  FUNC(add, 2, ((NUM, a), (ARG_OR_T, b, 1, Float)), (ARG, r, 1), DIM_MAX_ARGS_2, (INLINE, arg1 + arg2), "") \
  FUNC(sub, 2, ((NUM, a), (ARG_OR_T, b, 1, Float)), (ARG, r, 1), DIM_MAX_ARGS_2, (INLINE, arg1 - arg2), "") \
  FUNC(mult, 2, ((NUM, a), (ARG_OR_T, b, 1, Float)), (ARG, r, 1), DIM_MAX_ARGS_2, (INLINE, arg1 * arg2), "") \
  FUNC(div, 2, ((NUM, a), (ARG_OR_T, b, 1, Float)), (ARG, r, 1), DIM_MAX_ARGS_2, (INLINE, arg1 / arg2), "") \
  FUNC(mod, 2, ((NUM, a), (ARG_OR_T, b, 1, Float)), (ARG, r, 1), DIM_MAX_ARGS_2, (INLINE, arg1.componentBinary(arg2, [] (float a, float b) { return fmod(a, b); })), "Floating point modulo (C++ fmod)") \
  \
  SECTION("Basic logic functions") \
  FUNC(logOr, 2, ((T, a, Bool), (ARG, b, 1)), (ARG, r, 1), DIM_MAX_ARGS_2, (INLINE, arg1 || arg2), "") \
  FUNC(logAnd, 2, ((T, a, Bool), (ARG, b, 1)), (ARG, r, 1), DIM_MAX_ARGS_2, (INLINE, arg1 && arg2), "") \
  FUNC(logNot, 1, ((T, a, Bool)), (ARG, r, 1), DIM_ARG(1), (INLINE, !arg1), "") \
  \
  FUNC(bool, 1, ((T, a, Block)), (T, b, Bool), DIM_MAX_ARGS_1, (INLINE, arg1 != blockID_undefined), "Converts to bool (returns `true` if the block is not `block.undefined`, even with air.)") \
  \
  SECTION("Comparison functions") \
  FUNC(compEq, 2, ((ANY, a), (ARG, b, 1)), (T, r, Bool), DIM_MAX_ARGS_2, (INLINE, arg1 == arg2), "") \
  FUNC(compEq, 2, ((NUM_VEC, a), (T, b, Float)), (T, r, Bool), DIM_MAX_ARGS_2, (INLINE, arg1 == arg2), "") \
  FUNC(compNeq, 2, ((ANY, a), (ARG, b, 1)), (T, r, Bool), DIM_MAX_ARGS_2, (INLINE, arg1 != arg2), "") \
  FUNC(compNeq, 2, ((NUM_VEC, a), (T, b, Float)), (T, r, Bool), DIM_MAX_ARGS_2, (INLINE, arg1 != arg2), "") \
  FUNC(compLt, 2, ((T, a, Float), (ARG, b, 1)), (T, r, Bool), DIM_MAX_ARGS_2, (INLINE, arg1 < arg2), "") \
  FUNC(compGt, 2, ((T, a, Float), (ARG, b, 1)), (T, r, Bool), DIM_MAX_ARGS_2, (INLINE, arg1 > arg2), "") \
  FUNC(compLeq, 2, ((T, a, Float), (ARG, b, 1)), (T, r, Bool), DIM_MAX_ARGS_2, (INLINE, arg1 <= arg2), "") \
  FUNC(compGeq, 2, ((T, a, Float), (ARG, b, 1)), (T, r, Bool), DIM_MAX_ARGS_2, (INLINE, arg1 >= arg2), "") \

class WorldGenAPI {

public:
	using Seed = uint32_t;
	using FunctionArgs = std::vector<WGA_Value *>;
	using FunctionID = int;
	using Type = WGA_Value::ValueType;

public:
	struct FunctionArgument {

	public:
		FunctionArgument() {}

		inline FunctionArgument(Type type, const std::string &name) : type(type), name(name) {}

	public:
		Type type;
		std::string name;

	};
	struct Function {

	public:
		/// Integer ID
		FunctionID id;

		/// Name of the function
		std::string name;

		/// name(Arg1, Arg2, ...)
		std::string prototype;

		/// For documentation purposes
		std::string description;

		std::string section;

	public:
		std::vector<FunctionArgument> arguments;
		FunctionArgument returnValue;

	public:
		static std::string composePrototype(const std::string &functionName, const std::vector<WGA_Value::ValueType> &argTypes);

	};
	struct Functions {

	public:
		std::vector<Function> list;
		std::map<std::string, FunctionID> prototypeMapping;
		std::unordered_set<std::string> nameSet;
		std::vector<std::string> nameList; ///< Ordered name list
		std::map<std::string, std::vector<FunctionID>> nameMapping;

	public:
		/// Generates documentation in markdown format
		void generateDocumentation() const;

	};
	static const Functions &functions();

public:
	virtual ~WorldGenAPI();

public:
	inline WorldGenSeed seed() const {
		return seed_;
	}

	virtual void setSeed(WorldGenSeed set) {
		seed_ = set;
	}

	inline const std::unordered_map<std::string, BlockID> &blockUIDMapping() const {
		return blockUIDMapping_;
	}

	virtual void setBlockUIDMapping(const std::unordered_map<std::string, BlockID> &set) {
		blockUIDMapping_ = set;
	}

	inline auto biomeGridSize() const {
		return biomeGridSize_;
	}

	inline void setBiomeGridSize(BlockWorldPos_T set) {
		if(set < 16 || !std::has_single_bit(static_cast<uint64_t>(set)))
			throw std::exception("Biome grid size must be larger than 16 and be power of 2.");

		biomeGridSize_ = set;
	}

public:
	virtual WGA_Value *constFloat(float val) = 0;
	virtual WGA_Value *constFloat3(const V3F val) = 0;
	virtual WGA_Value *constBlock(BlockID val) = 0;
	virtual WGA_Value *constBool(bool val) = 0;
	virtual WGA_Value *constRule(WGA_Rule *val) = 0;
	virtual WGA_Value *constComponentNode(WGA_ComponentNode *val) = 0;

	inline WGA_Value *airBlock() {
		return constBlock(BlockID(0));
	}

	inline WGA_Value *constBlock(const std::string &uid) {
		const auto r = blockUIDMapping_.find(uid);
		if(r == blockUIDMapping_.end())
			throw std::exception(std::format("Block UID '{}' not defined.", uid).c_str());

		return constBlock(r->second);
	}

public:
	virtual WGA_Biome *newBiome() = 0;
	virtual WGA_Rule *newRule() = 0;

	/// New rule expansion that expands to nothing
	virtual WGA_RuleExpansion *newRuleExpansion(WGA_Rule *rule) = 0;

	/// Rule expansion to a component
	virtual WGA_RuleExpansion *newRuleExpansion(WGA_Rule *rule, WGA_Component *component, const std::string &node) = 0;

	/// Rule expansion to another rule
	virtual WGA_RuleExpansion *newRuleExpansion(WGA_Rule *rule, WGA_Rule *targetRule) = 0;

	virtual WGA_Component *newComponent() = 0;
	virtual WGA_ComponentNode *newComponentNode() = 0;

public:
	virtual WGA_Value *function(FunctionID function, const FunctionArgs &args) = 0;

	/// Proxy creates a WGA_Value with exact same values as #v.
	/// This is useful for biome variables, because they are indexed by the default WGA_Value.
	/// So if the default value is same for multiple biome variables, they would be considered the same one variable. Creating a proxy prevents that.
	virtual WGA_Value *proxy(WGA_Value *v) = 0;

	/// Returns value representing given grammar symbol param.
	virtual WGA_Value *grammarSymbolParam(WGA_GrammarSymbol *sym, const std::string &name, WGA_Value::ValueType type, WGA_Value *defaultValue) = 0;

private:
	WorldGenSeed seed_ = 0;
	std::unordered_map<std::string, BlockID> blockUIDMapping_;
	BlockWorldPos_T biomeGridSize_ = 256;

};

