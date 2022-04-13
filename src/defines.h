#pragma once

#include <stdint.h>

#include "util/vector.h"
#include "util/matrix.h"

using BlockWorldPos_T = int32_t;
using BlockWorldPos = Vector<BlockWorldPos_T, 3>;

constexpr BlockWorldPos chunkSize = 16;
constexpr BlockWorldPos_T chunkSurface = 256;
constexpr BlockWorldPos_T chunkVolume = 4096;

constexpr BlockWorldPos_T blockInChunkPosMask = 0xf;

using BlockTransformMatrix = Matrix<BlockWorldPos_T, 4, 4>;

using BlockID = uint16_t;
using ChunkBlockIndex = uint16_t;
using WorldGenSeed = size_t;