#pragma once

#include "OpenGLTypes.h"

#include <glm/glm.hpp>
#include <memory>

namespace reng {

//fwd decls
class Camera;
class Transform;

class Material
{
public:
	Material(ProgramId programId, TextureId=TextureId_Invalid, const char* projViewUniform="projectionView", const char* texUniform=nullptr);

	ProgramId GetProgramId() const { return m_programId;  }

    void BindTexture() const;
	void UpdateUniforms( const glm::mat4x4& projectionViewMatrix, const glm::mat4x4& pTransform );

private:
	void UpdateProjectionView(const glm::mat4x4& projectionView);

	ProgramId m_programId;
    TextureId m_textureId;

	UniformLocationId m_mvpLocation;
    UniformLocationId m_texLocation;
};

}