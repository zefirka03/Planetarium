#pragma once
#include "../core/AirCore.h"
#include "Camera2d.h"
#include "Sprite.h"
#include "Texture.h"

#include <unordered_map>
#include <vector>

AIR_NAMESPACE_BEGIN

class Renderer2d {
	struct RenderStats;
public:
	struct SpriteInstance {
		glm::vec2 position;
		glm::vec2 texCoords;
		glm::vec3 color;
	};

	struct HostSpriteInstance {
		SpriteInstance data;
		GLuint tex_id;
	};

	Renderer2d(uint64_t max_sprites_count = 150000);
	~Renderer2d() {}
	
	void draw(HostSpriteInstance&& sprite);
	void submit(C_Camera2d& camera);
	RenderStats const& get_stats() const;

private:
	friend class S_Renderer2d;
	struct RenderStats {
		uint64_t video_memory_allocated = 0;
		uint64_t video_memory_use = 0;
		uint16_t batch_count = 0;
		uint64_t sprites_rendered = 0;
	} m_render_stats;

	std::unordered_map<GLuint, size_t> m_data_texture_pointer;
	std::vector<HostSpriteInstance> m_data;
	Shader m_shader;
	VAO m_vao;
	TextureManager m_textureManager;

	size_t m_cur_size = 0;
};


class S_Renderer2d : public System {
public:
	S_Renderer2d() { m_renderer = new Renderer2d(); };
	~S_Renderer2d() {};

	void start() override;
	void update() override;

	TextureManager& get_texture_manager();
	Renderer2d::RenderStats const& get_stats() const;
private:
	Renderer2d* m_renderer = nullptr;
};

AIR_NAMESPACE_END