/*
 *  File: Transform.h
 *  Author: Alex Emeny
 *  Date: December 17th, 2024 (Last Edited)
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

        /* Transform variables setters */
        void setRotation(glm::vec3 _rot) { m_rotation = _rot; }
        void setPosition(glm::vec3 _pos) { m_position = _pos; }
        void setScale(glm::vec3 _scale) { m_scale = _scale; }

        /* Transform variables getters */
        glm::vec3 getRotation() const { return m_rotation; }
        glm::vec3 getPosition() const { return m_position; }
        glm::vec3 getScale() const { return m_scale; }
        glm::mat4 getLocalToWorldMatrix() const;
        glm::mat4 getModelMatrix() const { return m_modelMatrix; }


    private:
        /* Transform specific variables */
        glm::vec3 m_position;
        glm::vec3 m_rotation;
        glm::vec3 m_scale;

        glm::mat4 m_modelMatrix;
    };
}