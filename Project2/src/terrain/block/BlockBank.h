#pragma once
#include "BlockData.h"
#include "../utils/Singleton.h"
#include <iostream>
#include <map>



class BlockBank {
private:
	static BlockBank* INSTANCE;
	std::map<BlockType, BlockInfo> mBlockInfos;

	BlockBank() {
		BlockInfo grass;
		grass.mType = GRASS;
		grass.solid = true;
		grass.mBottomPosition = TexturePosition{ 0,0 ,1 ,1};
		grass.mTopPosition = TexturePosition{ 0,0 , 1, 1};
		grass.mSidePosition = TexturePosition{ 0,0 ,1 , 1};
		mBlockInfos.emplace(GRASS, grass);

		BlockInfo air;
		air.mType = AIR;
		air.solid = false;
		mBlockInfos.emplace(AIR, air);
	}

	~BlockBank() {
		delete INSTANCE;
	}
public:
	static BlockBank* getInstance() {
		if (INSTANCE == nullptr)
			INSTANCE = new BlockBank;
		return INSTANCE;
	}
	BlockInfo getInfo(const BlockType& type) const {
		return mBlockInfos.at(type);
	}

	std::map<BlockType, BlockInfo> getInfoList() const {
		return mBlockInfos;
	}

	TexturePosition getTextureCoord(const BlockType& type, const Side& side) const {
		if (side == TOP)
			return getInfo(type).mTopPosition;
		if (side == BOTTOM)
			return getInfo(type).mBottomPosition;
		if (side == SIDE)
			return getInfo(type).mSidePosition;

		return TexturePosition{ 0, 0, 1, 1 };
	}
};

