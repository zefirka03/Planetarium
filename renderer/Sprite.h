#pragma once
#include "../core/AirCore.h"
#include "Transform.h"
#include "Texture.h"

AIR_NAMESPACE_BEGIN

class C_Sprite : public Component {
public:
	C_Sprite() = default;
	~C_Sprite() {};

	void set_size(glm::vec2 size);
	glm::vec2 get_size();
	void set_texture(Texture* texture);
	Texture* const get_texture() const;
	void set_texture_rect(glm::vec4 textureRect);
	glm::vec4 get_texture_rect();

private:
	glm::vec2 m_size;
	glm::vec4 m_textureRect;
	Texture* m_texture = nullptr;
};


class P_Sprite : public Prefab<C_Transform, C_Sprite> {};

AIR_NAMESPACE_END