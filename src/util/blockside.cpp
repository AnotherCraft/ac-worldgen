#include "blockside.h"

const BlockWorldPos &blockSideNormalVector(BlockSide s) {
	static const BlockWorldPos result[+BlockSide::_cnt + 2] = {
		BlockWorldPos(-1, 0, 0),
		BlockWorldPos(1, 0, 0),
		BlockWorldPos(0, -1, 0),
		BlockWorldPos(0, 1, 0),
		BlockWorldPos(0, 0, -1),
		BlockWorldPos(0, 0, 1),

		BlockWorldPos(0, 0, 0),
		BlockWorldPos(0, 0, 0),
	};

	return result[+s];
}

const Vector3F &blockSideNormalVectorF(BlockSide s) {
	static const Vector3F result[+BlockSide::_cnt + 2] = {
		Vector3F(-1, 0, 0),
		Vector3F(1, 0, 0),
		Vector3F(0, -1, 0),
		Vector3F(0, 1, 0),
		Vector3F(0, 0, -1),
		Vector3F(0, 0, 1),

		Vector3F(0, 0, 0),
		Vector3F(0, 0, 0),
	};

	return result[+s];
}

BlockSideFlags relativeSideBlockSides(BlockSide s) {
	static const BlockSideFlags r[3] = {
		{BlockSideFlag::Yplus, BlockSideFlag::Yminus, BlockSideFlag::Zplus, BlockSideFlag::Zminus},
		{BlockSideFlag::Xplus, BlockSideFlag::Xminus, BlockSideFlag::Zplus, BlockSideFlag::Zminus},
		{BlockSideFlag::Xplus, BlockSideFlag::Xminus, BlockSideFlag::Yplus, BlockSideFlag::Yminus},
	};
	return r[+s >> 1];
}

const QString &blockSideName(BlockSide s) {
	static const QString result[]{
#define I(A, name, ...) #name,
		BLOCK_SIDES(I, void)
#undef I
	};
	return result[+s];
}