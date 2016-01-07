#pragma once

#include "entity/Component.h"
#include "entity/ComponentHandle.h"

#include <memory>

namespace reng {

class Camera;
class ComponentDatabase;
class OpenGLRenderer;
class Material;
class Mesh;
class TransformComponent;

class RenderableComponent : public IComponent 
{
public:
    RenderableComponent(const ComponentHandle<TransformComponent>& trans, std::shared_ptr<Mesh> pMesh, std::shared_ptr<Material> pMaterial) :
        m_transformComponentHandle(trans),
        m_pMesh(pMesh),
        m_pMaterial(pMaterial)
    {}

    ~RenderableComponent() override {} // Make sure the shared_ptrs get cleaned up.

    Material* GetMaterial() { return m_pMaterial.get(); }

    virtual void Draw(OpenGLRenderer* pRenderer, Camera* pCamera) const;

protected:
    const ComponentHandle<TransformComponent> m_transformComponentHandle;
    std::shared_ptr<Mesh> m_pMesh;
    std::shared_ptr<Material> m_pMaterial;

};

}