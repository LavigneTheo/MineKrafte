#pragma once

enum BlockType {
	AIR = 0,
	GRASS = 1,
	DIRT = 2
};

enum Side {
	TOP = 0,
	BOTTOM = 1,
	SIDE = 2
};

struct TexturePosition {
	float xStart, yStart, xEnd, yEnd;
};

struct BlockInfo
{
	BlockType mType;

	//Texture position
	TexturePosition mTopPosition;
	TexturePosition mBottomPosition;
	TexturePosition mSidePosition;

	bool solid;
};

class BlockData {
private:
	BlockInfo mInfo;
	BlockData(const BlockInfo& info) : mInfo(info) {}
public:
	BlockInfo getInfo() const {
		return mInfo;
	}


	
};
