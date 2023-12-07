#pragma once
#include "../core/AirCore.h"
#include "SOIL.h"

#define AIR_TEXTURE_LINEAR GL_LINEAR
#define AIR_TEXTURE_NEAREST GL_NEAREST
#define AIR_TEXTURE_RGB GL_RGB
#define AIR_TEXTURE_RGBA GL_RGBA
#define AIR_TEXTURE_R8 GL_R8
#define AIR_TEXTURE_RED GL_RED

AIR_NAMESPACE_BEGIN

struct TextureParameters {
	int sizeX = 100;
	int sizeY = 100;
	uint16_t internalFormat = AIR_TEXTURE_RGBA;
	uint16_t format = AIR_TEXTURE_RGBA;
};


class Texture {
public:
	operator GLuint() { return m_id; }
private:
	friend class TextureManager;
	GLuint m_id;
};


struct TextureManager {
	void load_texture(const char* path, const char* name);
	void load_texture_by_data(char* data, TextureParameters params, const char* name);
	Texture* get_texture(const char* name);
	~TextureManager();

private:
	std::unordered_map<std::string, Texture*> m_texturesPath;
	std::unordered_map<std::string, Texture*> m_texturesNames;
};

AIR_NAMESPACE_END