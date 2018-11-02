#pragma once

#include <inc/glew.h>

class TerrainMesh {
private:
	unsigned int m_vao, m_vbo, m_ibo, m_size;

public:

	TerrainMesh(float* vertices, unsigned int vertices_count);
	void draw();

};