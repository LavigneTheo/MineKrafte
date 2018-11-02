#pragma once
#include "../buffer/Mesh.h"
#include "glm/common.hpp"
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <iostream>
#include <vector>
#include "FaceMesh.h"
#include "../buffer/TextureCache.h"

//#include "Vertices.h"

class Cube {
private:
	MeshTexture m_texture;

	glm::vec3 m_chunk_position;
	glm::vec3 m_world_position;

	bool m_solid;
	bool m_visible = false;

	unsigned int m_vbo, m_ibo, m_vao;
	unsigned int m_size;
public:
	Cube(const glm::vec2& chunk_postion, const glm::vec3 chunk_position, const bool& solid);

	bool is_solid() const;
	bool is_visible() const;

	void activate();
	void disable();

	void draw();
	glm::vec3 get_world_position();
};