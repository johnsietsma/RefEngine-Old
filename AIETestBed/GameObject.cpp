#include "GameObject.h"


GameObject::GameObject(const glm::mat4x4& transform, std::shared_ptr<Material> pMaterial, std::shared_ptr<Buffer> buffer)
: m_transform(transform)
, m_pMaterial(pMaterial)
, m_pBuffer(buffer)
{
}


GameObject::~GameObject()
{
}
