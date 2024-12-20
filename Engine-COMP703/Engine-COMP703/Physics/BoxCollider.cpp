/*
 * File: BoxCollider.cpp
 * Author: Alex Emeny
 * Date: December 20th, 2024 (Last Edited)
 * Description: This file implements the methods declared in BoxCollider.h.
 *              It implements the functions for initializing and updating physicals based handling.
 *				This struct handles collision based responses based on AABB's.
 */

#include "BoxCollider.h"
#include "RigidBody.h"
#include "../GameEngine/Entity.h"

namespace PhysicsSystem
{
    void AABBCollider::initialize()
    {
        m_colliderOffset = glm::vec3(0.0f);
        m_colliderSize = glm::vec3(1.0f);

        /* Checks if a rigid body exists on this entity */
        std::weak_ptr<RigidBody> rigidBodyPtr = m_entity.lock()->findComponent<RigidBody>();
        if (!rigidBodyPtr.expired())
        {
            m_rigidBodyPtr = rigidBodyPtr;
        }
    }

    void AABBCollider::onAABBCollisionUpdate(const std::vector<std::weak_ptr<AABBCollider>>& _AABBColliders)
    {
        for (size_t ci = 0; ci < _AABBColliders.size(); ++ci)
        {
            if (_AABBColliders.at(ci).lock().get() != this)
            {
                if (checkCollision(_AABBColliders.at(ci)))
                {
                    resolveCollision(_AABBColliders.at(ci));
                }
            }
        }
    }

    /* Checks if this collider is colliding with passed collider */
    bool AABBCollider::checkCollision(const std::weak_ptr<AABBCollider>& _other) const
    {
        glm::vec3 minA = getMin();
        glm::vec3 maxA = getMax();
        glm::vec3 minB = _other.lock()->getMin();
        glm::vec3 maxB = _other.lock()->getMax();

        /* Returns if in bound of other collision box */
        return (maxA.x > minB.x && minA.x < maxB.x) &&
               (maxA.y > minB.y && minA.y < maxB.y) &&
               (maxA.z > minB.z && minA.z < maxB.z);
    }

    /* Resolves the conflict if found by moving the collider's transform */
    void AABBCollider::resolveCollision(const std::weak_ptr<AABBCollider>& _other)
    {
        glm::vec3 minA = getMin();
        glm::vec3 maxA = getMax();
        glm::vec3 minB = _other.lock()->getMin();
        glm::vec3 maxB = _other.lock()->getMax();

        /* Find the depth of the collision box intersection */
        glm::vec3 penetrationDepth = glm::vec3(
            std::min(maxA.x - minB.x, maxB.x - minA.x),
            std::min(maxA.y - minB.y, maxB.y - minA.y),
            std::min(maxA.z - minB.z, maxB.z - minA.z)
        );

        /* Find the smallest axis of penetration */
        if (penetrationDepth.x < penetrationDepth.y && penetrationDepth.x < penetrationDepth.z)
        {
            penetrationDepth.y = penetrationDepth.z = 0.0f;
        }
        else if (penetrationDepth.y < penetrationDepth.x && penetrationDepth.y < penetrationDepth.z)
        {
            penetrationDepth.x = penetrationDepth.z = 0.0f;
        }
        else
        {
            penetrationDepth.x = penetrationDepth.y = 0.0f;
        }

        /* Push the current entity out of the collision */
        getEntityTransform().lock()->setPosition(getEntityTransform().lock()->getPosition() + penetrationDepth);
        
        /* Stop the rigid body's movement in the direction of collision */
        if (!m_rigidBodyPtr.expired())
        {
            glm::vec3 currentVelocity = m_rigidBodyPtr.lock()->getVelocity();
            if (penetrationDepth.x != 0.0f) m_rigidBodyPtr.lock()->setVelocity(glm::vec3(0.0f, currentVelocity.y, currentVelocity.z));
            if (penetrationDepth.y != 0.0f) m_rigidBodyPtr.lock()->setVelocity(glm::vec3(currentVelocity.x, 0.0f, currentVelocity.z));
            if (penetrationDepth.z != 0.0f) m_rigidBodyPtr.lock()->setVelocity(glm::vec3(currentVelocity.x, currentVelocity.y, 0.0f));
        }
    }

    glm::vec3 AABBCollider::getMax() const
    {
        return getEntityTransform().lock()->getPosition() + m_colliderOffset + (m_colliderSize / 2.0f);
    }

    glm::vec3 AABBCollider::getMin() const
    {
        return getEntityTransform().lock()->getPosition() + m_colliderOffset - (m_colliderSize / 2.0f);
    }
}
