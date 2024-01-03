#include "Transform.h"

AIR_NAMESPACE_BEGIN

void C_Transform::set_rotate(float angle) {
	m_rotation = angle;
}


void C_Transform::set_position(glm::vec2 position) {
	m_position = position;
}


void C_Transform::set_scale(glm::vec2 scale) {
	m_scale = scale;
}


glm::vec2 C_Transform::get_position() {
	return m_position;
}

glm::vec2 C_Transform::get_scale() {
	return m_scale;
}


float C_Transform::get_rotation() {
	return m_rotation;
}

AIR_NAMESPACE_END