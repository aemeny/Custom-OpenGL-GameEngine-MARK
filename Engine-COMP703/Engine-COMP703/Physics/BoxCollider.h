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
#include "../GameEngine/LineRenderer.h"
#include "../Graphics/Vao.h"

namespace PhysicsSystem
{
    struct RigidBody;
    struct AABBCollider : PhysicsComponent
    {
        /* Override component functions */
        void initialize() override;
        void onDisplay() override;
        void onAABBCollisionUpdate(const std::vector<std::weak_ptr<AABBCollider>>& _AABBColliders) override;
        
        /* Checks if this collider is colliding with passed collider */
        bool checkCollision(const std::weak_ptr<AABBCollider>& _other) const;

        /* Checks if this is colliding with frustum planes */
        bool checkCollision(const std::array<FrustumPlane, 6>& _frustumPlanes) const;

        /* Resolves the conflict if found by moving the collider's transform */
        void resolveCollision(const std::weak_ptr<AABBCollider>& _other);

        /* Components variable setters */
        void setColliderSize(glm::vec3 _size) { m_colliderSize = _size; }
        void setColliderOffset(glm::vec3 _offset) { m_colliderOffset = _offset; }

        /* If the debug outline should be rendered */
        void setRenderOutline(bool _render) { m_renderOutline = _render; }

        void setKinematicState(bool _isKinematic) { m_isKinematic = _isKinematic; }
        bool hasCollided() const { return m_collision; }

        void setTriggerCollider(bool _value) { m_isTrigger = _value; }
        bool isTriggerCollider() const { return m_isTrigger; }

        /* Loops through all names collided with to compare with passed name */
        bool ifCollidedWithName(std::string _name);
    private:
        friend RigidBody;

        glm::vec3 getMax() const;
        glm::vec3 getMin() const;

        bool m_isKinematic;
        bool m_isTrigger;

        /* If a collision has been made on this frame */
        bool m_collision;

        /* Pushes updates box collider size to LineRenderer */
        void updateDebugOutline();

        /* Offsets the collider from the entities transform */
        glm::vec3 m_colliderOffset;

        /* Scale of the box collider */
        glm::vec3 m_colliderSize;

        /* Reference to a potential rigid body on entity */
        std::weak_ptr<RigidBody> m_rigidBodyPtr;

        /* Debug outline render */
        std::weak_ptr<GameEngine::LineRenderer> m_lineRenderer;
        std::weak_ptr<GraphicsRenderer::Vbo> m_vbo;
        bool m_renderOutline;
        bool m_lineRendererDirty;

        /* Keeps track of entity names which have been collided with this frame */
        std::vector<std::string> m_names;
    };
}