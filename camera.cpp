#include "pch.h"
#include "camera.h"

Camera::Camera(float fov, float aspect, float nearZ, float farZ)
    : m_fov { fov }
    , m_aspect { aspect }
    , m_near { nearZ }
    , m_far { farZ }
{
}

void Camera::Update(GLFWwindow* pWindow, float dt)
{
    const float cameraSpeed = 10.0f;

    if (glfwGetKey(pWindow, GLFW_KEY_W) == GLFW_PRESS) {
        m_position += m_front * dt * cameraSpeed;
    } else if (glfwGetKey(pWindow, GLFW_KEY_S) == GLFW_PRESS) {
        m_position -= m_front * dt * cameraSpeed;
    } else if (glfwGetKey(pWindow, GLFW_KEY_A) == GLFW_PRESS) {
        glm::vec3 cameraRight = glm::normalize(glm::cross(m_up, -m_front));
        m_position -= cameraRight * dt * cameraSpeed;
    } else if (glfwGetKey(pWindow, GLFW_KEY_D) == GLFW_PRESS) {
        glm::vec3 cameraRight = glm::normalize(glm::cross(m_up, -m_front));
        m_position += cameraRight * dt * cameraSpeed;
    }

    if (glfwGetMouseButton(pWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        double x, y;
        glfwGetCursorPos(pWindow, &x, &y);

        if (m_prevPos.x != 0 && m_prevPos.y != 0) {
            m_yaw -= x - m_prevPos.x;
        }
        m_prevPos.x = x;
        m_prevPos.y = y;
    } else if (glfwGetMouseButton(pWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
        m_prevPos = glm::vec2(0.0f, 0.0f);
    }
}

glm::mat4 Camera::GetViewMatrix(void)
{
    m_front = glm::rotate(glm::mat4(1.0f), glm::radians(m_yaw), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f);

    return glm::lookAt(m_position, m_position + m_front, m_up);
}

glm::mat4 Camera::GetProjectionMatrix(void)
{
    return glm::perspective(glm::radians(m_fov), m_aspect, m_near, m_far);
}
