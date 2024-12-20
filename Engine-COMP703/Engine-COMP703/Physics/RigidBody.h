/*
 *  File: RigidBody.h
 *  Author: Alex Emeny
 *  Date: December 20th, 2024 (Last Edited)
 *  Description: This file contains the RigidBody struct,
 *               It defines functions for updating physicals based movement.
 *               This struct handles updating movement with forces such as gravity.
 */

#pragma once
#include "PhysicsComponent.h"

namespace PhysicsSystem
{
    struct RigidBody : PhysicsComponent
    {
        /* Override component functions */
        void initialize() override;
        void onRigidBodyUpdate() override;

        /* Variable Setters */
        void setVelocity(const glm::vec3& _velocity) { m_velocity = _velocity; }
        void addForce(const glm::vec3& _force) { m_acceleration += _force / m_mass; }
        void setMass(float _mass) { m_mass = (_mass > 0.1f) ? _mass : 0.1f; }
        void setUseGravity(bool _useGravity) { m_useGravity = _useGravity; }
        void setGravity(glm::vec3 _gravity) { m_gravity = _gravity; }

        /* Variable Getters */
        glm::vec3 getVelocity() { return m_velocity; }

    private:
        /* Physics based variables */
        glm::vec3 m_velocity;
        glm::vec3 m_acceleration;
        float m_mass;
        bool m_useGravity;
        glm::vec3 m_gravity;
    };
}