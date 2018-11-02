#include "Cube.h"

float cube_vertices[] = {
	// front
	-.5f, -.5f,  .5f,
	 .5f, -.5f,  .5f,
	 .5f,  .5f,  .5f,
	-.5f,  .5f,  .5f,
	// back
	-.5f, -.5f, -.5f,
	 .5f, -.5f, -.5f,
	 .5f,  .5f, -.5f,
	-.5f,  .5f, -.5f,
};

/* init_resources */
unsigned int cube_indices[] = {
	// front
	2, 1, 0,
	0, 3, 2,
	// right
	6, 5, 1,
	1, 2, 6,
	// back
	5, 6, 7,
	7, 4, 5,
	// left
	3, 0, 4,
	4, 7, 3,
	// bottom
	1, 5, 4,
	4, 0, 1,
	// top
	6, 2, 3,
	3, 7, 6,
};

unsigned int face_indices[] = {
	0, 1, 2,
	2, 3, 1
};

float front_face[] = {
	0.f, 0.f, 0.f,   0, 0,
	1.f, 0.f, 0.f,   1, 0,
	1.f, 1.0f, 1.f,  1, 1,
	0.f, 1.f, 0.f,   0, 1
};

float right_face[] = {
	1.f, 0.f, 0.f,
	1.f, 0.f, 1.f,
	1.f, 1.0f, 1.f,
	1.f, 1.f, 0.f
};

float left_face[] = {
	0.f, 0.f, 0.f,
	0.f, 0.f, 1.f,
	0.f, 1.0f, 1.f,
	0.f, 1.f, 0.f
};

float bottom_face[] = {
	0.f, 0.f, 0.f,
	1.f, 0.f, 0.f,
	1.f, 1.0f, 0.f,
	0.f, 1.f, 0.f
};

float top_face[] = {
	0.f, 1.f, 0.f,
	1.f, 1.f, 0.f,
	1.f, 1.0f, 1.f,
	0.f, 1.f, 1.f
};

float back_face[] = {
	0.f, 0.f, 1.f,
	1.f, 0.f, 1.f,
	1.f, 1.0f, 1.f,
	0.f, 1.f, 1.f
};

Cube::Cube(const glm::vec2& chunk_postion, const glm::vec3 chunk_position, const bool& solid) : 
	m_solid(solid) {
	std::string str("res/grass.png");
	m_texture = TextureCache::get_texture_cache()->load_texture(str);
	m_world_position = glm::vec3(
		chunk_position.x + chunk_postion.x * 16,
		chunk_position.y,
		-chunk_position.z + -chunk_postion.y * 16
	);
	
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	glGenBuffers(1, &m_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);

	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

	//Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//Texture Coord
	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	glBindVertexArray(0);
}

bool Cube::is_solid() const{
	return m_solid;
}

bool Cube::is_visible() const{
	return m_visible;
}

void Cube::activate() {
	m_visible = true;
}
void Cube::disable() {
	m_visible = false;
}

glm::vec3 Cube::get_world_position() {
	return m_world_position;
}

void Cube::draw() {

	glBindVertexArray(m_vao);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture.id);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	
	glBindVertexArray(0);
}




