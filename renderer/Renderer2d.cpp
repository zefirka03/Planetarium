#include "Renderer2d.h"

AIR_NAMESPACE_BEGIN

void SRenderer2d::start() {
	AIR_LOG("RENDERER2d start");
}


void SRenderer2d::update() {
	auto& reg = ECS::registry;

	C_Camera2d* active_camera = nullptr;
	reg.view<C_Camera2d>().each([&](C_Camera2d& camera) {
		active_camera = &camera;
	});


	std::vector<GLfloat> data = { -0.5f, -0.5f, 0.0f,
						 0.5f, -0.5f, 0.0f,
						 0.0f, 0.5f, 0.0f };
	VAO vao;
	vao.pushVBO(0, 3, 0).buffer(data.data(), data.size() * sizeof(GLfloat));

	Shader sh;
	sh.loadFromString(
std::string({R"(~~vertex~~
#version 430 core
layout(location = 0) in vec3 position;
void main() {
	gl_Position = vec4(position, 1.0); 
}

~~fragment~~
#version 430 core

out vec4 out_color;

void main() {
	// out_color = f_color;
	out_color = vec4(0.8, 0.8, 0, 1);
}
)"}).c_str(),
		AIR_SHADER_VF);

	sh.use();
	vao.bind();
	glDrawArrays(GL_TRIANGLES, 0, 3);
	vao.unbind();
	sh.unuse();
}

AIR_NAMESPACE_END