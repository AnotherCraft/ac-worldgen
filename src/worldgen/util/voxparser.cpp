#include "voxparser.h"

#include <QFile>
#include <QDebug>

template<typename T>
T readPrimitive(QBuffer &b) {
	if(b.pos() > b.size() - static_cast<int>(sizeof(T)))
		throw "Invalid data (RP)";

	T result;
	b.read(reinterpret_cast<char *>(&result), sizeof(T));
	return result;
}

void VOXParser::parseFile(const QString &file) {
	QFile f(file);

	if(!f.open(QIODevice::ReadOnly))
		throw QStringLiteral("Could not open VOX file '%1' for reading.").arg(file);

	parseData(f.readAll());
}

void VOXParser::parseData(const QByteArray &data) {
	clear();

	QBuffer db;
	db.setData(data);
	db.open(QIODevice::ReadOnly);

	if(db.read(4) != "VOX ")
		throw QStringLiteral("Provided file is not of the VOX file format");

	const auto fileVersion = readPrimitive<uint32_t>(db);
	if(fileVersion != 150)
		throw QStringLiteral("Unsupported vox file format version (%1)").arg(fileVersion);

	// Process main chunk
	{
		const Chunk mainChunk = readChunk(db);
		if(mainChunk.name != "MAIN")
			throw "MAIN chunk expected";

		if(!db.atEnd())
			throw "There should be nothing left after the main chunk";

		if(!mainChunk.data.isEmpty())
			throw "Main chunk should not have any data";

		QBuffer mb;
		mb.setData(mainChunk.childrenChunks);
		mb.open(QIODevice::ReadOnly);

		while(!mb.atEnd()) {
			const Chunk ch = readChunk(mb);

			if(!ch.childrenChunks.isEmpty())
				throw "Invalid data (3)";

			QBuffer cb;
			cb.setData(ch.data);
			cb.open(QIODevice::ReadOnly);

			if(ch.name == "XYZI") {
				struct VoxelRec {
					uint8_t x, y, z, id;
				};

				if(!voxels_.isEmpty())
					throw "Multiple models are not supported";

				auto numVoxels = readPrimitive<uint32_t>(cb);
				if(cb.size() - cb.pos() != numVoxels * sizeof(VoxelRec))
					throw "Invalid data (5)";

				while(numVoxels--) {
					const VoxelRec voxel = readPrimitive<VoxelRec>(cb);
					voxels_[voxel.id] += VoxelPos{voxel.x, voxel.y, voxel.z};
				}
			}

				// We don't care about other chunk types
			else
				continue;

			if(!cb.atEnd())
				throw "Invalid data (4)";
		}
	}
}

void VOXParser::clear() {
	voxels_.clear();
}

VOXParser::Chunk VOXParser::readChunk(QBuffer &b) {
	if(b.pos() > b.size() - 12)
		throw "Invalid data (1)";

	Chunk chunk;
	chunk.name = b.read(4);
	const auto dataSize = readPrimitive<uint32_t>(b);
	const auto childrenSize = readPrimitive<uint32_t>(b);

	if(b.pos() > b.size() - dataSize - childrenSize)
		throw "Invalid data (2)";

	chunk.data = b.read(dataSize);
	chunk.childrenChunks = b.read(childrenSize);
	return chunk;
}
