#pragma once

namespace reng {

class Camera;

class CameraComponent 
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