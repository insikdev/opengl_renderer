#pragma once

class Camera {
public:
    Camera(float fov = 55.0f, float aspect = 1.7f, float nearZ = 1.0f, float farZ = 50.0f);
    ~Camera() = default;

public:
    void Update(GLFWwindow* pWindow, float dt);
    glm::mat4 GetViewMatrix(void);
    glm::mat4 GetProjectionMatrix(void);

public:
    glm::vec3 m_position { 0.0f, 0.0f, 10.0f };
    glm::vec3 m_front { 0.0f, 0.0f, -1.0f };
    const glm::vec3 m_up { 0.0f, 1.0f, 0.0f };
    float m_pitch {};
    float m_yaw {};
    glm::vec2 m_prevPos { 0.0f };

public:
    float m_fov;
    float m_aspect;
    float m_near;
    float m_far;
};
