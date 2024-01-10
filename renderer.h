#pragma once

#include "camera.h"

class FrameBuffer;
class Program;
class Mesh;
class Gui;
class Model;
class Cubemap;
class Uniform;

class Renderer {
public:
    Renderer(GLFWwindow* pWindow);
    ~Renderer();

public:
    void Update(void);
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
    Gui* p_gui;

public:
    Camera m_camera {};

private: // shader program
    const Program* p_program;
    const Program* p_normalProgram;
    const Program* p_skyboxProgram;

private:
    Model* m_model;
    Mesh* m_cube;
    Cubemap* m_cubemap;
    Uniform* m_uniform;
    Uniform* m_uniformLight;
    Light m_light;

private:
    GuiOptions m_guiOptions;
};
