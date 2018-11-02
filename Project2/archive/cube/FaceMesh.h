#pragma once
#include "../buffer/Mesh.h"
#include "inc/glew.h"

typedef enum FaceType {
	FRONT, BOTTOM, RIGHT, LEFT, TOP, BACK
};

class FaceMesh {
private:
	unsigned int m_vbo, m_ibo, m_vao;
	unsigned int m_size;
	FaceType m_type;

public:
	FaceMesh(const FaceType& face_type);
	void bind_data(const float* vertices);
	void draw();
};