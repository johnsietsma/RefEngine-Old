#include "ShaderManager.h"
#include "gl_core_4_4.h"
#include "GLHelpers.h"


ProgramId ShaderManager::MakeProgram(const char* vertexShaderFileName, const char* fragmentShaderFileName)
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

	//m_mvpLocation = glGetUniformLocation(programId, "MVP");
	return programId;
}
