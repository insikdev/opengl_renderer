#include "pch.h"
#include "renderer.h"
#include "gl_frame_buffer.h"
#include "gl_program.h"
#include "mesh.h"
#include "geometry_helper.h"
#include "gl_texture.h"
#include "gui.h"

Renderer::Renderer(GLFWwindow* pWindow)
    : p_window { pWindow }
{
    LoadFunctions();
    InitFrameBuffer();
    InitProgram();
    SetState();
    p_gui = new Gui { p_window, m_guiOptions };
}

Renderer::~Renderer()
{
    delete p_gui;
}

void Renderer::Update(float dt)
{
}

void Renderer::Render(void)
{
    if (m_guiOptions.wireframe) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    if (m_guiOptions.cullBackface) {
        glEnable(GL_CULL_FACE);
    } else {
        glDisable(GL_CULL_FACE);
    }

    static float angle = 0.0f;
    p_frameBuffer->Bind();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    p_program->Use();
    p_program->SetUniform("world", glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0, 1.0f, 0)));
    p_program->SetUniform("view", m_camera.GetViewMatrix());
    p_program->SetUniform("projection", m_camera.GetProjectionMatrix());

    m_texture->Bind();
    m_mesh->Draw();

    if (m_guiOptions.drawNormal) {
        p_normalProgram->Use();
        p_program->SetUniform("world", glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0, 1.0f, 0)));
        p_program->SetUniform("view", m_camera.GetViewMatrix());
        p_program->SetUniform("projection", m_camera.GetProjectionMatrix());

        m_texture->Bind();
        m_mesh->Draw();
    }

    p_gui->Render();
    p_frameBuffer->DrawToScreen();
    angle += 1.0f;
}

void Renderer::SetSize(uint32_t width, uint32_t height)
{
    p_frameBuffer->Resize(width, height);
    m_camera.m_aspect = width / static_cast<float>(height);
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
    m_camera.m_aspect = width / static_cast<float>(height);
    glViewport(0, 0, width, height);
}

void Renderer::InitProgram(void)
{
    std::vector<ShaderInfo> simpleShaders = {
        { "shaders/simple.vert", GL_VERTEX_SHADER },
        { "shaders/simple.frag", GL_FRAGMENT_SHADER },
    };

    p_program = std::make_unique<Program>(simpleShaders);

    std::vector<ShaderInfo> normalShaders = {
        { "shaders/draw_normal.vert", GL_VERTEX_SHADER },
        { "shaders/draw_normal.geo", GL_GEOMETRY_SHADER },
        { "shaders/draw_normal.frag", GL_FRAGMENT_SHADER },
    };

    p_normalProgram = std::make_unique<Program>(normalShaders);

    // m_mesh = new Mesh { GeometryHelper::CreateRectangle() };
    m_mesh = new Mesh { GeometryHelper::CreateCube() };
    // m_mesh = new Mesh { GeometryHelper::CreatePlane(10, 5) };
    m_texture = new Texture { "assets/wall.jpg" };
}

void Renderer::SetState(void)
{
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
    glClearColor(0.5f, 1.0f, 1.0f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
}
