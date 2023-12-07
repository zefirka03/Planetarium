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


	std::vector<GLfloat> data = { 0, 0, 0.0f,
						 500.f,0, 0.0f,
						 250.f, 500.f, 0.0f };
	VAO vao;
	vao.pushVBO(0, 3, 0).buffer(data.data(), data.size() * sizeof(GLfloat));

	Shader sh;
	sh.load_from_string(
std::string({R"(~~vertex~~
#version 430 core
layout(location = 0) in vec3 position;

uniform mat4 proj;

void main() {
	gl_Position = proj * vec4(position.xy, 0.0, 1.0); 
	gl_Position.z = 0.0;
}
 
~~fragment~~
#version 430 core

out vec4 out_color;
uniform vec4 col;

void main() {
	// out_color = f_color;
	out_color = col;
}
)"}).c_str(),
		AIR_SHADER_VF);


	sh.setMatrix4f(active_camera->get_projection(), "proj");
	sh.setVector4f(glm::vec4(0.9, 0.9, 0, 1), "col");
	vao.bind();
	sh.use();
	glDrawArrays(GL_TRIANGLES, 0, 3);
	sh.unuse();
	vao.unbind();
}

AIR_NAMESPACE_END