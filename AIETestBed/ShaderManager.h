#pragma once

#include "OpenGLTypes.h"

class ShaderManager
{
public:
	static ProgramId ShaderManager::MakeProgram(const char* vertexShaderFileName, const char* fragmentShaderFileName);
};

