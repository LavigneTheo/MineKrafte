#pragma once
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <iostream>
#include <vector>
#include <random>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "block/Block.h"
#include "block/BlockBank.h"
#include "../buffer/Mesh.h"
#include "../utils/math/Vec2f.h"
#include "../kernel/TimeTester.h"

class TerrainManager;

class Chunk : Mesh {
private:
	Vec2f mPosition;
	std::vector<Block> mBlocks;
	BlockBank* mBlockBank = BlockBank::getInstance();

	TimeTester* t = TimeTester::getInstance();
public:
	//set within the terrainManager constructor
	static TerrainManager* mTerrainManager;

	const static int WIDTH = 16, DEPTH = 16, HEIGHT = 256;

	Chunk(int& x, int& z);
	Chunk(const Vec2f v);
	~Chunk();
	
	Vec2f get_position() const { return mPosition; };

	void fillFlat();
	void fillBumpy();

	void buildMesh();
	void rebuildMesh() { deleteMesh(); buildMesh();}

	void tryAddFace(const unsigned int& x, const unsigned int& y, const unsigned int& z, std::vector<float>& data, std::vector<unsigned int>& indices, unsigned int& indicesCount);

	Block getBlock(const int& x, const int& y, const int& z) {
		return mBlocks.at(x * Chunk::DEPTH * Chunk::HEIGHT + Chunk::HEIGHT * z + y);
	}

	bool isSolidAt(const int& x, const int& y, const int& z) {
		return getBlock(x, y, z).getData().solid;
	}
	void loadMeshData(const std::vector<float>& data, const std::vector<unsigned int>& indices);

	void drawChunk() const;
	void freeChunk();

	bool operator==(const Vec2f& v) { return v.mx == mPosition.mx && v.my == mPosition.my; }
	bool operator==(const Chunk& c) { return c.get_position().mx == mPosition.mx && c.get_position().my == mPosition.my; }
};



