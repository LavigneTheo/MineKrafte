#pragma once
#include <inc/assimp/Importer.hpp>
#include <inc/assimp/material.h>
#include <inc/assimp/scene.h>
#include <inc/assimp/postprocess.h>

#include <iostream>
#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Mesh.h"
#include "TextureCache.h"

using namespace std;

class Model
{
private:
	/*  Model Data  */
	vector<Mesh> m_meshes;
	string m_directory;
	vector<MeshTexture> textures_loaded;

	glm::mat4* m_model_matrix;
	glm::vec3* m_position;
	glm::vec3* m_rotation;
	glm::vec3* m_scale;

	bool m_process_model_matrix;

	/*  Functions   */
	void loadModel(string path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	vector<MeshTexture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);

	void process_model_matrix();

public:
	/*  Functions   */
	Model(const char* path);
	~Model();

	void draw();

	void set_position(const float x, const float y, const float z);
	void set_position(const glm::vec3& rotation);

	void rotate(const float x, const float y, const float z);
	void rotate(const glm::vec3& rotation);

	void scale(const float x, const float y, const float z);
	void scale(const glm::vec3& rotation);

	glm::vec3* get_position()const;
	glm::vec3* get_rotation()const;
	glm::vec3* get_scale()const;

	glm::mat4* get_model_matrix();
};