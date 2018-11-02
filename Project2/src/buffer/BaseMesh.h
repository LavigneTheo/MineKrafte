#pragma once

class BaseMesh {
private:
	unsigned int m_vbo, m_ibo, m_vao;
	unsigned int m_size;
public:
	virtual void draw() = 0;

};
