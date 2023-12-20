#pragma once

class Camera {
public:
    Camera() = default;
    ~Camera() = default;

public:
    glm::mat4 GetViewMatrix(void);
    glm::mat4 GetProjectionMatrix(void);

public:
    glm::vec3 m_position { glm::vec3 { 5.0f, 5.0f, 5.0f } };
    float m_pitch {};
    float m_yaw {};
};
