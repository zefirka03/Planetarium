#pragma once
#include "../core/AirCore.h"
#include "Transform.h"

AIR_NAMESPACE_BEGIN

class C_Sprite : public Component {
public:
	C_Sprite() = default;
	~C_Sprite() {};

	void set_size(glm::vec2 size);
	glm::vec2 get_size();

private:
	glm::vec2 m_size;
};


class P_Sprite : public Prefab<C_Transform, C_Sprite> {

};

AIR_NAMESPACE_END