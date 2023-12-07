#pragma once
#include "../core/AirCore.h"

AIR_NAMESPACE_BEGIN

class C_Transform : public Component {
public:
	C_Transform() = default;
	~C_Transform() {};

	void set_scale(glm::vec2 scale);
	void set_position(glm::vec2 position);
	void set_rotate(float angle);
	glm::vec2 get_position();
	glm::vec2 get_scale();
	float get_rotation();

private:
	glm::vec2 m_position = glm::vec2(0);
	glm::vec2 m_scale = glm::vec2(1);
	float m_rotation = 0;
};

AIR_NAMESPACE_END