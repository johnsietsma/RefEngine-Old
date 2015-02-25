#include "VertexArrayRenderer.h"
#include "GLHelpers.h"

#include <assert.h>
#include <glm/matrix.hpp>

bool VertexArrayRenderer::Init(const GLfloat* vertexData, const char* vertexShaderFileName, const char* fragmentShaderFileName)
{
	assert(!m_isValid);

	if (!InitShaders(vertexShaderFileName, fragmentShaderFileName)) { return false; }
	InitVertexBuffer();

	m_isValid = true;

	return true;
}

void VertexArrayRenderer::Render( const glm::mat4& projView ) const
{
	assert(m_isValid);

	glm::mat4 Model = glm::mat4(1.f);
	glm::mat4 MVP = projView * Model;

	glUseProgram(m_programId);

	glUniformMatrix4fv(m_mvpLocation, 1, GL_FALSE, &MVP[0][0]);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);
}

void VertexArrayRenderer::Destroy()
{
	if (m_isValid) return;

	glDeleteBuffers(1, &m_vertexBufferId);

	m_isValid = false;
}

void VertexArrayRenderer::InitVertexBuffer()
{
	const float vertexBufferData[] = {
		-1.f, -1.f, 0.f,
		1.f, -1.f, 0.f,
		0.f, 1.f, 0.f
	};

	glGenBuffers(1, &m_vertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferData), vertexBufferData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


bool VertexArrayRenderer::InitShaders(const char* vertexShaderFileName, const char* fragmentShaderFileName)
{
	GLuint vertexShaderId = GLHelpers::LoadShader(vertexShaderFileName, GL_VERTEX_SHADER);
	GLuint fragmentShaderId = GLHelpers::LoadShader(fragmentShaderFileName, GL_FRAGMENT_SHADER);

	if (vertexShaderId == (GLuint)-1 || fragmentShaderId == (GLuint)-1) { return false; }

	GLuint programId = glCreateProgram();
	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);
	glLinkProgram(programId);

	if (!GLHelpers::CheckLinkStatus(programId)) {
		return false;
	}

	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);

	m_mvpLocation = glGetUniformLocation(programId, "MVP");
	m_programId = programId;

	return true;
}
