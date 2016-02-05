#pragma once

#include "utils/memaligned.h"

#include <glm/glm.hpp>

#include "Transform.h"

namespace reng {

class Camera
{
public:
	Camera( float fov, float aspectRatio, float nearClipDistance, float farClipDistance );
	Camera( const Transform& transform, float fov, float aspectRatio, float nearClipDistance, float farClipDistance );

	glm::mat4 GetProjectionViewMatrix() const { return m_projection * GetViewMatrix(); }
	glm::mat4 GetViewMatrix() const { return glm::inverse(m_worldTransform.GetMatrix()); }

	const Transform& GetTransform() const { return m_worldTransform; };

	void SetTransform(const Transform& transform) { m_worldTransform = transform; }
	void SetProjection(float fov, float aspectRatio, float nearClipDistance, float farClipDistance);

	ALIGNED_NEW_OP_16
	ALIGNED_DELETE_OP

private:
	Transform m_worldTransform;
	glm::mat4 m_projection;
};

}