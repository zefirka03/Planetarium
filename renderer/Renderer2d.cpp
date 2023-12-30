#include "Renderer2d.h"

AIR_NAMESPACE_BEGIN

Renderer2d::Renderer2d(uint64_t max_sprites_count) {
	m_data = std::vector<SpriteInstance>(max_sprites_count);
	m_shader.load_from_string(
	std::string({ R"(~~vertex~~
#version 430 core
layout(location = 0) in vec2 position;
layout(location = 1) in vec2 texCoords;
layout(location = 2) in vec3 color;

uniform mat4 proj;
out vec3 o_color;
out vec2 o_texCoords;

void main() {
	gl_Position = proj * vec4(position, 0.0, 1.0); 
	o_color = color;
	o_texCoords = texCoords;
}
 
~~fragment~~
#version 430 core

in vec3 o_color;
in vec2 o_texCoords;
out vec4 out_color;
uniform vec4 col;
uniform sampler2D tex; 

void main() {
	// out_color = f_color;
	//out_color = vec4(o_color,1);
	out_color = texture(tex, o_texCoords);
}
)" }).c_str(),
AIR_SHADER_VF);

	m_vao.pushVBO(0, 0, 2, sizeof(SpriteInstance::Vertex), 0 * sizeof(GLfloat)).buffer(nullptr, max_sprites_count * sizeof(SpriteInstance));
	m_vao.pushVBO(0, 1, 2, sizeof(SpriteInstance::Vertex), 2 * sizeof(GLfloat));
	m_vao.pushVBO(0, 2, 3, sizeof(SpriteInstance::Vertex), 4 * sizeof(GLfloat));

	m_render_stats.video_memory_allocated = max_sprites_count * sizeof(SpriteInstance);
}


void Renderer2d::draw(HostSpriteInstance&& sprite) {
	++m_data_texture_pointer[sprite.tex_id];
	m_data[m_cur_size++] = sprite.data;
}


void Renderer2d::draw(HostSpriteInstance const& sprite) {
	++m_data_texture_pointer[sprite.tex_id];
	m_data[m_cur_size++] = sprite.data;
}


void Renderer2d::submit(C_Camera2d& camera) {
	// reset render stats
	m_render_stats.batch_count = m_data_texture_pointer.size();
	m_render_stats.video_memory_use = m_cur_size * sizeof(SpriteInstance);
	m_render_stats.sprites_rendered = m_cur_size;

	// render logic
	m_shader.set_matrix4f(camera.get_projection(), "proj");

	size_t it = 0;

	m_vao.get_VBO(0).rebuffer(m_data.data(), 0, m_cur_size * sizeof(SpriteInstance));
	for (auto sprites : m_data_texture_pointer) {
		glBindTexture(GL_TEXTURE_2D, sprites.first);
		m_vao.bind();
		m_shader.use();
		glDrawArrays(GL_TRIANGLES, it*6, sprites.second * 6);
		m_shader.unuse();
		m_vao.unbind();
		glBindTexture(GL_TEXTURE_2D, 0);
		it += sprites.second;
	}
	m_data_texture_pointer.clear();
	m_cur_size = 0;
}

Renderer2d::RenderStats const& Renderer2d::get_stats() const {
	return m_render_stats;
}


/////////////////////////


void S_Renderer2d::start() {
	AIR_LOG("RENDERER_2D start");
}


void S_Renderer2d::update() {
	auto& reg = ECS::registry;

	C_Camera2d* active_camera = nullptr;
	reg.view<C_Camera2d>().each([&](C_Camera2d& camera) {
		active_camera = &camera;
	});

	reg.sort<C_Sprite>([](const auto& lhs, const auto& ths) {
		return (GLuint)*lhs.get_texture() < (GLuint)*ths.get_texture();
	});

	reg.view<C_Sprite>().each([&](C_Sprite& sprite) {
		m_renderer->draw(sprite.get_instance());
	});

	m_renderer->submit(*active_camera);
}


TextureManager& S_Renderer2d::get_texture_manager() {
	return m_renderer->m_textureManager;
}


Renderer2d::RenderStats const& S_Renderer2d::get_stats() const {
	return m_renderer->get_stats();
}


AIR_NAMESPACE_END