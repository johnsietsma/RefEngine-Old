#include "ProgramManager.h"
#include "gl_core_4_1.h"
#include "GLHelpers.h"
#include "pow2assert.h"

#include <functional>

ProgramId ProgramManager::GetOrCreateProgram(const char* vertexShaderFileName, const char* fragmentShaderFileName)
{
    // Check to see if the program already exists
	int programKey = GetProgramKey( vertexShaderFileName, fragmentShaderFileName );
	if( m_programMap.find(programKey)!=m_programMap.end() ) { return m_programMap[programKey]; }

    // Create or get the shaders
	ShaderId vertexShaderId = GetShader( vertexShaderFileName, GL_VERTEX_SHADER );
	ShaderId fragmentShaderId = GetShader(fragmentShaderFileName, GL_FRAGMENT_SHADER);
	if (vertexShaderId == ShaderId_Invalid || fragmentShaderId == ShaderId_Invalid) { return ProgramId_Invalid; }

    // Create the program
	GLuint programId = glCreateProgram();
	glAttachShader(programId, vertexShaderId.Value());
	glAttachShader(programId, fragmentShaderId.Value());
	glLinkProgram(programId);

	if (!GLHelpers::CheckLinkStatus(programId)) {
		programId = ProgramId_Invalid.Value();
	}


    // Cache the program (even if it's invalid to save time relinking bad shaders)
	m_programMap[programKey] = programId;

    // Cleanup
	glDeleteShader(vertexShaderId.Value());
	glDeleteShader(fragmentShaderId.Value());


	return programId;
}

ShaderId ProgramManager::GetShader(const char* shaderFileName, GLenum shaderType )
{
	// We only support verex and fragment shaders right now
	POW2_ASSERT(shaderType==GL_VERTEX_SHADER || shaderType==GL_FRAGMENT_SHADER);
	return GLHelpers::LoadShader(shaderFileName, shaderType);
}

int ProgramManager::GetProgramKey(const char* vertexShaderFileName, const char* fragmentShaderFileName)
{
	std::hash<std::string> hash_fn;
	return hash_fn(vertexShaderFileName) ^ hash_fn(fragmentShaderFileName);
}

