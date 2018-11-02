#include "Chunk.h"
#include "../manager/TerrainManager.h"


TerrainManager* Chunk::mTerrainManager = nullptr;

Chunk::Chunk(int& x, int& z) {
	mPosition.mx = x;
	mPosition.my = z;
	
	fillBumpy();
}

Chunk:: Chunk(const Vec2f v) : mPosition(v) {

	fillBumpy();
}

Chunk::~Chunk() {
	
}

void Chunk::fillBumpy() {
	
	for (int x = 0; x < Chunk::WIDTH; x++) {
		for (int z = 0; z < Chunk::DEPTH; z++) {
			float value = mTerrainManager->get2DNoiseAt(Vec2f(
				x + mPosition.mx * WIDTH,
				z + mPosition.my * DEPTH
			)) * 255;
			for (int y = 0; y < Chunk::HEIGHT; y++) {
				if (y > (int)value) {
					mBlocks.push_back(Block(AIR, mBlockBank));
				}
				else
					mBlocks.push_back(Block(GRASS, mBlockBank));
			}
		}
	}
	
	buildMesh();
}

void Chunk::fillFlat() {
	
	for (unsigned int y = 0; y < Chunk::HEIGHT; y++) {
		for (unsigned int x = 0; x < Chunk::WIDTH; x++) {
			for (unsigned int z = 0; z < Chunk::DEPTH; z++) {
				if (y > 9) {
					mBlocks.push_back(Block(AIR, mBlockBank));
				}
					
				else 
					mBlocks.push_back(Block(GRASS, mBlockBank));
			}
		}
	}
	
	buildMesh();
}




float frontFace[] = {
	1, 1, 0,
	1, 0, 0,
	0, 0, 0,
	0, 1, 0
};

float backFace[] = {
	0, 0, 1,
	1, 0, 1,
	1, 1, 1,
	0, 1, 1
};

float rightFace[] = {
	1, 0, 1,
	1, 0, 0,
	1, 1, 0,
	1, 1, 1

};

float leftFace[] = {
	0, 1, 0,
	0, 0, 0,
	0, 0, 1,
	0, 1, 1
};

float topFace[] = {
	1, 1, 0,
	0, 1, 0,
	0, 1, 1,
	1, 1, 1
};

float bottomFace[] = {
	0, 0, 1,
	0, 0, 0,
	1, 0, 0,
	1, 0, 1
};


void insert(float* faceVertices, TexturePosition& texCoord, const int& xOffset, const int& yOffset, const int& zOffset, std::vector<float>& vertices, std::vector<unsigned int>& indices, unsigned int& indicesCount) {
	vertices.push_back(xOffset + faceVertices[0]);
	vertices.push_back(yOffset + faceVertices[1]);
	vertices.push_back(zOffset + faceVertices[2]);

	vertices.push_back(texCoord.xStart);
	vertices.push_back(texCoord.yEnd);

	vertices.push_back(xOffset + faceVertices[3]);
	vertices.push_back(yOffset + faceVertices[4]);
	vertices.push_back(zOffset + faceVertices[5]);

	vertices.push_back(texCoord.xStart);
	vertices.push_back(texCoord.yStart);

	vertices.push_back(xOffset + faceVertices[6]);
	vertices.push_back(yOffset + faceVertices[7]);
	vertices.push_back(zOffset + faceVertices[8]);

	vertices.push_back(texCoord.xEnd);
	vertices.push_back(texCoord.yStart);

	vertices.push_back(xOffset + faceVertices[9]);
	vertices.push_back(yOffset + faceVertices[10]);
	vertices.push_back(zOffset + faceVertices[11]);

	vertices.push_back(texCoord.xEnd);
	vertices.push_back(texCoord.yEnd);

	indices.push_back(indicesCount++);
	indices.push_back(indicesCount++);
	indices.push_back(indicesCount++);

	indices.push_back(indicesCount- 1);
	indices.push_back(indicesCount++);
	indices.push_back(indicesCount- 4);
}

