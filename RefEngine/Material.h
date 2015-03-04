#pragma once

#include "OpenGLTypes.h"

#include <glm/glm.hpp>

class Material
{
public:
	Material(ProgramId programId);

	ProgramId GetProgramId() const { return m_programId;  }

	void UpdateMVP( const glm::mat4x4& newMVP );

private:
	ProgramId m_programId;
	UniformLocationId m_mvpLocation;
};
