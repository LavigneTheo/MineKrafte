#include "TerrainMesh.h"
#include <iostream>

TerrainMesh::TerrainMesh(float* vertices, unsigned int vertices_count) {
	m_size = 6;

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	float arr2[] = {
	0.f, 0.f, 0.f,
	100.f, 0.f, 0.f,
	100.f, 0.f, 100.f,
	0.f, 0.f, 100.f
	};

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_vbo);

	glGenBuffers(1, &m_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_size * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices_count * sizeof(float), arr2, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindVertexArray(0);
}

void TerrainMesh::draw() {
	glBindVertexArray(m_vao);
	glEnableVertexAttribArray(0);

	glDrawElements(GL_TRIANGLES, m_size, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
}