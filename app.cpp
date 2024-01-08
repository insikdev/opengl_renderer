#include "pch.h"
#include "app.h"
#include "renderer.h"

App::App(uint32_t width, uint32_t height, const char* title)
{
    InitGLFW(width, height, title);
    InitRenderer();
    SetCallback();
}

App::~App()
{
    if (m_window) {
        glfwDestroyWindow(m_window);
    }
    glfwTerminate();
}

void App::Run(void)
{
    glfwSwapInterval(1); // vsync

    while (!glfwWindowShouldClose(m_window)) {
        p_renderer->Update();
        p_renderer->Render();
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
}

void App::InitGLFW(uint32_t width, uint32_t height, const char* title)
{
    if (!glfwInit()) {
        SPDLOG_ERROR("Falied to initialize GLFW");
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);

    if (!m_window) {
        SPDLOG_ERROR("Falied to create window");
        glfwDestroyWindow(m_window);
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(m_window);
}

void App::InitRenderer()
{
    p_renderer = std::make_unique<Renderer>(m_window);
}

void App::SetCallback(void)
{
    glfwSetWindowUserPointer(m_window, this);

    glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {
        reinterpret_cast<App*>(glfwGetWindowUserPointer(window))->HandleFrameBufferSizeChange(width, height);
    });

    glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        reinterpret_cast<App*>(glfwGetWindowUserPointer(window))->HandleKey(key, scancode, action, mods);
    });
}

void App::HandleFrameBufferSizeChange(int width, int height)
{
    int w = glm::max(1, width);
    int h = glm::max(1, height);
    glViewport(0, 0, w, h);
    p_renderer->SetSize(w, h);
}

void App::HandleKey(int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(m_window, true);
    }
}
