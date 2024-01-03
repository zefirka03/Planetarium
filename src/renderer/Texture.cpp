#include "Texture.h"

AIR_NAMESPACE_BEGIN

void TextureManager::load_texture(const char* path, const char* name) {
	if (m_texturesPath.find(path) == m_texturesPath.end()) {
		int szx, szy;
		unsigned char* image = SOIL_load_image(path, &szx, &szy, 0, SOIL_LOAD_RGBA);

		GLuint id;
		glGenTextures(1, &id);

		glBindTexture(GL_TEXTURE_2D, id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, szx, szy, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		Texture* tx = new Texture();
		tx->m_id = id;

		m_texturesPath.insert(std::make_pair(path, tx));
		m_texturesNames.insert(std::make_pair(name, tx));
	}
}


void TextureManager::load_texture_by_data(char* data, TextureParameters params, const char* name) {
	GLuint id;
	glGenTextures(1, &id);

	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, 0, params.internalFormat, params.sizeX, params.sizeY, 0, params.format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	Texture* tx = new Texture();
	tx->m_id = id;

	m_texturesNames.insert(std::make_pair(name, tx));
}


TextureManager::~TextureManager() {
	for (auto it = m_texturesNames.begin(); it != m_texturesNames.end(); ++it) {
		delete it->second;
	}
}


Texture* TextureManager::get_texture(const char* name) {
	return m_texturesNames[name];
}

AIR_NAMESPACE_END