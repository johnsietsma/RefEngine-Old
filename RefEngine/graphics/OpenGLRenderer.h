#pragma once

#include "graphics/GLTypes.h"

namespace reng {

class Mesh;

struct OpenGLState
{
	ProgramId programId;
	IBOId iboId;
	VBOId vboId;
	VAOId vaoId;
};

class OpenGLRenderer
{
public:
	void UseProgram(ProgramId programId);
	void Bind(const Mesh& mesh);
	void Draw(const Mesh& mesh);
	void Unbind();
	void UnuseProgram();

private:
	OpenGLState m_state;
};

}