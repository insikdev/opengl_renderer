#include "pch.h"
#include "gl_program.h"
#include "gl_shader.h"

Program::Program(const std::vector<ShaderInfo>& infos)
{
    m_id = glCreateProgram();
    LinkShaders(infos);
}

Program::~Program()
{
    if (m_id) {
        glDeleteProgram(m_id);
    }
}

void Program::Use(void) const
{
    glUseProgram(m_id);
}

void Program::SetUniform(const std::string& name, const glm::mat4& value) const
{
    auto loc = glGetUniformLocation(m_id, name.c_str());
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));
}

void Program::SetUniform(const std::string& name, const glm::vec3& value) const
{
    auto loc = glGetUniformLocation(m_id, name.c_str());
    glUniform3fv(loc, 1, glm::value_ptr(value));
}

void Program::SetUniform(const std::string& name, int value) const
{
    auto loc = glGetUniformLocation(m_id, name.c_str());
    glUniform1i(loc, value);
}

void Program::SetUniform(const std::string& name, float value) const
{
    auto loc = glGetUniformLocation(m_id, name.c_str());
    glUniform1f(loc, value);
}

void Program::LinkShaders(const std::vector<ShaderInfo>& infos)
{
    std::vector<std::unique_ptr<Shader>> shaders;

    for (const auto& item : infos) {
        auto shader = std::make_unique<Shader>(item.filename, item.type);
        glAttachShader(m_id, shader->GetId());
        shaders.push_back(std::move(shader));
    }

    glLinkProgram(m_id);

    int success = 0;
    glGetProgramiv(m_id, GL_LINK_STATUS, &success);

    if (!success) {
        char log[1024];
        glGetProgramInfoLog(m_id, 1024, nullptr, log);
        SPDLOG_ERROR("Failed to link program: {}", log);
        exit(EXIT_FAILURE);
    }

    shaders.clear();
}
