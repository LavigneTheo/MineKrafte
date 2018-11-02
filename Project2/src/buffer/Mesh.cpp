#include "Mesh.h"

Mesh::Mesh(
	const float* vertices, 
	const int& vertices_count, 
	std::vector<unsigned int> indices,
	std::vector<MeshTexture>& textures
) {
	mMeshInfo.mSize = indices.size();
	mTextures = textures;

	glGenVertexArrays(1, &mMeshInfo.mVao);
	glBindVertexArray(mMeshInfo.mVao);

	glGenBuffers(1, &mMeshInfo.mVbo);
	glBindBuffer(GL_ARRAY_BUFFER, mMeshInfo.mVbo);

	glGenBuffers(1, &mMeshInfo.mIbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mMeshInfo.mIbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mMeshInfo.mSize * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	glBufferData(GL_ARRAY_BUFFER, vertices_count * sizeof(float), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),(void*) (6 * sizeof(float)));

	glBindVertexArray(0);
}

void Mesh::draw() {

	glBindVertexArray(mMeshInfo.mVao);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	for (unsigned int i = 0; i < mTextures.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, mTextures.at(i).id);
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mMeshInfo.mIbo);
	glDrawElements(GL_TRIANGLES, mMeshInfo.mSize, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	glBindVertexArray(0);
}

std::vector<MeshTexture> Mesh::get_textures() const {
	return mTextures;
}

void Mesh::deleteMesh() {
	glBindVertexArray(mMeshInfo.mVao);
	glDeleteBuffers(1, &mMeshInfo.mVbo);
	glDeleteVertexArrays(1, &mMeshInfo.mVao);
	glBindVertexArray(0);

}