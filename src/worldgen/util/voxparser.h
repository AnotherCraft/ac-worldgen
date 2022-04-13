#pragma once

#include <QByteArray>
#include <QBuffer>
#include <QHash>

/// Parser of the VOX file format
/// File format specified here: https://github.com/ephtracy/voxel-model/blob/master/MagicaVoxel-file-format-vox.txt
class VOXParser {

public:
	struct VoxelPos {
		uint8_t x, y, z;
	};

public:
	void parseFile(const QString &file);
	void parseData(const QByteArray &data);

public:
	inline const auto &voxels() const {
		return voxels_;
	}

	inline bool isEmpty() const {
		return voxels_.isEmpty();
	}

	void clear();

private:
	struct Chunk {
		QByteArray name;
		QByteArray data;
		QByteArray childrenChunks;
	};

private:
	Chunk readChunk(QBuffer &b);

private:
	QHash<uint8_t, QVector<VoxelPos>> voxels_;

};

