/*
 *  File: Vbo.h
 *  Author: Alex Emeny
 *  Date: December 28th, 2024 (Last Edited)
 *  Description: This file contains the Vbo struct
 *               It defines functions for initializing new Vbo's to the Vao and storing Vbo data.
 */

#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <memory>
#include <stdexcept>

namespace GraphicsRenderer
{
    struct Vao;

    struct Vbo
    {
        Vbo();

        /* Add data to the Vbo either with Vec2 or Vec3 */
        void add(const glm::vec2& _value);
        void add(const glm::vec3& _value);
        void clearData();

        /* Returns ID generated or if dirty generates a new ID */
        GLuint getID();

        /* Setters and Getters for the Vbos variables */
        int getIdentifierID() { return vboIdentifierID; }

        void setVao(std::weak_ptr<Vao> _Vao) { m_vao = _Vao; }
        int getDataSize() { return m_data.size(); }
        int getNumComponents() const { return m_numComponents; }

        void setStride(int _stride) { m_stride = _stride; }
        void setOffset(int _offset) { m_offset = _offset; }
        int getStride() const { return m_stride; }
        int getOffset() const { return m_offset; }

    private:
        /* Generated Vbo ID */
        GLuint m_ID;

        /* If ID should be regenerated for new data */
        bool m_dirty;

        /* Reference to the Vao storing the this Vbo */
        std::weak_ptr<Vao> m_vao;

        /* Data stored and information */
        std::vector<float> m_data;
        int m_numComponents;

        /* Distance between consecutive attributes */
        int m_stride;
        /* Offset of the first attribute in the buffer */
        int m_offset;

        /* Unique ID identifier for each Vbo */
        int vboIdentifierID;
        static int count;
    };
}
