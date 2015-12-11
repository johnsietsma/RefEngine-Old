#pragma once

#include "IGameObject.h"
#include "Transform.h"

#include <glm\glm.hpp>
#include <memory>

namespace reng {

class Material;
class Mesh;
class Transform;

class RenderableGameObject: public IGameObject
{
public:
    RenderableGameObject(const Transform& trans, std::shared_ptr<Mesh> pMesh, std::shared_ptr<Material> pMaterial) :
        m_transform(trans),
        m_pMesh(pMesh),
        m_pMaterial(pMaterial)
    {}

    void Update(double deltaTime) override {} //no-op

    void Draw(OpenGLRenderer* pRenderer, Camera* pCamera) const override;


protected:
    Transform m_transform;
    std::shared_ptr<Mesh> m_pMesh;
    std::shared_ptr<Material> m_pMaterial;

};


}