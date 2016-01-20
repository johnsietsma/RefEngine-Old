#pragma once

#include "entity/ComponentHandle.h"

#include <memory>

namespace reng {

class Camera;
class OpenGLRenderer;
class Material;
class Mesh;
class TransformComponent;

class RenderableComponent 
{
public:
    RenderableComponent(const ComponentHandle<TransformComponent>& trans, std::shared_ptr<Mesh> pMesh, std::shared_ptr<Material> pMaterial) :
        m_transformComponentHandle(trans),
        m_pMesh(pMesh),
        m_pMaterial(pMaterial)
    {}

    ~RenderableComponent() = default;

    Material* GetMaterial() { return m_pMaterial.get(); }

    void Draw(OpenGLRenderer* pRenderer, Camera* pCamera) const;

protected:
    const ComponentHandle<TransformComponent> m_transformComponentHandle;
    std::shared_ptr<Mesh> m_pMesh;
    std::shared_ptr<Material> m_pMaterial;

};

}