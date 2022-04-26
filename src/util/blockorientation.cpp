
#include "blockorientation.h"

#include <unordered_map>

static const std::unordered_map<std::string, BlockSide> strToSide{
	{"x+", BlockSide::Xplus},
	{"x-", BlockSide::Xminus},
	{"y+", BlockSide::Yplus},
	{"y-", BlockSide::Yminus},
	{"z+", BlockSide::Zplus},
	{"z-", BlockSide::Zminus},
	{"",   BlockSide::_cnt}
};

BlockOrientation::BlockOrientation() {

}

BlockOrientation::BlockOrientation(const std::string &facing, const std::string &rotation) {
	facing_ = strToSide.at(facing);
	upDirection_ = strToSide.at(rotation);

	validate();
}

BlockOrientation::BlockOrientation(BlockSide facing, BlockSide rotation) {
	facing_ = facing;
	upDirection_ = rotation;

	validate();
}

BlockOrientation BlockOrientation::adjacent() const {
	return isSpecified() ? BlockOrientation(oppositeBlockSide(facing_), upDirection_) : BlockOrientation();
}

BlockOrientation BlockOrientation::nextUpVariant() const {
	if(!isSpecified())
		return {};

	int up = +upDirection_;

	do
		up = (+up + 1) % +BlockSide::_cnt;

	while(absBlockSide(facing_) == absBlockSide(static_cast<BlockSide>(up)));

	return BlockOrientation(facing_, static_cast<BlockSide>(up));
}

BlockTransformMatrix BlockOrientation::transformToMatch(const BlockOrientation &target, int flags) const {
	if(!isSpecified() || !target.isSpecified())
		return BlockTransformMatrix();

	static const std::unordered_map<BlockOrientation, BlockTransformMatrix> matrices = [] {
		std::unordered_map<BlockOrientation, BlockTransformMatrix> result;

		for(int f = 0; f < +BlockSide::_cnt; f++) {
			const BlockSide fs = static_cast<BlockSide>(f);

			for(int u = 0; u < +BlockSide::_cnt; u++) {
				const BlockSide us = static_cast<BlockSide>(u);

				if(absBlockSide(fs) == absBlockSide(us))
					continue;

				result.insert({BlockOrientation(fs, us), BlockTransformMatrix::lookAt(BlockWorldPos(), blockSideNormalVector(f), blockSideNormalVector(u))});
			}
		}

		return result;
	}();
	static const std::unordered_map<BlockOrientation, BlockTransformMatrix> invMatrices = [] {
		std::unordered_map<BlockOrientation, BlockTransformMatrix> result;
		for(auto it = matrices.begin(), end = matrices.end(); it != end; it++)
			result.insert({it->first, it->second.nonScalingInverted()});
		return result;
	}();

	BlockTransformMatrix result;

	result *= invMatrices.at(target);

	const BlockWorldPos translation = BlockWorldPos(
		(flags & +TransformFlags::horizontalEdge) && !(flags & +TransformFlags::mirror) ? 1 : 0,
		flags & +TransformFlags::verticalEdge ? 1 : 0,
		flags & +TransformFlags::adjacent ? 1 : 0
	);

	if(translation != BlockWorldPos())
		result *= BlockTransformMatrix::translation(translation);

	if(flags & +TransformFlags::mirror)
		result *= BlockTransformMatrix::scaling(BlockWorldPos(-1, 1, 1));

	result *= matrices.at(*this);

	return result;
}

std::string BlockOrientation::toString() const {
	if(!isSpecified())
		return "(unspecified)";

	static const std::unordered_map<int, std::string> sideToStr = [] {
		std::unordered_map<int, std::string> result;
		for(auto it = strToSide.begin(), end = strToSide.end(); it != end; it++)
			result[+it->second] = it->first;

		return result;
	}();

	return sideToStr.at(+facing_) + sideToStr.at(+upDirection_);
}

void BlockOrientation::validate() {
	if(isSpecified() && upDirection_ == BlockSide::_cnt)
		upDirection_ = absBlockSide(facing_) == BlockSide::Zplus ? BlockSide::Xplus : BlockSide::Zplus;

	ASSERT(!isSpecified() || absBlockSide(facing_) != absBlockSide(upDirection_));
}
