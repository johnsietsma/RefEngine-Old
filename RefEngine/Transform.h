#pragma once

#include "utils/memaligned.h"

#include <glm/glm.hpp>


namespace reng {

class Transform {
public:
    Transform() :
        m_localTransform(1),
        m_globalTransform(1)
    {}

    Transform(const glm::vec3& position, const glm::quat& rot, const glm::vec3& scale);

    Transform(glm::vec3 position);

	Transform( const glm::mat4x4& transform ) :
		m_globalTransform(transform)
	{}

	const glm::mat4x4& GetMartix() const { return m_globalTransform; }
	glm::vec3 GetPosition() const { return glm::vec3(m_globalTransform[3]); };
	glm::vec3 GetRight() const { return glm::vec3(m_globalTransform[0]); }
	glm::vec3 GetUp() const { return glm::vec3(m_globalTransform[1]); }
	glm::vec3 GetForward() const { return glm::vec3(m_globalTransform[2]); }

	void SetMatrix( const glm::mat4x4& transform )  { m_globalTransform = transform; }
	void SetPosition(const glm::vec3& position) { m_globalTransform[3] = glm::vec4(position, 1); }

	void Translate(const glm::vec3& positionDelta) { SetPosition(GetPosition() + positionDelta); }

	ALIGNED_NEW_OP_16
	ALIGNED_DELETE_OP

private:
	glm::mat4x4 m_localTransform;
	glm::mat4x4 m_globalTransform;
};

}
