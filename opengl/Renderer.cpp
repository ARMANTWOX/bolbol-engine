#include "Renderer.h"
#include <glad/glad.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

static const std::string vertexSrc = R"glsl(
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
out vec3 vColor;
uniform mat4 u_Model;
void main() {
    vColor = aColor;
    gl_Position = u_Model * vec4(aPos, 1.0);
}
)glsl";

static const std::string fragmentSrc = R"glsl(
#version 330 core
in vec3 vColor;
out vec4 FragColor;
void main() {
    FragColor = vec4(vColor, 1.0);
}
)glsl";

Renderer::Renderer() {}

Renderer::~Renderer() {
    if (m_VBO) glDeleteBuffers(1, &m_VBO);
    if (m_VAO) glDeleteVertexArrays(1, &m_VAO);
    delete m_Shader;
}

bool Renderer::init() {
    m_Shader = new Shader(vertexSrc, fragmentSrc);
    if (!m_Shader) return false;

    float vertices[] = {
        // positions       // colors
         0.0f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f
    };

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);

    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    glBindVertexArray(0);
    return true;
}

void Renderer::onResize(int width, int height) {
    glViewport(0, 0, width, height);
}

void Renderer::render(float time) {
    glClearColor(0.1f, 0.12f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_Shader->bind();
    glm::mat4 model = glm::rotate(glm::mat4(1.0f), time * 0.5f, glm::vec3(0.0f, 0.0f, 1.0f));
    m_Shader->setUniformMat4("u_Model", &model[0][0]);

    glBindVertexArray(m_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);

    m_Shader->unbind();
}
