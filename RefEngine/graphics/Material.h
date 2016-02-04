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
    
    extern const char* DiffuseSampler;
    extern const char* NormalSampler;
    extern const char* SpecularSampler;
    extern const char* AmbientSampler;
    extern const char* AlphaSampler;
    extern const char* GlossSampler;
    extern const char* GlowSampler;
    extern const char* DisplacementSampler;

    extern const char* LightDirection;
    extern const char* LightColor;
    extern const char* CameraPosition;
    extern const char* SpecularPower;
}

enum class WellKnownTextureUnit {
    Diffuse,
    Normal,
    Specular,
    Ambient,
    Alpha,
    Gloss,
    Glow,
    Displacement
};
    
    
class Material
{
public:
    Material(ProgramId programId);
    Material( const Material& copy ) = default;

    bool IsLit() const { return m_isLit;  }

	ProgramId GetProgramId() const { return m_programId;  }

    void BindTexture( int textureUnit = 0 ) const;

    UniformLocationId GetUniformLocation(const char* uniformName) const
    {
        return glGetUniformLocation(m_programId.Value(), uniformName);
    }

    void SetProjectionView(const glm::mat4x4& mat);

    void SetSampler(const char* location, TextureId textureId, int textureUnit);
    void SetDiffuseSampler(TextureId textureId, int textureUnit=(int)WellKnownTextureUnit::Diffuse);
    void SetNormalSampler(TextureId textureId, int textureUnit=(int)WellKnownTextureUnit::Normal);
    void SetSpecularSampler(TextureId textureId, int textureUnit=(int)WellKnownTextureUnit::Specular);
    void SetAmbientSampler(TextureId textureId, int textureUnit=(int)WellKnownTextureUnit::Ambient);
    void SetAlphaSampler(TextureId textureId, int textureUnit=(int)WellKnownTextureUnit::Alpha);
    void SetGlossSampler(TextureId textureId, int textureUnit=(int)WellKnownTextureUnit::Gloss);
    void SetGlowSampler(TextureId textureId, int textureUnit=(int)WellKnownTextureUnit::Glow);
    void SetDisplacementSampler(TextureId textureId, int textureUnit=(int)WellKnownTextureUnit::Displacement);

    void SetLightDirection(const glm::vec3& lightDirection);

    void SetLightColor(const glm::vec3& lightColor);

    void SetCameraPosition(const glm::vec3& cameraPosition);

    void SetSpecularPower(float specularPower);

    template<typename T>
    bool SetUniformValue(const char* uniformName, const T& value) const
    {
        auto locId = GetUniformLocation(uniformName);
        if( locId== UniformLocationId_Invalid ) {
            POW2_ASSERT_FAIL("The program does not have location %s", uniformName);
            return false;
        }
        GLProgram::SetProgramUniform(m_programId, locId, value);
        return true;
    }

	void UpdateUniforms( const glm::mat4x4& projectionViewMatrix, const glm::mat4x4& pTransform );

private:
    static const int MaxTextures = 64;
    
	ProgramId m_programId;
    TextureId m_textureIds[MaxTextures]; // Each array slot is a texture unit, which has the tex that is bound to it.
    bool m_isLit;
};

}