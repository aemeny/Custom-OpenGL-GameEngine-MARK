/*
 *  File: BoxCollider.h
 *  Author: Alex Emeny
 *  Date: December 18th, 2024 (Last Edited)
 *  Description: This file contains the BoxCollider struct,
 *               It defines functions for initializing and updating physicals based handling.
 *               This struct handles collision based responses based on AABB's.
 */

#pragma once
#include "PhysicsComponent.h"

namespace PhysicsSystem
{
    struct AABBCollider : PhysicsComponent
    {
        /* Override component functions */
        void initialize() override;
        void onPhysicsUpdate() ;
        
        /* Components variable setters */
        void setColliderSize(glm::vec3 _size) { m_colliderSize = _size; }
        void setColliderOffset(glm::vec3 _offset) { m_colliderOffset = _offset; }

    private:
        /* Offsets the collider from the entities transform */
        glm::vec3 m_colliderOffset;

        /* Scale of the box collider */
        glm::vec3 m_colliderSize;
    };
}