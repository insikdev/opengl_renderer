#pragma once

#include "camera.h"

class FrameBuffer;
class Program;
class Mesh;
class Texture;
class Gui;
class Model;
class Cubemap;

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
    Gui* p_gui;
    Camera m_camera {};

private: // program
    const Program* p_program;
    const Program* p_normalProgram;
    const Program* p_skyboxProgram;

private:
    Model* m_model;
    Mesh* m_cube;
    Cubemap* m_cubemap;

private:
    GuiOptions m_guiOptions;
};
