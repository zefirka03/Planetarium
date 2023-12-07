#include "VAO.h"

AIR_NAMESPACE_BEGIN

VAO::VAO() {
	glGenVertexArrays(1, &m_vao);
	AIR_LOG("VAO [id=%d] inited", m_vao);
}


void VAO::bind() {
	glBindVertexArray(m_vao);
}


void VAO::unbind() {
	glBindVertexArray(0);
}


/*
	size - dimentions (2d = 2, 3d = 3, ...)
*/
VBO& VAO::pushVBO(GLuint index, GLuint size, GLsizei stride) {
	this->bind();
	VBO& tmp = m_vbo[index];
	tmp.bind();
	glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, (const void*)0);
	glEnableVertexAttribArray(index);
	this->unbind();
	return tmp;
}

VAO::~VAO() {
	AIR_LOG("VAO [id=%d] destructed", m_vao);
	glDeleteVertexArrays(1, &m_vao);
}

AIR_NAMESPACE_END