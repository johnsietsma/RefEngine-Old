#include "Material.h"

#include "Camera.h"
#include "Transform.h"
#include "utils/pow2assert.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace reng;

Material::Material(ProgramId programId, TextureId textureId, const char* projViewUniform, const char* texUniform ) :
    m_programId(programId),
    m_textureId(textureId)
{
	m_mvpLocation = glGetUniformLocation(m_programId.Value(), projViewUniform);
	POW2_ASSERT(m_mvpLocation != UniformLocationId_Invalid);

    if (texUniform != nullptr) {
        m_texLocation = glGetUniformLocation(m_programId.Value(), texUniform);
        POW2_ASSERT(m_texLocation != UniformLocationId_Invalid);

        glProgramUniform1i(programId.Value(), m_texLocation.Value(), 0);
    }
}

void Material::BindTexture() const
{
    if (m_textureId != TextureId_Invalid) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_textureId.Value());
    }
}

void Material::UpdateUniforms(const glm::mat4x4& projectionViewMatrix, const glm::mat4x4& transform)
{
	glm::mat4 MVP = projectionViewMatrix * transform;
	UpdateProjectionView(MVP);
}


void Material::UpdateProjectionView(const glm::mat4x4& projectionView) 
{
	glUniformMatrix4fv(m_mvpLocation.Value(), 1, GL_FALSE, glm::value_ptr(projectionView));
}
