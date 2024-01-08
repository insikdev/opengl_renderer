#include "pch.h"
#include "renderer.h"
#include "gl_frame_buffer.h"
#include "gl_program.h"
#include "mesh.h"
#include "geometry_helper.h"
#include "gl_texture.h"
#include "gui.h"
#include "model.h"
#include "gl_cubemap.h"
#include "gl_uniform.h"

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
    delete m_uniform;
    delete m_cube;
    delete p_gui;
    delete p_program;
    delete p_normalProgram;
    delete p_skyboxProgram;
}

void Renderer::Update()
{
    float dt = ImGui::GetIO().DeltaTime;
    m_camera.Update(p_window, dt);
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

    // uniform buffer
    m_uniform->Bind();
    m_uniform->CopyData(0, sizeof(glm::mat4), glm::value_ptr(m_camera.GetViewMatrix()));
    m_uniform->CopyData(sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(m_camera.GetProjectionMatrix()));

    m_uniform->Unbind();

    p_program->Use();

    glm::mat4 world(1.0f);
    // world = glm::scale(world, glm::vec3(0.01f, 0.01f, 0.01f));
    //  world = glm::rotate(world, glm::radians(angle), glm::vec3(0, 1.0f, 0));
    p_program->SetUniform("world", world);
    p_program->SetUniform("cameraPos", m_camera.m_position);

    m_model->Draw(p_program);

    if (m_guiOptions.drawNormal) {
        p_normalProgram->Use();
        p_program->SetUniform("world", world);
        m_model->Draw(p_program);
    }

    { // skybox
        glDisable(GL_CULL_FACE);
        glDepthFunc(GL_LEQUAL);

        p_skyboxProgram->Use();
        glActiveTexture(GL_TEXTURE0);
        m_cubemap->Bind();
        p_skyboxProgram->SetUniform("skybox", 0);
        m_cube->Draw(p_skyboxProgram);

        glDepthFunc(GL_LESS);
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
        { "shaders/env.vert", GL_VERTEX_SHADER },
        { "shaders/env.frag", GL_FRAGMENT_SHADER },
    };

    p_program = new Program { simpleShaders };

    std::vector<ShaderInfo> normalShaders = {
        { "shaders/draw_normal.vert", GL_VERTEX_SHADER },
        { "shaders/draw_normal.geo", GL_GEOMETRY_SHADER },
        { "shaders/draw_normal.frag", GL_FRAGMENT_SHADER },
    };

    p_normalProgram = new Program { normalShaders };

    std::vector<ShaderInfo> skyboxPrograms = {
        { "shaders/skybox.vert", GL_VERTEX_SHADER },
        { "shaders/skybox.frag", GL_FRAGMENT_SHADER },
    };

    p_skyboxProgram = new Program { skyboxPrograms };

    m_cube = new Mesh { GeometryHelper::CreateCube() };
    m_model = new Model { "models/backpack/backpack.obj" };

    m_cubemap = new Cubemap { {
        "skybox/posx.jpg",
        "skybox/negx.jpg",
        "skybox/posy.jpg",
        "skybox/negy.jpg",
        "skybox/posz.jpg",
        "skybox/negz.jpg",
    } };

    m_uniform = new Uniform { 0, GL_STATIC_DRAW, sizeof(glm::mat4), 2 };
}

void Renderer::SetState(void)
{
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
    glClearColor(0.5f, 1.0f, 1.0f, 1.0f);

    glEnable(GL_DEPTH_TEST);
}