void Chunk::tryAddFace(const unsigned int& x, const unsigned int& y, const unsigned int& z, std::vector<float>& vertices, std::vector<unsigned int>& indices, unsigned int& indicesCount) {
	Block b = getBlock(x, y, z);
	
	int xOffset = mPosition.mx * WIDTH + x;
	int zOffest = mPosition.my * DEPTH + z;
	
	if (b.getData().solid) {
		TexturePosition texCoord = mBlockBank->getTextureCoord(b.getData().mType, SIDE);
		
		//Right
		if (x + 1 == WIDTH) {
			Chunk* c = mTerrainManager->getChunkAt(Vec2f(mPosition.mx + 1, mPosition.my));
			if (c != nullptr && !c->isSolidAt(0, y, z))
				insert(rightFace, texCoord, xOffset, y, zOffest, vertices, indices, indicesCount);

		} else if (!isSolidAt(x + 1, y, z)) {
			insert(rightFace, texCoord, xOffset, y, zOffest, vertices, indices, indicesCount);
		}

		//Left
		if (x == 0) {
			Chunk* c = mTerrainManager->getChunkAt(Vec2f(mPosition.mx - 1, mPosition.my));
			if (c != nullptr && !c->isSolidAt(WIDTH - 1, y, z))
				insert(leftFace, texCoord, xOffset, y, zOffest, vertices, indices, indicesCount);

		} else if (!isSolidAt(x - 1, y, z)) {
			insert(leftFace, texCoord, xOffset, y, zOffest, vertices, indices, indicesCount);
		}

		//Front
		if (z == 0) {
			Chunk* c = mTerrainManager->getChunkAt(Vec2f(mPosition.mx, mPosition.my - 1));
			if (c != nullptr &&!c->isSolidAt(x, y, DEPTH - 1))
				insert(frontFace, texCoord, xOffset, y, zOffest, vertices, indices, indicesCount);

		} else if (!isSolidAt(x, y, z - 1)) {
			insert(frontFace, texCoord, xOffset, y, zOffest, vertices, indices, indicesCount);
		}


		//Back
		if (z == DEPTH - 1) {
			Chunk* c = mTerrainManager->getChunkAt(Vec2f(mPosition.mx, mPosition.my + 1));
			if (c != nullptr && !c->isSolidAt(x, y, 0))
				insert(backFace, texCoord, xOffset, y, zOffest, vertices, indices, indicesCount);

		} else if (!isSolidAt(x, y, z + 1)) {
			insert(backFace, texCoord, xOffset, y, zOffest, vertices, indices, indicesCount);
		}

		//No check for chunk's neighboors
		if (y + 1 == HEIGHT || !isSolidAt(x, y + 1, z)) {
			insert(topFace, texCoord, xOffset, y, zOffest, vertices, indices, indicesCount);
		}
		if (y == 0)
			return;
		if (!isSolidAt(x, y - 1, z)) {
			insert(bottomFace, texCoord, xOffset, y, zOffest, vertices, indices, indicesCount);
		}
	}
}

void Chunk::buildMesh() {


	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	
	unsigned int indicesCount = 0;
	for (unsigned int y = 0; y < Chunk::HEIGHT; y++) {
		for (unsigned int x = 0; x < Chunk::WIDTH; x++) {
			for (unsigned int z = 0; z < Chunk::DEPTH; z++) {
				tryAddFace(x, y, z, vertices, indices, indicesCount);
			}
		}
	}
	
	
	TerrainManager::vertexCount += indices.size() - mMeshInfo.mSize;
	
	mMeshInfo.mSize = indices.size();
	
	loadMeshData(vertices, indices);
}

void Chunk::loadMeshData(const std::vector<float>& data, const std::vector<unsigned int>& indices) {
	
	glGenVertexArrays(1, &mMeshInfo.mVao);
	glBindVertexArray(mMeshInfo.mVao);

	glGenBuffers(1, &mMeshInfo.mVbo);
	glBindBuffer(GL_ARRAY_BUFFER, mMeshInfo.mVbo);

	glGenBuffers(1, &mMeshInfo.mIbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mMeshInfo.mIbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), &indices[0], GL_STATIC_DRAW);

	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * data.size(), &data[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(0));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(3 * sizeof(float)));

	glBindVertexArray(0);
}

void Chunk::drawChunk() const {
	
	glBindVertexArray(mMeshInfo.mVao);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mMeshInfo.mIbo);
	glDrawElements(GL_TRIANGLES, mMeshInfo.mSize, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glBindVertexArray(0);
	
}

void Chunk::freeChunk() {
	TerrainManager::vertexCount -= mMeshInfo.mSize;
	deleteMesh();
}