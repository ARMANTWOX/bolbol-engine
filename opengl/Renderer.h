#pragma once

#include "Shader.h"
#include <string>

class Renderer {
public:
    Renderer();
    ~Renderer();

    bool init();
    void onResize(int width, int height);
    void render(float time);

private:
    unsigned int m_VAO = 0, m_VBO = 0;
    Shader* m_Shader = nullptr;
};
