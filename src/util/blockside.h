#pragma once

#include "enumutils.h"
#include "flags.h"
#include "bitset.h"
#include "defines.h"

#include "util/blockworldpos.h"

#define BLOCK_SIDES(I, A) I(A, Xminus) I(A, Xplus) I(A, Yminus) I(A, Yplus) I(A, Zminus) I(A, Zplus)
#define SPECIAL_BLOCK_SIDES(I, A) I(A, Xcenter) I(A, Ycenter) I(A, Zcenter)
#define BLOCK_SIDE_ALIASES(I, A) I(A, Up, Zplus) I(A, Down, Zminus)

enum class BlockSide {
#define I(A, name, ...) name,
#define AI(A, name, alias, ...) name = alias,

	BLOCK_SIDES(I, NOTHING)

	_cnt,
	_xx = _cnt - 1,

	SPECIAL_BLOCK_SIDES(I, NOTHING)

	BLOCK_SIDE_ALIASES(AI, NOTHING)

#undef I
#undef AI
};
enum BlockSideFlag {
#define I(A, name, ...) name = 1 << +BlockSide::name,
	BLOCK_SIDES(I, NOTHING)
	SPECIAL_BLOCK_SIDES(I, NOTHING)
	BLOCK_SIDE_ALIASES(I, NOTHING)
#undef I
};
using BlockSideFlags = Flags<BlockSideFlag>;
using BlockSideBitSet = BitSet<+BlockSide::_cnt>;

static inline const BlockSideFlags horizontalBlockSides{BlockSideFlag::Xplus, BlockSideFlag::Xminus, BlockSideFlag::Yplus, BlockSideFlag::Yminus};

/// For Xplus returns Xminus etc
inline BlockSide oppositeBlockSide(BlockSide s) {
	return static_cast<BlockSide>(+s ^ 1);
}

/// For both Xplus and Xminus returns Xplus etc
inline BlockSide absBlockSide(BlockSide s) {
	return static_cast<BlockSide>(+s | 1);
}

/// For both Xplus and Xminus returns Xplus etc
inline bool isBlockSidePositive(BlockSide s) {
	return (+s & 1);
}

inline int blockSideVectorComponent(BlockSide s) {
	return (+s >> 1);
}

/// Returns 4 block sides that are side to a given direction
BlockSideFlags relativeSideBlockSides(BlockSide s);

const BlockWorldPos &blockSideNormalVector(BlockSide s);

inline const BlockWorldPos &blockSideNormalVector(int s) {
	return blockSideNormalVector(static_cast<BlockSide>(s));
}

const Vector3F &blockSideNormalVectorF(BlockSide s);

inline const Vector3F &blockSideNormalVectorF(int s) {
	return blockSideNormalVectorF(static_cast<BlockSide>(s));
}