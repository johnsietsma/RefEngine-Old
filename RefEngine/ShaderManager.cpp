#include "ShaderManager.h"
#include "gl_core_4_1.h"
#include "GLHelpers.h"


ProgramId ShaderManager::MakeProgram(const char* vertexShaderFileName, const char* fragmentShaderFileName)
{
	GLuint vertexShaderId = GLHelpers::LoadShader(vertexShaderFileName, GL_VERTEX_SHADER);
	GLuint fragmentShaderId = GLHelpers::LoadShader(fragmentShaderFileName, GL_FRAGMENT_SHADER);
	if (vertexShaderId == (GLuint)-1 || fragmentShaderId == (GLuint)-1) { return ProgramId_Invalid; }

	GLuint programId = glCreateProgram();
	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);
	glLinkProgram(programId);

	if (!GLHelpers::CheckLinkStatus(programId)) {
		return ProgramId_Invalid;
	}

	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);

	//m_mvpLocation = glGetUniformLocation(programId, "MVP");
	return programId;
}
