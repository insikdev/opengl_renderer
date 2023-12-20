#include "pch.h"
#include "renderer.h"
#include "gl_frame_buffer.h"
#include "gl_program.h"
#include "mesh.h"
#include "geometry_helper.h"
#include "gl_texture.h"

Renderer::Renderer(GLFWwindow* pWindow)
    : p_window { pWindow }
{
    LoadFunctions();
    InitFrameBuffer();
    InitProgram();
    SetState();
}

Renderer::~Renderer()
{
}

void Renderer::Update(float dt)
{
}

void Renderer::Render(void)
{
    static float angle = 0.0f;
    p_frameBuffer->Bind();
    int width;
    int height;
    glfwGetFramebufferSize(p_window, &width, &height);
    auto projection = glm::perspective(glm::radians(45.0f), width / static_cast<float>(height), 0.1f, 50.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    p_program->Use();
    p_program->SetUniform("world", glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0, 1.0f, 0)));
    p_program->SetUniform("view", m_camera.GetViewMatrix());
    p_program->SetUniform("projection", projection);
    // glActiveTexture(GL_TEXTURE0);
    m_texture->Bind();
    m_mesh->Draw();
    p_frameBuffer->DrawToScreen();
    angle += 1.0f;
}

void Renderer::SetSize(uint32_t width, uint32_t height)
{
    p_frameBuffer->Resize(width, height);
}

void Renderer::LoadFunctions(void)
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        SPDLOG_ERROR("Failed to load OpenGL");
        exit(EXIT_FAILURE);
    }

    auto glVersion = glGetString(GL_VERSION);
    SPDLOG_INFO("Create OpenGL Context - version : {}", (const char*)glVersion);
}

void Renderer::InitFrameBuffer(void)
{
    int width;
    int height;
    glfwGetFramebufferSize(p_window, &width, &height);

    p_frameBuffer = std::make_unique<FrameBuffer>(width, height);
    glViewport(0, 0, width, height);
}

void Renderer::InitProgram(void)
{
    std::vector<ShaderInfo> shaders = {
        { "shaders/simple.vert", GL_VERTEX_SHADER },
        { "shaders/simple.frag", GL_FRAGMENT_SHADER },
    };

    p_program = std::make_unique<Program>(shaders);
    m_mesh = new Mesh { GeometryHelper::CreateCube() };
    m_texture = new Texture { "assets/wall.jpg" };
}

void Renderer::SetState(void)
{
    glClearColor(0.5f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
}
