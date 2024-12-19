/*
 * File: BoxCollider.cpp
 * Author: Alex Emeny
 * Date: December 19th, 2024 (Last Edited)
 * Description: This file implements the methods declared in BoxCollider.h.
 *              It implements the functions for initializing and updating physicals based handling.
 *				This struct handles collision based responses based on AABB's.
 */

#include "BoxCollider.h"

namespace PhysicsSystem
{
    void AABBCollider::initialize()
    {
        m_colliderOffset = glm::vec3(0);
        m_colliderSize = glm::vec3(1);
    }
    void AABBCollider::onPhysicsUpdate()
    {

    }
}
