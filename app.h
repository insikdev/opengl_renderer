#pragma once

class Renderer;

class App {
public:
    App(uint32_t width, uint32_t height, const char* title);
    ~App();

public:
    void Run(void);

private:
    void InitGLFW(uint32_t width, uint32_t height, const char* title);
    void InitRenderer(void);
    void SetCallback(void);

private: // callback
    void HandleFrameBufferSizeChange(int width, int height);

private:
    GLFWwindow* m_window {};
    std::unique_ptr<Renderer> p_renderer;
};
