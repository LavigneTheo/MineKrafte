#pragma once
#include <iostream>
#include <map>

#include "../terrain/Chunk.h"
#include "../shader/TerrainShader.h"
#include "../kernel/Window.h"
#include "../buffer/Mesh.h"
#include "../buffer/TextureCache.h"
#include "../utils/algo/Perlin2D.h"
#include "../kernel/TimeTester.h"
#include "../utils/math/Vec2f.h"
#include <algorithm>


class TerrainManager : CameraSubscriber {
private:
	std::vector<Chunk> mChunks;

	TerrainShader m_shader;
	MeshTexture mBlocSprite;

	TimeTester* t = TimeTester::getInstance();

	short VIEW_RANGE = 5;

	int mRightTheshhold, mLeftThreshold, mFrontThreshold, mBackThreshold;
	//In which chunk the camera is sittong
	Vec2f mCurrentChunk;

	Perlin2D mPerlin2D = Perlin2D(64, 45678, 1, 0.5, 5);

public:
	static int vertexCount;
	TerrainManager();
	~TerrainManager() {};

	void draw();
	void init_shader();

	void insertChunk(Vec2f position);

	void moveChunks(const Vec2f& direction);
	void removeChunk(const int& x, const int& y);

	void onCameraMove() override;

	Perlin2D* getPerlin2D() { return &mPerlin2D; }
	float get2DNoiseAt(const Vec2f& pos) { return mPerlin2D.getFractalSumAt(pos); }


	Chunk* getChunkAt(Vec2f pos) {
		for (Chunk& c : mChunks)
			if (c == pos)
				return &c;
		return nullptr;
	}

	Chunk* getChunkAt(const int& x, const int& y) {
		for (Chunk& c : mChunks)
			if (c.get_position().mx == x && c.get_position().my == y)
				return &c;
		return nullptr;
	}

	int getChunkIndex(const int& x, const int& y) {
		for (int i = 0; i < mChunks.size(); i++)
			if (mChunks.at(i).get_position().mx == x && mChunks.at(i).get_position().my == y)
				return i;
		return -1;
	}
};

