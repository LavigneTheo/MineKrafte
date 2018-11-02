#pragma once

#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>
#include <random>
#include <functional>

#define _USE_MATH_DEFINES
#include <math.h>

#include "../math/Vec2f.h"

class Perlin2D {
	unsigned int mSize, mSeed, mLayers;
	float mFrequency, mAmplitude;

	int* mPermutationTable;
	std::vector<Vec2f> mRandoms;

	Perlin2D() {}
	void generateHashTable();
	float getNoiseAt(const Vec2f& v);

public:
	Perlin2D(const unsigned int size, const unsigned int seed, const float freq, const float amplitude, const unsigned int layers) :
		mSize(size), mSeed(seed), mFrequency(freq), mAmplitude(amplitude), mLayers(layers) {
		mPermutationTable = (int*)malloc(sizeof(int) * 2 * mSize);
		generateHashTable();
	}
	~Perlin2D() { free(mPermutationTable); }
	
	float getFractalSumAt(const Vec2f& v);
	void saveFractSum();

	float smoothstep(const float& raw_t) { return raw_t * raw_t * (3 - 2 * raw_t); }
	float lerp(const float xLow, const float xHigh, const float t) { return xLow * (1 - t) + xHigh * t; }
	float dot(const Vec2f& v1, const Vec2f& v2) { return v1.mx * v2.mx + v1.my * v2.my; }
	int hash(const int &x, const int &y) const { return mPermutationTable[mPermutationTable[x] + y]; }

};