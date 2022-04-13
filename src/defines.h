#pragma once

#include <stdint.h>

#include "util/vector.h"
#include "util/matrix.h"

using BlockWorldPos_T = int32_t;
using ChunkWorldPos_T = int32_t;
using BlockID = uint16_t;
using ChunkBlockIndex = uint16_t;
using WorldGenSeed = size_t;

constexpr BlockWorldPos_T chunkSize = 16;
constexpr BlockWorldPos_T chunkSurface = 256;
constexpr BlockWorldPos_T chunkVolume = 4096;

constexpr BlockWorldPos_T blockInChunkPosMask = 0xf;

using BlockTransformMatrix = Matrix<BlockWorldPos_T, 4, 4>;

static constexpr BlockID blockID_air = 0;
static constexpr BlockID blockID_undefined = 1;