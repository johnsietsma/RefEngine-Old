#include "Material.h"


Material::Material( ProgramId programId )
:m_programId(programId)
{
	m_mvpLocation = glGetUniformLocation(m_programId.Value(), "MVP");
}

void Material::UpdateMVP(const glm::mat4x4& newMVP) {
	glUniformMatrix4fv(m_mvpLocation.Value(), 1, GL_FALSE, &newMVP[0][0]);
}
