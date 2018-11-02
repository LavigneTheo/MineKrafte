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

	for (int z = -(VIEW_RANGE - 1); z < VIEW_RANGE; z++) {
		for (int x = -(VIEW_RANGE - 1); x < VIEW_RANGE; x++) {
			insertChunk(Vec2f(xStart + x, zStart + z));
		}
	}

	init_shader();
}


void TerrainManager::draw() {

	m_shader.start();

	m_shader.load_mat4x4("view", *Camera::get_instance()->get_view_matrix());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mBlocSprite.id);

	for (const Chunk& chunk : mChunks)
		chunk.drawChunk();
	
	m_shader.stop();
}

void TerrainManager::init_shader() {
	m_shader.addVertexShader("shader/terrain/VS.glsl");
	m_shader.addFragmentShader("shader/terrain/FS.glsl");
	m_shader.linkProgram();
	m_shader.get_uniforms_location();

	std::string str("res/diamond2.png");
	mBlocSprite = TextureCache::getInstance()->load_texture(str);

	m_shader.start();
	glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)1400 / (float)1050, 0.1f, 1000.f);
	m_shader.load_mat4x4("projection", proj);
	m_shader.stop();
}

void TerrainManager::insertChunk(Vec2f position) {

	mChunks.push_back(Chunk(position));

	Vec2f positionsss[] = {
		Vec2f(1, 0),
		Vec2f(-1, 0),
		Vec2f(0, 1),
		Vec2f(0, -1)
	};
	/*for (const Vec2f& p : positionsss) {
		Chunk* c = getChunkAt(position.mx + p.mx, position.my + p.my);
		if (c != nullptr)
			c->rebuildMesh();

	}*/
}

void TerrainManager::onCameraMove() {
	glm::vec3 pos = *mCamera->get_position();
	
	if ((int)pos.x > (mCurrentChunk.mx + 1) * Chunk::WIDTH) {
		//t->start("MoveChuhnk(VIEW_RANGE5-!rebuild)_1-1");
		moveChunks(Vec2f(1, 0));
		//t->stop();
	}
	else if ((int)pos.x < mCurrentChunk.mx * Chunk::WIDTH) {
		//t->start("MoveChuhnk(VIEW_RANGE5-!rebuild)_1-1");
		moveChunks(Vec2f(-1, 0));
		//t->stop();
	}

	if (pos.z > (mCurrentChunk.my + 1)* Chunk::DEPTH) {
		//t->start("MoveChuhnk(VIEW_RANGE5-!rebuild)_1-1");
		moveChunks(Vec2f(0, 1));
		//t->stop();
	}
	else if (pos.z < mCurrentChunk.my * Chunk::DEPTH) {
		//t->start("MoveChuhnk(VIEW_RANGE5-!rebuild)_1-1");
		moveChunks(Vec2f(0, -1));
		//t->stop();
	}
}

void TerrainManager::moveChunks(const Vec2f& direction) {

	if (direction.my == 0) {
		int topCorner = mCurrentChunk.my - (VIEW_RANGE - 1);
		int bottomCorner = mCurrentChunk.my + (VIEW_RANGE - 1);
		
		for (int z = topCorner; z <= bottomCorner; z++) {
			//t.start("insert");
			insertChunk(Vec2f(
				direction.mx > 0 ? mCurrentChunk.mx + VIEW_RANGE : mCurrentChunk.mx - VIEW_RANGE,
				z
			));
			//t.stop();
			removeChunk(
				direction.mx < 0 ? mCurrentChunk.mx + (VIEW_RANGE - 1) : mCurrentChunk.mx - (VIEW_RANGE - 1),
				z
			);
		}
	}
	else {
		int leftCorner = mCurrentChunk.mx - (VIEW_RANGE - 1);
		int rightCorner = mCurrentChunk.mx + (VIEW_RANGE - 1);
		
		for (int x = leftCorner; x <= rightCorner; x++) {
			//t.start("insert");
			insertChunk(Vec2f(
				x,
				direction.my > 0 ? mCurrentChunk.my + VIEW_RANGE : mCurrentChunk.my - VIEW_RANGE
			));
			//t.stop();
			removeChunk(
				x,
				direction.my < 0 ? mCurrentChunk.my + (VIEW_RANGE - 1) : mCurrentChunk.my - (VIEW_RANGE - 1)
			);
			
		}
	}

	mCurrentChunk.mx += direction.mx;
	mCurrentChunk.my += direction.my;
}

void TerrainManager::removeChunk(const int& x, const int& y) {
	
	int index = getChunkIndex(x, y);
	if (index != -1) {
		Chunk& c = mChunks.at(index);
		c.freeChunk();
		std::iter_swap(mChunks.begin() + index, mChunks.begin() + (mChunks.size() - 1));
		mChunks.erase(mChunks.begin() + (mChunks.size() - 1));
	}
}
