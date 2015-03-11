#pragma once

#include "OpenGLTypes.h"

#include <map>

class ProgramManager
{
public:
	ProgramId GetOrCreateProgram(const char* vertexShaderFileName, const char* fragmentShaderFileName);

private:
    ShaderId GetShader( const char* shaderFileName, GLenum shaderType );
    int GetProgramKey(const char* vertexShaderFileName, const char* fragmentShaderFileName);

    std::map<int,ProgramId> m_programMap;
};

