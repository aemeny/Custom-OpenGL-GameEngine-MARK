/*
 *  File: BoxCollider.h
 *  Author: Alex Emeny
 *  Date: December 20th, 2024 (Last Edited)
 *  Description: This file contains the BoxCollider struct,
 *               It defines functions for initializing and updating physicals based handling.
 *               This struct handles collision based responses based on AABB's.
 */

#pragma once
#include "PhysicsComponent.h"

namespace PhysicsSystem
{
    struct RigidBody;
    struct AABBCollider : PhysicsComponent
    {
        /* Override component functions */
        void initialize() override;
        void onAABBCollisionUpdate(const std::vector<std::weak_ptr<AABBCollider>>& _AABBColliders) override;
        
        /* Checks if this collider is colliding with passed collider */
        bool checkCollision(const std::weak_ptr<AABBCollider>& _other) const;

        /* Resolves the conflict if found by moving the collider's transform */
        void resolveCollision(const std::weak_ptr<AABBCollider>& _other);

        /* Components variable setters */
        void setColliderSize(glm::vec3 _size) { m_colliderSize = _size; }
        void setColliderOffset(glm::vec3 _offset) { m_colliderOffset = _offset; }

    private:
        friend RigidBody;

        glm::vec3 getMax() const;
        glm::vec3 getMin() const;

        /* Offsets the collider from the entities transform */
        glm::vec3 m_colliderOffset;

        /* Scale of the box collider */
        glm::vec3 m_colliderSize;

        /* Reference to a potential rigid body on entity */
        std::weak_ptr<RigidBody> m_rigidBodyPtr;
    };
}