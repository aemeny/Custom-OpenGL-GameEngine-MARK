/*
 *  File: Vao.cpp
 *  Author: Alex Emeny
 *  Date: December 28th, 2024 (Last Edited)
 *  Description: This file contains the methods declared in Vao.h
 *               It implements the functions for initializing new Vao's and adding Vbo's.
 */

#include "Vao.h"

namespace GraphicsRenderer
{
    Vao::Vao() : m_ID(0), m_dirty(true)
    {}

    /* Returns the Vao ID and generates a new one if dirty */
    GLuint Vao::getID()
    {
        if (!m_ID)
        {
            glGenVertexArrays(1, &m_ID);

            if (!m_ID)
                throw std::runtime_error("Failed to allocate VAO");
        }
        if (m_dirty)
        {
            m_dirty = false;

            glBindVertexArray(m_ID);

            for (size_t i = 0; i < m_vbos.size(); i++)
            {
                if (m_vbos.at(i)->getNumComponents() != 0) 
                {
                    glBindBuffer(GL_ARRAY_BUFFER, m_vbos[i]->getID());
                    glVertexAttribPointer(
                        i,
                        m_vbos[i]->getNumComponents(),
                        GL_FLOAT,
                        GL_FALSE,
                        m_vbos.at(i)->getStride(),
                        (void*)(m_vbos.at(i)->getOffset())
                    );
                    glEnableVertexAttribArray(i);
                }
            }

            glBindVertexArray(0);
        }

        return m_ID;
    }

    /* Adds new Vbos to vector and sets dirty flag within */
    void Vao::addVbo(std::shared_ptr<Vbo> _vbo)
    {
        m_vbos.push_back(_vbo);
        _vbo->setVao(m_self);

        if (_vbo->getNumComponents() != 0)
            m_dirty = true;
    }
}