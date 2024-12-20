/*
 *  File: PhysicComponent.h
 *  Author: Alex Emeny
 *  Date: December 20th, 2024 (Last Edited)
 *  Description: This file contains the PhysicsComponent struct,
 *               It defines functions for updating inherited physicals based handling.
 *               This struct handles calling on child components.
 */

#pragma once
#include "../GameEngine/Component.h"
#include "../GameEngine/Transform.h"

#include <vector>

namespace PhysicsSystem
{
    struct AABBCollider;
    struct PhysicsComponent : GameEngine::Component
    {
        /* Calls the override function onRigidBodyUpdate() for all child components */
        void rigidBodyUpdate();
        
        /* Calls the override function onRigidBodyUpdate() for all child components */
        void AABBCollisionUpdate(const std::vector<std::weak_ptr<AABBCollider>>& _AABBColliders);

    protected:
        /* Calls on inherited overridden Rigid Body update functions */
        virtual void onRigidBodyUpdate();
        
        /* Calls on inherited overridden Rigid Body update functions */
        virtual void onAABBCollisionUpdate(const std::vector<std::weak_ptr<AABBCollider>>& _AABBColliders);
    };
}