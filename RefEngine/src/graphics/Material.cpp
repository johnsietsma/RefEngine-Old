#include "Material.h"

#include "Camera.h"
#include "Transform.h"
#include "utils/pow2assert.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace reng;

Material::Material( ProgramId programId, TextureId textureId /* = TextureId_Invalid */ ) : 
m_programId(programId),
m_textureId(textureId)
{
	m_mvpLocation = glGetUniformLocation(m_programId.Value(), "ProjectionView");
	POW2_ASSERT(m_mvpLocation != UniformLocationId_Invalid);
}

void Material::UpdateUniforms(const Camera* pCamera, const glm::mat4x4& transform)
{
	glm::mat4 MVP = pCamera->GetProjectionView() * transform;
	UpdateProjectionView(MVP);
}


void Material::UpdateProjectionView(const glm::mat4x4& projectionView) 
{
	glUniformMatrix4fv(m_mvpLocation.Value(), 1, GL_FALSE, glm::value_ptr(projectionView));
}
