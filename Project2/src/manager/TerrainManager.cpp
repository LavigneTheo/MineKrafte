#include "TerrainManager.h"

int TerrainManager::vertexCount = 0;


TerrainManager::TerrainManager() : CameraSubscriber() {

	Chunk::mTerrainManager = this;
		
	glm::vec3 pos = *mCamera->get_position();
	
	int xStart = ((int)pos.x / Chunk::WIDTH) - ((int)pos.x < 0);
	int zStart = (int)pos.z / Chunk::DEPTH - ((int)pos.z < 0);

	mCurrentChunk.mx = xStart; mCurrentChunk.my = zStart;

	mRightTheshhold = (xStart + 1) * Chunk::WIDTH;
	mLeftThreshold = xStart * Chunk::WIDTH;
	mFrontThreshold = zStart * Chunk::DEPTH;
	mBackThreshold = (zStart + 1)* Chunk::DEPTH;
	
	for (int z = 0; z < VIEW_RANGE; z++) {
		for (int x = 0; x < VIEW_RANGE; x++) {
			insertChunk(Vec2(xStart + x, zStart + z));
			insertChunk(Vec2(xStart - x, zStart + z));

			insertChunk(Vec2(xStart + x, zStart - z));
			insertChunk(Vec2(xStart - x, zStart - z));
		}
	}
	
	init_shader();
}

TerrainManager::~TerrainManager() {	

}

void TerrainManager::draw() {

	m_shader.start();

	m_shader.load_mat4x4("view", *Camera::get_instance()->get_view_matrix());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mBlocSprite.id);

	for (auto const& chunk : mChunks)
		((Chunk)chunk.second).drawChunk();
	
	m_shader.stop();
}

void TerrainManager::init_shader() {
	m_shader.addVertexShader("shader/terrain/VS.glsl");
	m_shader.addFragmentShader("shader/terrain/FS.glsl");
	m_shader.linkProgram();
	m_shader.get_uniforms_location();

	std::string str("res/diamond2.png");
	mBlocSprite =  TextureCache::getInstance()->load_texture(str);

	m_shader.start();
	glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)1400/ (float)1050, 0.1f, 1000.f);
	m_shader.load_mat4x4("projection", proj);
	m_shader.stop();
}

void TerrainManager::insertChunk(const Vec2 position) {
	mChunks.emplace(
		position,
		Chunk(position.mx, position.my)
	);
	Vec2 positionsss[] = {
		Vec2(1, 0),
		Vec2(-1, 0),
		Vec2(0, 1),
		Vec2(0, -1)
	};
	for (const Vec2& p : positionsss) {
		Chunk* c = getChunkAt(Vec2(position.mx + p.mx, position.my + p.my));
		if (c != nullptr)
			c->rebuildMesh();

	}
}

void TerrainManager::onCameraMove() {
	glm::vec3 pos = *mCamera->get_position();
	
	if ((int)pos.x > (mCurrentChunk.mx + 1) * Chunk::WIDTH) {
		moveChunks(Vec2(1, 0));
	} else if ((int)pos.x < mCurrentChunk.mx * Chunk::WIDTH) {
		moveChunks(Vec2(-1, 0));
	}

	if (pos.z > (mCurrentChunk.my + 1)* Chunk::DEPTH) {
		moveChunks(Vec2(0, 1));
	}
	else if (pos.z < mCurrentChunk.my * Chunk::DEPTH) {
		moveChunks(Vec2(0, -1));
	}
}

void TerrainManager::moveChunks(const Vec2& direction) {

	if (direction.my == 0) {
		int topCorner = mCurrentChunk.my - (VIEW_RANGE - 1);
		int bottomCorner = mCurrentChunk.my + (VIEW_RANGE - 1);

		for (int z = topCorner; z <= bottomCorner; z++) {
			insertChunk(Vec2(
				direction.mx > 0 ? mCurrentChunk.mx + VIEW_RANGE : mCurrentChunk.mx - VIEW_RANGE,
				z
			));
			removeChunk(Vec2(
				direction.mx < 0 ? mCurrentChunk.mx + (VIEW_RANGE -1 ) : mCurrentChunk.mx - (VIEW_RANGE - 1),
				z
			));
		}
	}
	else {
		int leftCorner = mCurrentChunk.mx - (VIEW_RANGE - 1);
		int rightCorner = mCurrentChunk.mx + (VIEW_RANGE - 1);
		
		for (int x = leftCorner; x <= rightCorner; x++) {
			insertChunk(Vec2(
				x,
				direction.my > 0 ? mCurrentChunk.my + VIEW_RANGE : mCurrentChunk.my - VIEW_RANGE
			));
			removeChunk(Vec2(
				x,
				direction.my < 0 ? mCurrentChunk.my + (VIEW_RANGE - 1) : mCurrentChunk.my - (VIEW_RANGE - 1)
			));
		}
	}

	mCurrentChunk.mx += direction.mx;
	mCurrentChunk.my += direction.my;
}

void TerrainManager::removeChunk(const Vec2& position) {
	Chunk* c = getChunkAt(position);

	if (c != nullptr) {
		c->freeChunk();
		mChunks.erase(position);
	}
}
