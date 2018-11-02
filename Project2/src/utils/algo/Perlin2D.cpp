#include "Perlin2D.h"


void Perlin2D::generateHashTable() {

	std::mt19937 generator(mSeed);
	std::uniform_real_distribution<float> distribution;
	auto dice = std::bind(distribution, generator);
	for (unsigned i = 0; i < mSize; ++i) {
		mRandoms.push_back(Vec2f(2 * dice() - 1, 2 * dice() - 1));
		mRandoms.at(i).normalize();
		mPermutationTable[i] = i;
	}

	std::mt19937 gen(mSeed);
	std::uniform_int_distribution<unsigned> distrUint;
	auto randInt = std::bind(distrUint, gen);

	for (int i = 0; i < mSize; i++) {
		unsigned random_index = randInt() &(mSize - 1);
		std::swap(mPermutationTable[i], mPermutationTable[random_index]);
		mPermutationTable[i + mSize] = mPermutationTable[i];
	}
}


float Perlin2D::getNoiseAt(const Vec2f& v) {
	int table_size_mask = mSize - 1;

	int xi0 = ((int)std::floor(v.m_x)) & table_size_mask;
	int yi0 = ((int)std::floor(v.m_y)) & table_size_mask;

	int xi1 = (xi0 + 1) & table_size_mask;
	int yi1 = (yi0 + 1) & table_size_mask;

	float tx = v.m_x - ((int)std::floor(v.m_x));
	float ty = v.m_y - ((int)std::floor(v.m_y));

	float ru = smoothstep(tx);
	float rv = smoothstep(ty);

	const Vec2f &c000 = mRandoms[hash(xi0, yi0)];
	const Vec2f &c100 = mRandoms[hash(xi1, yi0)];
	const Vec2f &c010 = mRandoms[hash(xi0, yi1)];
	const Vec2f &c110 = mRandoms[hash(xi1, yi1)];

	float x0 = tx, x1 = tx - 1;
	float y0 = ty, y1 = ty - 1;

	Vec2f p00 = Vec2f(x0, y0);
	Vec2f p10 = Vec2f(x1, y0);
	Vec2f p01 = Vec2f(x0, y1);
	Vec2f p11 = Vec2f(x1, y1);

	float a = lerp(dot(c000, p00), dot(c100, p10), ru);
	float b = lerp(dot(c010, p01), dot(c110, p11), ru);

	return lerp(a, b, rv);
}

float Perlin2D::getFractalSumAt(const Vec2f& pos) {

	float value = 0;
	float amplitude = mAmplitude;
	float cumAmplitude = 0;

	float xRatio = 1.f / mSize;
	float yRatio = 1.f / mSize;
	float x = pos.m_x * xRatio * mFrequency;
	float y = pos.m_y * yRatio * mFrequency;
	
	for (int l = 0; l < mLayers; l++) {
		cumAmplitude += amplitude;
		value += getNoiseAt(Vec2f(x, y)) * amplitude;
		x *= 1.4; y *= 1.4;
		amplitude *= 0.5f;
	}

	return ((value / cumAmplitude) + 1) * 0.5f;
}

void Perlin2D::saveFractSum() {
	int imageWidth = mSize, imageHeight = mSize;
	float xRatio = 1.f / mSize;
	float yRatio = 1.f / mSize;
	float noiseFrequency = mFrequency;

	float* perlinData = (float*)calloc(imageHeight * imageWidth, sizeof(float));
	
	float max_noise = 0, min_noise = 10000;
	for (int j = 0; j < imageHeight; j++) {
		for (int i = 0; i < imageWidth; i++) {
			float x = i * xRatio * noiseFrequency;
			float y = j * yRatio * noiseFrequency;
			float amplitude = 1;
			float cumAmplitude = 0; 
			for (int l = 0; l < mLayers; l++) {
				cumAmplitude += amplitude;
				perlinData[j * imageWidth + i] += getNoiseAt(Vec2f(x, y)) * amplitude;
				x *= 1.4; y *= 1.4;
				amplitude *= 0.5f;
			}
			perlinData[j * imageWidth + i] = ((perlinData[j * imageWidth + i] / cumAmplitude) + 1) * 0.5f;
			if (perlinData[j * imageWidth + i] > max_noise) max_noise = perlinData[j * imageWidth + i];
			if (perlinData[j * imageWidth + i] < min_noise) min_noise = perlinData[j * imageWidth + i];
		}
	}

	for (int i = 0; i < imageHeight * imageWidth; i++) {
		std::cout << perlinData[i] << std::endl;
	}

	std::cout << max_noise << std::endl;
	std::cout << min_noise << std::endl;

	// output noise map to PPM
	std::ofstream ofs;
	ofs.open("noise2.ppm", std::ios::out | std::ios::binary);
	ofs << "P6\n" << imageWidth << " " << imageHeight << "\n255\n";
	for (unsigned k = 0; k < imageWidth * imageHeight; ++k) {
		unsigned char n = (unsigned char)(perlinData[k] * 255);
		ofs << n << n << n;
	}
	ofs.close();
	free(perlinData);
}



