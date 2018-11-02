#pragma once
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <iostream>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "block/Block.h"
#include "block/BlockBank.h"
#include "../buffer/Mesh.h"

class TerrainManager;

class Chunk : Mesh {
private:
	glm::vec2 mPosition;
	std::vector<Block> mBlocks;
	BlockBank* mBlockBank = BlockBank::getInstance();
	
	
public:
	//set within the terrainManager constructor
	static TerrainManager* mTerrainManager;

	const static int WIDTH = 16, DEPTH = 16, HEIGHT = 256;

	Chunk(int x, int z);
	~Chunk();
	
	glm::vec2 get_position() const;

	void fillFlat();
	void fillBumpy();

	void buildMesh();
	void rebuildMesh() { deleteMesh(); buildMesh();}

	void tryAddFace(const unsigned int& x, const unsigned int& y, const unsigned int& z, std::vector<float>& data, std::vector<unsigned int>& indices, unsigned int& indicesCount);

	Block getBlock(const int& x, const int& y, const int& z) {
		return mBlocks.at(y * Chunk::DEPTH * Chunk::WIDTH + Chunk::DEPTH * x + z);
	}

	bool isSolidAt(const int& x, const int& y, const int& z) {
		return getBlock(x, y, z).getData().solid;
	}
	void loadMeshData(const std::vector<float>& data, const std::vector<unsigned int>& indices);

	void drawChunk();
	void freeChunk();
};



