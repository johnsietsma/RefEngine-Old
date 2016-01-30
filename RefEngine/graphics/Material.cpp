#include "Material.h"

#include "Camera.h"
#include "Transform.h"
#include "utils/pow2assert.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

using namespace reng;

const char* WellKnownLocation::ProjectionView = "projectionView";
const char* WellKnownLocation::Sampler = "tex";
const char* WellKnownLocation::LightDirection = "lightDirection";
const char* WellKnownLocation::LightColor = "lightColor";
const char* WellKnownLocation::CameraPosition = "cameraPosition";
const char* WellKnownLocation::SpecularPower = "specularPower";

Material::Material(ProgramId programId) :
    m_programId(programId),
    m_textureId(TextureId_Invalid)
{
    m_isLit = GetUniformLocation(WellKnownLocation::LightDirection) != UniformLocationId_Invalid;
}


void Material::SetProjectionView(const glm::mat4x4& mat)
{
    SetUniformValue(WellKnownLocation::ProjectionView, mat);
}

void Material::SetTexture(TextureId textureId, int textureUnit)
{
    m_textureId = textureId;
    std::string samplerName = WellKnownLocation::Sampler;
    if( textureUnit > 0 ) {
        char numStr[15];
        sprintf(numStr, "%d", textureUnit);
        samplerName += numStr;
    }
    SetUniformValue(samplerName.c_str(), textureUnit);
}

void Material::SetLightDirection(const glm::vec3& lightDirection)
{
    SetUniformValue(WellKnownLocation::LightDirection, lightDirection);
}

void Material::SetLightColor(const glm::vec3& lightColor)
{
    SetUniformValue(WellKnownLocation::LightColor, lightColor);
}

void Material::SetCameraPosition(const glm::vec3& cameraPosition)
{
    SetUniformValue(WellKnownLocation::CameraPosition, cameraPosition);
}

void Material::SetSpecularPower(float specularPower)
{
    SetUniformValue(WellKnownLocation::SpecularPower, specularPower);
}


void Material::BindTexture(int textureUnit) const
{
    if (m_textureId != TextureId_Invalid) {
        glActiveTexture(GL_TEXTURE0 + textureUnit);
        glBindTexture(GL_TEXTURE_2D, m_textureId.Value());
    }
}

void Material::UpdateUniforms(const glm::mat4x4& projectionViewMatrix, const glm::mat4x4& transform)
{
    glm::mat4 MVP = projectionViewMatrix * transform;
    SetProjectionView(MVP);
}

