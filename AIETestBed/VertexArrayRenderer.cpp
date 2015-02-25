#include "VertexArrayRenderer.h"
#include "GLHelpers.h"

#include <assert.h>
#include <glm/ext.hpp>
#include <glm/glm.hpp>

VertexArrayRenderer::VertexArrayRenderer() : m_isValid(false)
{}

bool VertexArrayRenderer::Init(GLuint vertexDataSize, GLuint numVerts, const GLfloat* vertexData, const char* vertexShaderFileName, const char* fragmentShaderFileName)
{
	assert(!m_isValid);
	m_transform = glm::mat4(1.f);
	m_numberOfVerts = vertexDataSize / (3*sizeof(GLfloat));
	if (!InitShaders(vertexShaderFileName, fragmentShaderFileName)) { return false; }
	InitVertexBuffer(vertexDataSize, vertexData);
	m_isValid = true;
	return true;
}

void VertexArrayRenderer::Render( const glm::mat4& projView ) const
{
	assert(m_isValid);

	glm::mat4 MVP = projView * m_transform;

	glUseProgram(m_programId);
	glUniformMatrix4fv(m_mvpLocation, 1, GL_FALSE, &MVP[0][0]);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3*m_numberOfVerts);
	glDisableVertexAttribArray(0);
}

void VertexArrayRenderer::Destroy()
{
	if (m_isValid) return;

	glDeleteBuffers(1, &m_vertexBufferId);

	m_isValid = false;
}

void VertexArrayRenderer::InitVertexBuffer(size_t vertexDataSize, const GLfloat* vertexData)
{
	glGenBuffers(1, &m_vertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, vertexDataSize, vertexData, GL_STATIC_DRAW);
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
