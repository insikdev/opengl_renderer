#include "pch.h"
#include "camera.h"

Camera::Camera(float fov, float aspect, float nearZ, float farZ)
    : m_fov { fov }
    , m_aspect { aspect }
    , m_near { nearZ }
    , m_far { farZ }
{
}

glm::mat4 Camera::GetViewMatrix(void)
{
    return glm::lookAt(m_position, glm::vec3(0), glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::mat4 Camera::GetProjectionMatrix(void)
{
    return glm::perspective(glm::radians(m_fov), m_aspect, m_near, m_far);
}
