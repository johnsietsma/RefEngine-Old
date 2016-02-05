#include "Transform.h"

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/matrix_decompose.hpp"
#include "glm/gtx/transform.hpp"

using namespace reng;


Transform::Transform(glm::vec3 position)
: Transform(position, glm::quat(), glm::vec3(1) )
{
}


Transform::Transform(glm::vec3 position, glm::quat rot) :
Transform(position, rot, glm::vec3(1))
{
}

Transform::Transform(glm::vec3 position, glm::quat rot, glm::vec3 scale) :
	m_position(position),
	m_rotation(rot),
	m_scale(scale)
{
}


Transform::Transform(glm::vec3 position, glm::vec3 lookAt) :
	Transform(glm::inverse(glm::lookAt(position, lookAt, glm::vec3(0, 1, 0))) )
{
}

Transform::Transform(glm::mat4 matrix)
{
	glm::vec3 skew;
	glm::vec4 perspective;
	glm::decompose(matrix, m_scale, m_rotation, m_position, skew, perspective);
	glm::vec3 rot = glm::eulerAngles(m_rotation);

}

 glm::mat4 Transform::GetMatrix() const
{ 
	return glm::translate(m_position) * glm::mat4_cast(m_rotation);// *glm::scale(m_scale);
}
