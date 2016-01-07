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

class CameraComponent : public IComponent 
{
public:
    CameraComponent(glm::vec3 eye, glm::vec3 center, float fov, float aspectRatio) :
        m_camera(eye, center, fov, aspectRatio)
    {}

    Camera& GetCamera() { return m_camera;  }

protected:
    Camera m_camera;

};

}