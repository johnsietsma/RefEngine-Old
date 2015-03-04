#pragma once

#include "OpenGLTypes.h"

class ShaderManager
{
public:
	static ProgramId MakeProgram(const char* vertexShaderFileName, const char* fragmentShaderFileName);
};

