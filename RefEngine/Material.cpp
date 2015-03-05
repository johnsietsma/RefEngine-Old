#include "Material.h"

#include "Camera.h"
#include "GameObject.h"
#include "pow2assert.h"

#include <glm/gtc/type_ptr.hpp>


Material::Material( ProgramId programId )
:m_programId(programId)
{
	m_mvpLocation = glGetUniformLocation(m_programId.Value(), "ProjectionView");
	POW2_ASSERT(m_mvpLocation != UniformLocationId_Invalid);
}

void Material::UpdateUniforms(const Camera* pCamera, const GameObject* pGameObject)
{
	glm::mat4 MVP = pCamera->GetProjectionView() * pGameObject->GetTransform();
	UpdateProjectionView(MVP);
}


void Material::UpdateProjectionView(const glm::mat4x4& projectionView) 
{
	glUniformMatrix4fv(m_mvpLocation.Value(), 1, GL_FALSE, glm::value_ptr(projectionView));
}
