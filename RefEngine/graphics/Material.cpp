#include "Material.h"

#include "Camera.h"
#include "Transform.h"
#include "utils/pow2assert.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

using namespace reng;

const char* WellKnownLocation::ProjectionView = "projectionView";

const char* WellKnownLocation::DiffuseSampler = "diffuseSampler";
const char* WellKnownLocation::AmbientSampler = "ambientSampler";
const char* WellKnownLocation::GlowSampler = "glowSampler";
const char* WellKnownLocation::SpecularSampler = "specularSampler";
const char* WellKnownLocation::GlossSampler = "glossSampler";
const char* WellKnownLocation::NormalSampler = "normalSampler";
const char* WellKnownLocation::AlphaSampler = "alphaSampler";
const char* WellKnownLocation::DisplacementSampler = "displacementSampler";

const char* WellKnownLocation::LightDirection = "lightDirection";
const char* WellKnownLocation::LightColor = "lightColor";
const char* WellKnownLocation::CameraPosition = "cameraPosition";
const char* WellKnownLocation::SpecularPower = "specularPower";

Material::Material(ProgramId programId) :
    m_programId(programId)
{
    m_isLit = GetUniformLocation(WellKnownLocation::LightDirection) != UniformLocationId_Invalid;
    
    for( int i=0; i<MaxTextures; i++ ) {
        m_textureIds[i] = TextureId_Invalid;
    }
}

void Material::SetProjectionView(const glm::mat4x4& mat)
{
    SetUniformValue(WellKnownLocation::ProjectionView, mat);
}

void Material::SetSampler(const char* location, TextureId textureId, int textureUnit)
{
    SetUniformValue(location, textureUnit);
    m_textureIds[textureUnit] = textureId;
}

void Material::SetDiffuseSampler(TextureId textureId, int textureUnit)
{
    SetSampler(WellKnownLocation::DiffuseSampler, textureId, textureUnit);
}

void Material::SetNormalSampler(TextureId textureId, int textureUnit)
{
    SetSampler(WellKnownLocation::NormalSampler, textureId, textureUnit);
}

void Material::SetSpecularSampler(TextureId textureId, int textureUnit)
{
    SetSampler(WellKnownLocation::SpecularSampler, textureId, textureUnit);
}

void Material::SetAmbientSampler(TextureId textureId, int textureUnit)
{
    SetSampler(WellKnownLocation::AmbientSampler, textureId, textureUnit);
}

void Material::SetAlphaSampler(TextureId textureId, int textureUnit)
{
    SetSampler(WellKnownLocation::AlphaSampler, textureId, textureUnit);
}

void Material::SetGlossSampler(TextureId textureId, int textureUnit)
{
    SetSampler(WellKnownLocation::GlossSampler, textureId, textureUnit);
}

void Material::SetGlowSampler(TextureId textureId, int textureUnit)
{
    SetSampler(WellKnownLocation::GlowSampler, textureId, textureUnit);
}

void Material::SetDisplacementSampler(TextureId textureId, int textureUnit)
{
    SetSampler(WellKnownLocation::DiffuseSampler, textureId, textureUnit);
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
    for( int i=0; i<MaxTextures; i++ ) {
        if (m_textureIds[i] != TextureId_Invalid) {
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, m_textureIds[i].Value());
        }
    }
}

void Material::UpdateUniforms(const glm::mat4x4& projectionViewMatrix, const glm::mat4x4& transform)
{
    glm::mat4 MVP = projectionViewMatrix * transform;
    SetProjectionView(MVP);
}

