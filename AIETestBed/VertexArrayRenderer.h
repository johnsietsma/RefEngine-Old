#pragma once

#include "gl_core_4_4.h"

#include <glm/fwd.hpp>

class VertexArrayRenderer
{
public:
	bool Init(const GLfloat* vertexData, const char* vertexShaderFileName, const char* fragmentShaderFileName);
	void Render(const glm::mat4& projView) const;
	void Destroy();

private:
	void InitVertexBuffer();
	bool InitShaders(const char* vertexShaderFileName, const char* fragmentShaderFileName);

	bool m_isValid;
	GLuint m_vertexArrayId;
	GLuint m_vertexBufferId;
	GLuint m_programId;
	GLuint m_mvpLocation;
};

