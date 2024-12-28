/*
 *  File: Vao.h
 *  Author: Alex Emeny
 *  Date: December 28th, 2024 (Last Edited)
 *  Description: This file contains the Vao struct
 *               It defines functions for initializing new Vao's and storing Vbos.
 */

#pragma once
#include "Vbo.h"

namespace GameEngine { struct LineRenderer; }
namespace GraphicsRenderer
{
    struct Vao
    {
        Vao();

        /* Returns the Vao ID and generates a new one if dirty */
        GLuint getID();

        /* Adds new Vbos to vector and sets dirty flag within */
        void addVbo(std::shared_ptr<Vbo> _vbo);

        size_t getNumOfVboa() const { return m_vbos.size(); }
        void setDirtyFlag(bool _dirty) { m_dirty = _dirty; }

    private:
        friend GameEngine::LineRenderer;

        /* vao unique ID for rendering */
        GLuint m_ID;

        /* When dirty the ID will be regenerated with the Vbo's */
        bool m_dirty;

        /* Storage of all Vbo's within the Vao */
        std::vector<std::shared_ptr<Vbo>> m_vbos;

        /* Weak ref ptr to itself for passing to the Vbos */
        std::weak_ptr<Vao> m_self;
    };
}