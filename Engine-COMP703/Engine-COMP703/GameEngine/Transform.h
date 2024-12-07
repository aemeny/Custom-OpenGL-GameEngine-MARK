/*
 *  File: Transform.h
 *  Author: Alex Emeny
 *  Date: December 7th, 2024 (Last Edited)
 *  Description: This file contains the Transform struct,
 *               It defines functions for initializing and updating model matrix related handling.
 *               This struct handles returning the vital model matrix for positioning.
 */

#pragma once
#include "Component.h"

namespace GameEngine
{
    struct Transform : Component
    {
        void initialize() override;

        /* Updates the model matrix by scale, rotation and position */
        void updateMatrix();

    private:
        glm::vec3 m_position;
        glm::vec3 m_rotation;
        glm::vec3 m_scale;

        glm::mat4 m_modelMatrix;
    };
}