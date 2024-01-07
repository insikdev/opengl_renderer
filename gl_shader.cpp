#include "pch.h"
#include "gl_shader.h"
#include "utils.h"

Shader::Shader(const std::string& filename, GLenum type)
{
    const auto& code = Utils::LoadTextFromFile(filename);
    const char* codePtr = code.c_str();
    GLint codeLength = static_cast<GLint>(code.length());

    m_id = glCreateShader(type);

    glShaderSource(m_id, 1, &codePtr, &codeLength);
    glCompileShader(m_id);

    int result = 0;
    glGetShaderiv(m_id, GL_COMPILE_STATUS, &result);

    if (!result) {
        char infoLog[1024];
        glGetShaderInfoLog(m_id, 1024, nullptr, infoLog);
        SPDLOG_ERROR("failed to compile shader: {}", filename);
        SPDLOG_ERROR("reason: {}", infoLog);
        exit(EXIT_FAILURE);
    }

    SPDLOG_INFO("compile shader: {}", filename);
}

Shader::~Shader()
{
    if (m_id) {
        glDeleteShader(m_id);
    }
}
