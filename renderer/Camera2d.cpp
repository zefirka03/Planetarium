#include "Camera2d.h"

AIR_NAMESPACE_BEGIN

C_Camera2d::C_Camera2d(float width, float height) {
	resize(width, height);
}


C_Camera2d::~C_Camera2d() {}


void C_Camera2d::resize(float width, float height) {
	m_projection = glm::ortho(0.f, width, height, 0.f);
}


glm::mat4 C_Camera2d::get_projection() {
	glm::mat4 tmp(1);
	C_Transform& transform = get_entity().get_component<C_Transform>();
	tmp = glm::rotate(tmp, transform.get_rotation(), glm::vec3(0, 0, 1));
	tmp = glm::scale(tmp, glm::vec3(transform.get_scale(), 1));
	tmp = glm::translate(tmp, glm::vec3(transform.get_position(), 0));
	return tmp * m_projection;
}

AIR_NAMESPACE_END