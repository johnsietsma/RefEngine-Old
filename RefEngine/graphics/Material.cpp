#include "Material.h"

#include "Camera.h"
#include "Transform.h"
#include "utils/pow2assert.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace reng;

const char* WellKnownLocation::ProjectionView = "projectionView";
const char* WellKnownLocation::Sampler = "tex";
const char* WellKnownLocation::LightDirection = "lightDirection";
const char* WellKnownLocation::LightColor = "lightColor";

Material::Material(ProgramId programId) :
    m_programId(programId),
    m_textureId(TextureId_Invalid)
{
}


Material::Material(ProgramId programId, TextureId textureId, const char* projViewUniform, const char* texUniform ) :
    m_programId(programId),
    m_textureId(textureId)
{
	m_mvpLocation = glGetUniformLocation(m_programId.Value(), projViewUniform);
	POW2_ASSERT(m_mvpLocation != UniformLocationId_Invalid);

    if (texUniform != nullptr) {
        SetTexture(textureId, 0);
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
    SetProjectionView(MVP);
}

