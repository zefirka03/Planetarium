#pragma once
#include "../core/ogl_common.h"
#include "../core/AirUtils.h"
#include "../core/ECS.h"

#include "Transform.h"

AIR_NAMESPACE_BEGIN

class C_Camera2d : public Component {
public:
	C_Camera2d() {};
	C_Camera2d(float width, float height);
	~C_Camera2d();

	void resize(float width, float height);
	glm::mat4 get_projection();

private:
	glm::mat4 m_projection;
};


class P_Camera2d : public Prefab<C_Transform, C_Camera2d> {
public:
	P_Camera2d() {};
};

AIR_NAMESPACE_END
