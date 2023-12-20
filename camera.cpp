#include "pch.h"
#include "camera.h"

glm::mat4 Camera::GetViewMatrix(void)
{
    return glm::lookAt(m_position, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::mat4 Camera::GetProjectionMatrix(void)
{
    return glm::perspective(glm::radians(45.0f), 1024 / 768.0f, 0.1f, 50.0f);
}
