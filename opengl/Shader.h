#pragma once

#include <string>
#include <glm/vec3.hpp>

class Shader {
public:
    explicit Shader(const std::string &vertexSrc, const std::string &fragmentSrc);
    ~Shader();

    void bind() const;
    void unbind() const;

    void setUniformMat4(const std::string &name, const float* matrix) const;
    void setUniformVec3(const std::string &name, const glm::vec3 &v) const;

private:
    unsigned int m_RendererID = 0;
    unsigned int compileShader(unsigned int type, const std::string &src);
    unsigned int createProgram(const std::string &vs, const std::string &fs);
};
