/*
 *  File: Vbo.cpp
 *  Author: Alex Emeny
 *  Date: December 28th, 2024 (Last Edited)
 *  Description: This file contains the methods declared in Vbo.h
 *               It implements the functions for initializing new Vbo's to the Vao and returning a generated ID.
 */

#include "Vbo.h"
#include "Vao.h"

namespace GraphicsRenderer
{
    Vbo::Vbo() : m_ID(0), m_dirty(false), m_numComponents(0), 
        vboIdentifierID(count++), m_stride(0), m_offset(0)
    {}

    int Vbo::count = 0;

    /* Add data to the Vbo with Vec2 */
    void Vbo::add(const glm::vec2& _value)
    {
        m_data.push_back(_value.x);
        m_data.push_back(_value.y);

        m_dirty = true;
        m_numComponents = 2;

        if (m_vao.expired() == false)
            m_vao.lock()->setDirtyFlag(true);
    }

    /* Add data to the Vbo with Vec3 */
    void Vbo::add(const glm::vec3& _value)
    {
        m_data.push_back(_value.x);
        m_data.push_back(_value.y);
        m_data.push_back(_value.z);

        m_dirty = true;
        m_numComponents = 3;

        if (m_vao.expired() == false)
            m_vao.lock()->setDirtyFlag(true);
    }

    void Vbo::clearData()
    {
        m_data.clear();

        m_dirty = false;
        m_numComponents = 0;

        if (m_vao.expired() == false)
            m_vao.lock()->setDirtyFlag(false);
    }

    /* Returns ID generated or if dirty generates a new ID */
    GLuint Vbo::getID()
    {
        if (!m_ID)
        {
            glGenBuffers(1, &m_ID);
            if (!m_ID)
                throw std::runtime_error("Failed to allocate VBO");
        }
        if (m_dirty)
        {
            glBindBuffer(GL_ARRAY_BUFFER, m_ID);
            // Upload a copy of the data from memory into the new VBO
            glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_data.size(), &m_data.at(0), GL_STATIC_DRAW);
            // Reset the state
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            m_dirty = false;
        }

        return m_ID;
    }
}