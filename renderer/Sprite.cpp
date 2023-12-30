#include "Sprite.h"

AIR_NAMESPACE_BEGIN

glm::vec2 C_Sprite::get_size() {
	return m_size;
}


void C_Sprite::set_size(glm::vec2 size) {
	m_size = size;
	m_is_dirty = true;
}


void C_Sprite::set_texture(Texture* texture) {
	m_texture = texture;
	m_is_dirty = true;
}


Texture* const C_Sprite::get_texture() const {
	return m_texture;
}


void C_Sprite::set_texture_rect(glm::vec4 textureRect) {
	m_textureRect = textureRect;
	m_is_dirty = true;
}


HostSpriteInstance& const C_Sprite::get_instance() {
	if (m_is_dirty) {
		m_is_dirty = false;
		auto transform_pos = get_entity().get_component<C_Transform>().get_position();
		auto transform_size = get_size();

		m_last_sprite_instance = {
		{{
			{ {transform_pos.x, transform_pos.y}, {0.0, 0.0}, {1.0, 0.0, 1.0} },
			{ {transform_pos.x + transform_size.x, transform_pos.y}, {1.0, 0.0}, {0.0, 1.0, 1.0} } ,
			{ {transform_pos.x + transform_size.x, transform_pos.y + transform_size.y}, {1.0, 1.0}, {1.0, 1.0, 0.0} },
			{ {transform_pos.x, transform_pos.y}, {0.0, 0.0}, {0.0, 1.0, 1.0} } ,
			{ {transform_pos.x + transform_size.x, transform_pos.y + transform_size.y}, {1.0, 1.0}, {1.0, 1.0, 0.0} },
			{ {transform_pos.x, transform_pos.y + transform_size.y}, {0.0, 1.0}, {1.0, 1.0, 0.0} }
		}}, (GLuint)*m_texture};
	}
	return m_last_sprite_instance;
}


glm::vec4 C_Sprite::get_texture_rect() {
	return m_textureRect;
}


bool C_Sprite::is_dirty() {
	return m_is_dirty;
}

AIR_NAMESPACE_END