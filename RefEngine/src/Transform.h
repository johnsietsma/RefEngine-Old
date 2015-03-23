#pragma once

#include <glm/glm.hpp>
#include <memaligned.h>

namespace reng {

class Transform {
public:
	Transform(const glm::vec3 position) {
		glm::vec4 pos = glm::vec4(position, 1);
		glm::mat4 trans = glm::mat4(1.0f);
		m_globalTransform[3] = pos;
	}

	Transform( const glm::mat4x4& transform ) :
		m_globalTransform(transform)
	{}

	const glm::mat4x4& GetTransform() const { return m_globalTransform; }
	void SetTransform( const glm::mat4x4& transform )  { m_globalTransform = transform; }

	ALIGNED_NEW_OP_16
	ALIGNED_DELETE_OP

private:
	glm::mat4x4 m_localTransform;
	glm::mat4x4 m_globalTransform;
};

}