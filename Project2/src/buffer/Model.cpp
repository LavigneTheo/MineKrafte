
#include "Model.h"

Model::Model(const char* path) {
	loadModel(path);
	m_model_matrix = new glm::mat4;
	m_position = new glm::vec3(0, 0, -50.0f);
	m_rotation = new glm::vec3(0, 0, 0);
	m_scale = new glm::vec3(1, 1, 1);
	process_model_matrix();
}

Model::~Model() {
	delete m_model_matrix;
	delete m_position;
	delete m_rotation;
	delete m_scale;

}

void Model::loadModel(string path) {

	Assimp::Importer import;
	const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
		return;
	}
	m_directory = path.substr(0, path.find_last_of('/'));

	processNode(scene->mRootNode, scene);

}
void Model::processNode(aiNode *node, const aiScene *scene) {
	// process all the node's meshes (if any)
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		m_meshes.push_back(processMesh(mesh, scene));
	}
	// then do the same for each of its children
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}
Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene) {

	vector<unsigned int> indices;
	vector<MeshTexture> textures;
	
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	float* data = (float*)calloc(mesh->mNumVertices * 8, sizeof(float));
	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		*(data + i * 8) = mesh->mVertices[i].x;
		*(data + i * 8 + 1) = mesh->mVertices[i].y;
		*(data + i * 8 + 2) = mesh->mVertices[i].z;

		*(data + i * 8 + 3) = mesh->mNormals[i].x;
		*(data + i * 8 + 4) = mesh->mNormals[i].y;
		*(data + i * 8 + 5) = mesh->mNormals[i].z;

		*(data + i * 8 + 6) = mesh->mTextureCoords[0][i].x;
		*(data + i * 8 + 7) = mesh->mTextureCoords[0][i].y;
	}

	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
		vector<MeshTexture> diffuseMaps = loadMaterialTextures(material,aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		//vector<MeshTexture> specularMaps = loadMaterialTextures(material,aiTextureType_SPECULAR, "texture_specular");
		//textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}

	return Mesh(data, mesh->mNumVertices * 8, indices, textures);
}
vector<MeshTexture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName) {
	vector<MeshTexture> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		std::string type = str.C_Str();
		std::string path;
		path.append(m_directory).append("/").append(type);
		
		MeshTexture texture = TextureCache::getInstance()->load_texture(path);
		texture.path = str.C_Str();
		//texture.type = typeName;
		textures.push_back(texture);
		textures_loaded.push_back(texture); // add to loaded textures
		
	}
	return textures;
}
void Model::draw() {
	for (unsigned int i = 0; i < m_meshes.size(); i++)
		m_meshes[i].draw();
}


void Model::set_position(const float x, const float y, const float z) {

}
void Model::set_position(const glm::vec3& position) {
	m_position->x = position.x;
	m_position->y = position.y;
	m_position->z = position.z;
	m_process_model_matrix = true;
}

void Model::rotate(const float x, const float y, const float z) {
	m_rotation->x += x;
	m_rotation->y += y;
	m_rotation->z += z;
	m_process_model_matrix = true;
}
void Model::rotate(const glm::vec3& rotation) {
	m_rotation->x += rotation.x;
	m_rotation->y += rotation.y;
	m_rotation->z += rotation.z;
	m_process_model_matrix = true;
}

void Model::scale(const float x, const float y, const float z) {
	m_scale->x += x;
	m_scale->y += y;
	m_scale->z += z;
	m_process_model_matrix = true;
	m_process_model_matrix = true;
}
void Model::scale(const glm::vec3& rotation) {

	m_process_model_matrix = true;
}

void set_identity(glm::mat4* mat);

void Model::process_model_matrix() {
	m_process_model_matrix = false;

	set_identity(m_model_matrix);
	*m_model_matrix = glm::translate(*m_model_matrix, *m_position);

	*m_model_matrix = glm::rotate(*m_model_matrix, m_rotation->x, glm::vec3(1.0f, 0.0f, 0.0f));
	*m_model_matrix = glm::rotate(*m_model_matrix, m_rotation->y, glm::vec3(0.0f, 1.0f, 0.0f));
	*m_model_matrix = glm::rotate(*m_model_matrix, m_rotation->z, glm::vec3(0.0f, 0.0f, 1.0f));
}

glm::mat4* Model::get_model_matrix() {
	if (m_process_model_matrix)
		process_model_matrix();
	return m_model_matrix;
}

void set_identity(glm::mat4* mat) {
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			if (x != y)
				(*mat)[y][x] = 0;
			else
				(*mat)[y][x] = 1;
		}
	}
}

glm::vec3* Model::get_position()const {
	return m_position;
}
glm::vec3* Model::get_rotation()const {
	return m_rotation;
}
glm::vec3* Model::get_scale()const {
	return m_scale;
}