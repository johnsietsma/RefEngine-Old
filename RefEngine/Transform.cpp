#include "Transform.h"

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/transform.hpp"

using namespace reng;

Transform::Transform(const glm::vec3& position, const glm::quat& rot) :
Transform(position, rot, glm::vec3(1))
{
}

Transform::Transform(const glm::vec3& position, const glm::quat& rot, const glm::vec3& scale)
{
    m_globalTransform = glm::mat4_cast(rot);
    m_globalTransform *= glm::translate(position);
    m_globalTransform *= glm::scale(scale);
}

Transform::Transform(glm::vec3 position)
    : Transform(position, glm::quat(), glm::vec3(1) )
{
}
