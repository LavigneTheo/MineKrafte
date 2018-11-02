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

struct Vec2
{
	Vec2(int x, int y) { mx = x; my = y; }
	Vec2() { mx = 0; my = 0; }
	int mx, my;

	bool operator==(const Vec2 &p) const
	{
		return mx == p.mx && my == p.my;
	}
	bool operator<(const Vec2& v2) const
	{
		if (mx < v2.mx)
			return true;
		else
			if (mx == v2.mx)
				return my < v2.my;
		return false;
	}

	void print() { std::cout << "[" << mx << ", " << my << "]" << std::endl; }
};

class TerrainManager : CameraSubscriber {
private:
	std::map<Vec2, Chunk> mChunks;
	TerrainShader m_shader;
	MeshTexture mBlocSprite;

	TimeTester t;

	short VIEW_RANGE = 4;

	int mRightTheshhold, mLeftThreshold, mFrontThreshold, mBackThreshold;
	//In which chunk the camera is sittong
	Vec2 mCurrentChunk;

	Perlin2D mPerlin2D = Perlin2D(64, 45678, 0.5, 0.5, 5);

public:
	static int vertexCount;
	TerrainManager();
	~TerrainManager();

	void draw();
	void init_shader();

	void insertChunk(const Vec2 position);

	void moveChunks(const Vec2& direction);
	void removeChunk(const Vec2& position);

	Chunk* getChunkAt(Vec2 pos) {
		std::map<Vec2, Chunk>::iterator chunk = mChunks.find(pos);
		if (chunk == mChunks.end())
			return nullptr;
		return &chunk->second;
	}

	void onCameraMove() override;

	Perlin2D* getPerlin2D() { return &mPerlin2D; }
	float get2DNoiseAt(const Vec2f& pos) { return mPerlin2D.getFractalSumAt(pos); }
};

