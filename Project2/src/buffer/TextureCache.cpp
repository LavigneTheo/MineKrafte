#include "TextureCache.h"

TextureCache* TextureCache::INSTANCE = nullptr;

TextureCache* TextureCache::getInstance() {
if (INSTANCE == nullptr)
	INSTANCE = new TextureCache;
return INSTANCE;
}

TextureCache::~TextureCache() {
delete INSTANCE;
}


MeshTexture TextureCache::load_texture(std::string& path) {

	std::map<std::string, unsigned int>::iterator texture_id = m_textures.find(path);

	if (texture_id == m_textures.end()) {
		return load_texture_from_file(path);
	} 
	MeshTexture texture;
	texture.id = texture_id->second;
	return texture;

	
}

MeshTexture TextureCache::load_texture_from_file(std::string& path) {
	MeshTexture texture;

	//stbi_set_flip_vertically_on_load(1);
	int m_width, m_height, m_bpp;
	unsigned char* ptr = stbi_load(path.c_str(), &m_width, &m_height, &m_bpp, 4);

	glGenTextures(1, &texture.id);
	glBindTexture(GL_TEXTURE_2D, texture.id);

	m_textures.emplace(path, texture.id);

	/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);*/

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, ptr);

	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -0.3);

	glBindTexture(GL_TEXTURE_2D, 0);

	if (ptr)
		stbi_image_free(ptr);

	return texture;
}
