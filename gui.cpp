#include "pch.h"
#include "gui.h"

Gui::Gui(GLFWwindow* pWindow, GuiOptions& options)
    : m_options { options }
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(pWindow, true);
    ImGui_ImplOpenGL3_Init("#version 460 core");
}

Gui::~Gui()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Gui::Render()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("GUI", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::SetWindowPos(ImVec2(10, 10));

    ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::Checkbox("wireframe", &m_options.wireframe);
    ImGui::Checkbox("cull backface", &m_options.cullBackface);
    ImGui::Checkbox("draw normal", &m_options.drawNormal);

    ImGui::SliderFloat3("light.pos", glm::value_ptr(m_options.light->pos), -2.0f, 2.0f);
    ImGui::SliderFloat3("light.dir", glm::value_ptr(m_options.light->dir), -2.0f, 2.0f);
    ImGui::SliderFloat("light.cutoff Start", &m_options.light->cutoffStart, glm::cos(glm::radians(5.0f)), glm::cos(glm::radians(15.0f)));
    ImGui::SliderFloat("light.cutoff End", &m_options.light->cutoffEnd, glm::cos(glm::radians(15.0f)), glm::cos(glm::radians(35.0f)));
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
