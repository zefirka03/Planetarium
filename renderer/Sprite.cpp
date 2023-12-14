#include "Sprite.h"

AIR_NAMESPACE_BEGIN

glm::vec2 C_Sprite::get_size() {
	return m_size;
}


void C_Sprite::set_size(glm::vec2 size) {
	m_size = size;
}


void C_Sprite::set_texture(Texture* texture) {
	m_texture = texture;
}


Texture* C_Sprite::get_texture() {
	return m_texture;
}


void C_Sprite::set_texture_rect(glm::vec4 textureRect) {
	m_textureRect = textureRect;
}


glm::vec4 C_Sprite::get_texture_rect() {
	return m_textureRect;
}

AIR_NAMESPACE_END