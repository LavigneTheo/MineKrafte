#pragma once
#include "../manager/EntityManager.h"
#include "../manager/TerrainManager.h"
#include "TimeTester.h"

class Renderer {
private:
	EntityManager m_entity_manager;
	TerrainManager m_terrain_manager;
	TimeTester tester;
public:
	Renderer();
	~Renderer();

	void render();
	void update();
};