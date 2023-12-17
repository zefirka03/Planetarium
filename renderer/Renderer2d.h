#pragma once
#include "../core/AirCore.h"
#include "Camera2d.h"
#include "Sprite.h"
#include "Texture.h"

#include <unordered_map>
#include <vector>

AIR_NAMESPACE_BEGIN

class Renderer2d {
public:
	struct SpriteInstance {
		glm::vec2 position;
		glm::vec2 texCoords;
		glm::vec3 color;
	};

	struct HostSpriteInstance {
		GLuint tex_id;
		SpriteInstance data;
	};

	Renderer2d();
	~Renderer2d() {}
	
	void draw(HostSpriteInstance&& sprite);
	void submit(C_Camera2d& camera);

private:
	friend class SRenderer2d;
	std::unordered_map<GLuint, size_t> m_data_texture_pointer;
	std::vector<HostSpriteInstance> m_data;
	Shader m_shader;
	VAO m_vao;
	TextureManager m_textureManager;

	size_t cur_iterator = 0;
};


class SRenderer2d : public System {
public:
	SRenderer2d() { m_renderer = new Renderer2d(); };
	~SRenderer2d() {};

	void start() override;
	void update() override;

	TextureManager& get_texture_manager();
private:
	Renderer2d* m_renderer = nullptr;
};

AIR_NAMESPACE_END