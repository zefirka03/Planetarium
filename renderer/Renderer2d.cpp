#include "Renderer2d.h"

AIR_NAMESPACE_BEGIN

Renderer2d::Renderer2d() {
	m_shader.load_from_string(
	std::string({ R"(~~vertex~~
#version 430 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;

uniform mat4 proj;
out vec3 o_color;

void main() {
	gl_Position = proj * vec4(position, 1.0); 
	o_color = color;
}
 
~~fragment~~
#version 430 core

in vec3 o_color;
out vec4 out_color;
uniform vec4 col;

void main() {
	// out_color = f_color;
	out_color = vec4(o_color,1);
}
)" }).c_str(),
AIR_SHADER_VF);

	m_vao.pushVBO(0, 0, 3, 6 * sizeof(GLfloat), 0 * sizeof(GLfloat)).buffer(nullptr, 0);
	m_vao.pushVBO(0, 1, 3, 6 * sizeof(GLfloat), 3 * sizeof(GLfloat));
}


void Renderer2d::draw(SpriteInstance&& sprite, Texture* texture) {
	if (texture) {
		m_data[0].emplace_back(sprite);
	} else {
		m_data[(GLuint)texture].emplace_back(sprite);
	}
}


void Renderer2d::submit(C_Camera2d& camera) {
	m_shader.set_matrix4f(camera.get_projection(), "proj");
	for (auto sprites : m_data) {
		m_vao.get_VBO(0).buffer(sprites.second.data(), sprites.second.size() * sizeof(SpriteInstance));
		m_vao.bind();
		m_shader.use();
		glDrawArrays(GL_TRIANGLES, 0, sprites.second.size());
		m_shader.unuse();
		m_vao.unbind();
	}

	m_data.clear();
}


/////////////////////////


void SRenderer2d::start() {
	AIR_LOG("RENDERER2d start");
}


void SRenderer2d::update() {
	auto& reg = ECS::registry;

	C_Camera2d* active_camera = nullptr;
	reg.view<C_Camera2d>().each([&](C_Camera2d& camera) {
		active_camera = &camera;
	});

	reg.view<C_Sprite>().each([&](C_Sprite& sprite) {
		auto transform = sprite.get_entity().get_component<C_Transform>().get_position();
		m_renderer->draw({ {transform.x, transform.y, 0.0}, {1.0, 0.0, 1.0} });
		m_renderer->draw({ {transform.x+100, transform.y, 0.0}, {0.0, 1.0, 1.0} });
		m_renderer->draw({ {transform.x+50, transform.y+100, 0.0}, {1.0, 1.0, 0.0} });
	});

	m_renderer->submit(*active_camera);
}


TextureManager& SRenderer2d::get_texture_manager() {
	return m_renderer->m_textureManager;
}

AIR_NAMESPACE_END