#pragma once

#include "graphics/GLTypes.h"
#include "graphics/GLProgram.h"
#include "utils/pow2assert.h"

#include <glm/glm.hpp>
#include <memory>
#include <type_traits>

namespace reng {

//fwd decls
class Camera;
class Transform;

namespace WellKnownLocation {
    extern const char* ProjectionView;
    extern const char* Sampler;
    extern const char* LightDirection;
    extern const char* LightColor;
    extern const char* CameraPosition;
    extern const char* SpecularPower;
}

class Material
{
public:
    Material(ProgramId programId);

    Material(ProgramId programId, TextureId textureId, const char* projViewUniform = "projectionView", const char* texUniform = nullptr);

	ProgramId GetProgramId() const { return m_programId;  }

    void BindTexture() const;

    UniformLocationId GetUniformLocation(const char* uniformName) const
    {
        return glGetUniformLocation(m_programId.Value(), uniformName);
    }

    void SetProjectionView(const glm::mat4x4& mat);

    void SetTexture(TextureId textureId, int textureUnit);

    void SetLightDirection(const glm::vec3& lightDirection);

    void SetLightColor(const glm::vec3& lightColor);

    void SetCameraPosition(const glm::vec3& cameraPosition);

    void SetSpecularPower(float specularPower);

    template<typename T>
    void SetUniformValue(const char* uniformName, const T& value) const
    {
        auto locId = GetUniformLocation(uniformName);
        POW2_ASSERT_MSG(locId != UniformLocationId_Invalid, "The program does not have location %s", uniformName);
        GLProgram::SetProgramUniform<T>(m_programId, locId, value);
    }

	void UpdateUniforms( const glm::mat4x4& projectionViewMatrix, const glm::mat4x4& pTransform );

private:
	ProgramId m_programId;
    TextureId m_textureId;

	UniformLocationId m_mvpLocation;
    UniformLocationId m_texLocation;
};

}