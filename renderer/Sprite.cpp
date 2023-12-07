#include "Sprite.h"

AIR_NAMESPACE_BEGIN

glm::vec2 C_Sprite::get_size() {
	return m_size;
}


void C_Sprite::set_size(glm::vec2 size) {
	m_size = size;
}

AIR_NAMESPACE_END