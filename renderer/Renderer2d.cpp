#include "Renderer2d.h"

AIR_NAMESPACE_BEGIN

Renderer2d::Renderer2d() {
	m_data = std::vector<HostSpriteInstance>(7*100000);
	m_shader.load_from_string(
	std::string({ R"(~~vertex~~
#version 430 core
layout(location = 1) in vec2 position;
layout(location = 2) in vec2 texCoords;
layout(location = 3) in vec3 color;

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

	m_vao.pushVBO(0, 0, 1, sizeof(HostSpriteInstance), 0 * sizeof(GLfloat)).buffer(nullptr, 7*100000 * sizeof(HostSpriteInstance));
	m_vao.pushVBO(0, 1, 2, sizeof(HostSpriteInstance), 1 * sizeof(GLfloat));
	m_vao.pushVBO(0, 2, 2, sizeof(HostSpriteInstance), 3 * sizeof(GLfloat));
	m_vao.pushVBO(0, 3, 3, sizeof(HostSpriteInstance), 5 * sizeof(GLfloat));
}


void Renderer2d::draw(HostSpriteInstance&& sprite) {
	++m_data_texture_pointer[sprite.tex_id];
	m_data[cur_iterator] = sprite;
	++cur_iterator;
}


void Renderer2d::submit(C_Camera2d& camera) {
	m_shader.set_matrix4f(camera.get_projection(), "proj");
	std::sort(m_data.begin(), m_data.end(), [](HostSpriteInstance& a, HostSpriteInstance b) {
		return a.tex_id > b.tex_id;
	});
	size_t it = 0;
	for (auto sprites : m_data_texture_pointer) {
		glBindTexture(GL_TEXTURE_2D, sprites.first);
		m_vao.get_VBO(0).rebuffer(m_data.data(), it * sizeof(HostSpriteInstance), sprites.second * sizeof(HostSpriteInstance));
		m_vao.bind();
		m_shader.use();
		glDrawArrays(GL_TRIANGLES, 0, sprites.second);
		m_shader.unuse();
		m_vao.unbind();
		glBindTexture(GL_TEXTURE_2D, 0);
		it += sprites.second;
	}
	m_data_texture_pointer.clear();
	cur_iterator = 0;
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
		auto transform_pos = sprite.get_entity().get_component<C_Transform>().get_position();
		auto transform_size = sprite.get_size();
		Texture* texture = sprite.get_texture();

		m_renderer->draw({ (GLuint)*texture, {{transform_pos.x, transform_pos.y}, {0.0, 0.0}, {1.0, 0.0, 1.0} } });
		m_renderer->draw({ (GLuint)*texture, {{transform_pos.x + transform_size.x, transform_pos.y}, {1.0, 0.0}, {0.0, 1.0, 1.0} } });
		m_renderer->draw({ (GLuint)*texture, {{transform_pos.x + transform_size.x, transform_pos.y + transform_size.y}, {1.0, 1.0}, {1.0, 1.0, 0.0} } });
		m_renderer->draw({ (GLuint)*texture, {{transform_pos.x, transform_pos.y}, {0.0, 0.0}, {0.0, 1.0, 1.0} } });
		m_renderer->draw({ (GLuint)*texture, {{transform_pos.x + transform_size.x, transform_pos.y + transform_size.y}, {1.0, 1.0}, {1.0, 1.0, 0.0} } });
		m_renderer->draw({ (GLuint)*texture, {{transform_pos.x, transform_pos.y + transform_size.y}, {0.0, 1.0}, {1.0, 1.0, 0.0}} });
	});

	m_renderer->submit(*active_camera);
}


TextureManager& SRenderer2d::get_texture_manager() {
	return m_renderer->m_textureManager;
}

AIR_NAMESPACE_END