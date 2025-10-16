#include "Shader.h"
#include <glad/glad.h>
#include <iostream>

Shader::Shader(const std::string &vertexSrc, const std::string &fragmentSrc) {
    m_RendererID = createProgram(vertexSrc, fragmentSrc);
}

Shader::~Shader() {
    if (m_RendererID) glDeleteProgram(m_RendererID);
}

unsigned int Shader::compileShader(unsigned int type, const std::string &src) {
    unsigned int id = glCreateShader(type);
    const char* csrc = src.c_str();
    glShaderSource(id, 1, &csrc, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (!result) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        std::string message(length, '\0');
        glGetShaderInfoLog(id, length, &length, &message[0]);
        std::cerr << "Failed to compile shader: " << message << '\n';
        glDeleteShader(id);
        return 0;
    }
    return id;
}

unsigned int Shader::createProgram(const std::string &vs, const std::string &fs) {
    unsigned int program = glCreateProgram();
    unsigned int vsId = compileShader(GL_VERTEX_SHADER, vs);
    unsigned int fsId = compileShader(GL_FRAGMENT_SHADER, fs);
    if (!vsId || !fsId) return 0;

    glAttachShader(program, vsId);
    glAttachShader(program, fsId);
    glLinkProgram(program);

    int result;
    glGetProgramiv(program, GL_LINK_STATUS, &result);
    if (!result) {
        int length;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
        std::string message(length, '\0');
        glGetProgramInfoLog(program, length, &length, &message[0]);
        std::cerr << "Failed to link program: " << message << '\n';
        glDeleteProgram(program);
        return 0;
    }

    glDeleteShader(vsId);
    glDeleteShader(fsId);
    return program;
}

void Shader::bind() const { glUseProgram(m_RendererID); }
void Shader::unbind() const { glUseProgram(0); }

void Shader::setUniformMat4(const std::string &name, const float* matrix) const {
    int location = glGetUniformLocation(m_RendererID, name.c_str());
    if (location != -1) glUniformMatrix4fv(location, 1, GL_FALSE, matrix);
}

void Shader::setUniformVec3(const std::string &name, const glm::vec3 &v) const {
    int location = glGetUniformLocation(m_RendererID, name.c_str());
    if (location != -1) glUniform3f(location, v.x, v.y, v.z);
}
