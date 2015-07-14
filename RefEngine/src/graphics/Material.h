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
	Material(ProgramId programId, TextureId=TextureId_Invalid);

	ProgramId GetProgramId() const { return m_programId;  }

	void UpdateUniforms( const Camera* pCamera, const glm::mat4x4& pTransform );
private:
	void UpdateProjectionView(const glm::mat4x4& projectionView);

	ProgramId m_programId;
	UniformLocationId m_mvpLocation;
	TextureId m_textureId;
};

}