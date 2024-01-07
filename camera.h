#pragma once

class Camera {
public:
    Camera(float fov = 55.0f, float aspect = 1.7f, float nearZ = 1.0f, float farZ = 50.0f);
    ~Camera() = default;

public:
    glm::mat4 GetViewMatrix(void);
    glm::mat4 GetProjectionMatrix(void);

public:
    glm::vec3 m_position { glm::vec3 { 0.0f, 0.0f, -10.0f } };
    float m_pitch {};
    float m_yaw {};

public:
    float m_fov;
    float m_aspect;
    float m_near;
    float m_far;
};
