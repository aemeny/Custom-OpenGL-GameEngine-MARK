/*
 * File: BoxCollider.cpp
 * Author: Alex Emeny
 * Date: December 28th, 2024 (Last Edited)
 * Description: This file implements the methods declared in BoxCollider.h.
 *              It implements the functions for initializing and updating physicals based handling.
 *				This struct handles collision based responses based on AABB's.
 */

#include "BoxCollider.h"
#include "RigidBody.h"
#include "../GameEngine/Core.h"

namespace PhysicsSystem
{
    void AABBCollider::initialize()
    {
        m_colliderOffset = glm::vec3(0.0f);
        m_colliderSize = glm::vec3(1.0f);

        m_lineRendererDirty = true;
        m_isKinematic = false;
        m_collision = false;
        m_isTrigger = false;

        /* Checks if a rigid body exists on this entity */
        std::weak_ptr<RigidBody> rigidBodyPtr = m_entity.lock()->findComponent<RigidBody>();
        if (!rigidBodyPtr.expired())
        {
            m_rigidBodyPtr = rigidBodyPtr;
        }
    }

    void AABBCollider::onDisplay()
    {
        if (m_renderOutline)
        {
            updateDebugOutline();
        }
    }

    void AABBCollider::onAABBCollisionUpdate(const std::vector<std::weak_ptr<AABBCollider>>& _AABBColliders)
    {
        m_collision = false;
        for (size_t ci = 0; ci < _AABBColliders.size(); ++ci)
        {
            if (_AABBColliders.at(ci).lock().get() != this)
            {
                if (checkCollision(_AABBColliders.at(ci)))
                {
                    m_collision = true;
                    if (!isTriggerCollider() || !_AABBColliders.at(ci).lock()->isTriggerCollider())
                    {
                        if (m_isKinematic == false)
                        {
                            resolveCollision(_AABBColliders.at(ci));
                        }
                    }
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

        /* Determine which side we are on using the dot product */
        glm::vec3 centerA = (minA + maxA) * 0.5f;
        glm::vec3 centerB = (minB + maxB) * 0.5f;

        glm::vec3 collisionDirection = centerA - centerB;

        /* Adjust penetration depth based on the collision direction */
        penetrationDepth.x *= (glm::dot(collisionDirection, glm::vec3(1.0f, 0.0f, 0.0f)) > 0.0f) ? 1.0f : -1.0f;
        penetrationDepth.y *= (glm::dot(collisionDirection, glm::vec3(0.0f, 1.0f, 0.0f)) > 0.0f) ? 1.0f : -1.0f;
        penetrationDepth.z *= (glm::dot(collisionDirection, glm::vec3(0.0f, 0.0f, 1.0f)) > 0.0f) ? 1.0f : -1.0f;

        glm::vec3 currentPosition = getEntityTransform().lock()->getPosition();
        getEntityTransform().lock()->setPosition(currentPosition + penetrationDepth);

        
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

    void AABBCollider::updateDebugOutline()
    {
        if (m_lineRendererDirty)
        {
            m_lineRendererDirty = false;

            /* Grab debug line renderer from core */
            if (m_lineRenderer.expired())
            {
                m_lineRenderer = m_entity.lock()->m_corePtr.lock()->m_lineRenderer;
            }
            /* Make sure a vbo exists for this line data */
            if (m_vbo.expired())
            {
                m_vbo = m_lineRenderer.lock()->addVbo();
            }

            /* Refresh data inside */
            m_lineRenderer.lock()->clearLines(m_vbo);
            
            glm::vec3 CP = m_entity.lock()->m_transformPtr.lock()->getPosition() + m_colliderOffset; // Collider Position
            glm::vec3 HCS = m_colliderSize * 0.5f; // Half the collider size

            /* Position at each vertex of the box collider */
            glm::vec3 pos1(CP.x + HCS.x, CP.y + HCS.y, CP.z + HCS.z);
            glm::vec3 pos2(CP.x + HCS.x, CP.y + HCS.y, CP.z - HCS.z);
            glm::vec3 pos3(CP.x + HCS.x, CP.y - HCS.y, CP.z + HCS.z);
            glm::vec3 pos4(CP.x - HCS.x, CP.y + HCS.y, CP.z + HCS.z);
            glm::vec3 pos5(CP.x - HCS.x, CP.y - HCS.y, CP.z - HCS.z);
            glm::vec3 pos6(CP.x - HCS.x, CP.y - HCS.y, CP.z + HCS.z);
            glm::vec3 pos7(CP.x - HCS.x, CP.y + HCS.y, CP.z - HCS.z);
            glm::vec3 pos8(CP.x + HCS.x, CP.y - HCS.y, CP.z - HCS.z);

            /* Adds a line between adjacent box positions */
            m_lineRenderer.lock()->addLine(m_vbo, pos1, pos2);
            m_lineRenderer.lock()->addLine(m_vbo, pos1, pos3);
            m_lineRenderer.lock()->addLine(m_vbo, pos1, pos4);
            m_lineRenderer.lock()->addLine(m_vbo, pos5, pos6);
            m_lineRenderer.lock()->addLine(m_vbo, pos5, pos7);
            m_lineRenderer.lock()->addLine(m_vbo, pos5, pos8);
            m_lineRenderer.lock()->addLine(m_vbo, pos6, pos3);
            m_lineRenderer.lock()->addLine(m_vbo, pos8, pos3);
            m_lineRenderer.lock()->addLine(m_vbo, pos8, pos2);
            m_lineRenderer.lock()->addLine(m_vbo, pos7, pos2);
            m_lineRenderer.lock()->addLine(m_vbo, pos7, pos4);
            m_lineRenderer.lock()->addLine(m_vbo, pos6, pos4);
        }
    }
}
