#pragma once
#include "BlockData.h"
#include "BlockBank.h"

struct BlockDataHolder
{
	BlockType mType;
	bool solid;
};

class Block {
private:
	BlockDataHolder mData;

public:
	Block(BlockType blockType, BlockBank* bank) {
		mData.mType = blockType;
		mData.solid = bank->getInfo(blockType).solid;
	}

	BlockDataHolder getData() const {return mData;}
};

