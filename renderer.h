#pragma once

#include "camera.h"

class FrameBuffer;
class Program;
class Mesh;
class Texture;

class Renderer {
public:
    Renderer(GLFWwindow* pWindow);
    ~Renderer();

public:
    void Update(float dt);
    void Render(void);
    void SetSize(uint32_t width, uint32_t height);

private:
    void LoadFunctions(void);
    void InitFrameBuffer(void);
    void InitProgram(void);
    void SetState(void);

private:
    GLFWwindow* const p_window;
    std::unique_ptr<FrameBuffer> p_frameBuffer;
    std::unique_ptr<Program> p_program;
    Camera m_camera {};

private:
    Mesh* m_mesh;
    Texture* m_texture;
};
