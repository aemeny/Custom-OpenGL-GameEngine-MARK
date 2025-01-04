/*
 *  File: Transform.cpp
 *  Author: Alex Emeny
 *  Date: December 7th, 2024 (Last Edited)
 *  Description: This file implements the methods declared in transform.h,
 *               It implements the functions for initializing and updating model matrix related handling.
 */

#include "Transform.h"
#include <glm/ext.hpp>

namespace GameEngine
{
    void Transform::initialize()
    {
        m_position = glm::vec3(0.0f);
        m_rotation = glm::vec3(0.0f);
        m_scale = glm::vec3(1.0f);
        m_modelMatrix = glm::mat4(1.0f);
    }

    void Transform::updateMatrix()
    {
        /* Start with identity matrix */
        m_modelMatrix = glm::mat4(1.0f);


        /* Apply translation */
        m_modelMatrix = glm::translate(m_modelMatrix, m_position);

        /* Apply scale */
        m_modelMatrix = glm::scale(m_modelMatrix, m_scale);

        /* Apple rotation(X->Y->Z) */
        m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    }
}