/*
 * File: RigidBody.cpp
 * Author: Alex Emeny
 * Date: December 20th, 2024 (Last Edited)
 * Description: This file implements the methods declared in RigidBody.h.
 *              It implements the functions for updating physicals based movement.
 *               This struct handles updating movement with forces such as gravity.
 */

#include "RigidBody.h"
#include "BoxCollider.h"
#include "../GameEngine/Entity.h"

namespace PhysicsSystem
{
    void RigidBody::initialize()
    {
        m_velocity = glm::vec3(0.0f);
        m_acceleration = glm::vec3(0.0f);
        m_mass = 1.0f;
        m_useGravity = true;
        m_gravity = glm::vec3(0.0f, -9.81f, 0.0f);

        /* If a AABB collider exists add this rigid body as a pointer */
        std::weak_ptr<AABBCollider> collider = m_entity.lock()->findComponent<AABBCollider>();
        if (!collider.expired())
        {
            collider.lock()->m_rigidBodyPtr = m_entity.lock()->findComponent<RigidBody>();
        }
    }

    void RigidBody::onRigidBodyUpdate()
    {
        /* Apply gravity if active */
        if (m_useGravity)
        {
            m_acceleration += m_gravity;
        }

        /* Calculate velocity from acceleration */
        m_velocity += m_acceleration * static_cast<float>(getDeltaTime());

        /* Calculate new position from velocity */
        glm::vec3 position = getEntityTransform().lock()->getPosition();
        position += m_velocity * static_cast<float>(getDeltaTime());
        getEntityTransform().lock()->setPosition(position);

        /* Reset Acceleration for next frame */
        m_acceleration = glm::vec3(0.0f);
    }
}