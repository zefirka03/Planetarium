#pragma once
#include "ogl_common.h"
#include "AirUtils.h"
#include "VBO.h"
#include <unordered_map>

AIR_NAMESPACE_BEGIN

class VAO {
public:
	VAO();
	~VAO();
	
	void bind();
	void unbind();
	VBO& pushVBO(GLuint index, GLuint size, GLsizei stride);
private:
	std::unordered_map<size_t, VBO> m_vbo;
	GLuint m_vao;
};

AIR_NAMESPACE_END