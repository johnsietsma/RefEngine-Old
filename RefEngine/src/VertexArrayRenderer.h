#pragma once

#include "gl_core_4_1.h"

#include <glm/glm.hpp>

class VertexArrayRenderer
{
public:
	VertexArrayRenderer();

	bool Init(GLuint vertexDataSize, GLuint numberOfVerts, const GLfloat* vertexData, const char* vertexShaderFileName, const char* fragmentShaderFileName);
	void Render(const glm::mat4& projView) const;
	void Destroy();
	bool InitShaders(const char* vertexShaderFileName, const char* fragmentShaderFileName);

private:
	void InitVertexBuffer(size_t vertexDataSize, const GLfloat* vertexData);

	bool m_isValid;
	glm::mat4 m_transform;
	GLuint m_vertexBufferId;
	GLuint m_numberOfVerts;
	GLuint m_programId;
	GLuint m_mvpLocation;
};

