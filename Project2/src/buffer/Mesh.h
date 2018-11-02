#pragma once
#include <inc/glew.h>
#include <iostream>
#include <vector>

struct MeshTexture {
	GLuint id;
	std::string type;
	std::string path;
};

struct MeshInfo {
	GLuint mVbo, mIbo, mVao, mSize = 0;
};

class Mesh {
	private :

	std::vector<MeshTexture> mTextures;
protected:
	MeshInfo mMeshInfo;
	Mesh() {}
public:
	Mesh(
		const float* vertices, 
		const int& vertices_count, 
		std::vector<unsigned int> indices,
		std::vector<MeshTexture>& textures
		);
	void draw();
	std::vector<MeshTexture> get_textures() const;

	void deleteMesh();
};
