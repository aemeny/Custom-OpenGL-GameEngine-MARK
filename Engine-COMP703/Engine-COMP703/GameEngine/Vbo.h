#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <memory>

namespace GraphicsRenderer
{
    struct Vao;

    struct Vbo
    {
        Vbo();

    private:
        GLuint m_ID;
    };
}
