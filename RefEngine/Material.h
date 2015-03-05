#pragma once

#include "OpenGLTypes.h"

#include <glm/glm.hpp>
#include <memory>

//fwd decls
class Camera;
class GameObject;

class Material
{
public:
	Material(ProgramId programId);

	ProgramId GetProgramId() const { return m_programId;  }

	void UpdateUniforms( const Camera* pCamera, const GameObject* pGameObject );
private:
	void UpdateProjectionView(const glm::mat4x4& projectionView);

	ProgramId m_programId;
	UniformLocationId m_mvpLocation;
};
