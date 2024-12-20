/*
 * File: PhysicsComponent.cpp
 * Author: Alex Emeny
 * Date: December 20th, 2024 (Last Edited)
 * Description: This file implements the methods declared in PhysicsComponent.h.
 *              It implements the functions for updating inherited physicals based handling.
 *              This struct handles calling on child components.
 */

#include "PhysicsComponent.h"

namespace PhysicsSystem
{
    /* Calls the override function onRigidBodyUpdate() for all child components */
    void PhysicsComponent::rigidBodyUpdate()
    {
        onRigidBodyUpdate();
    }

    /* Calls the override function onRigidBodyUpdate() for all child components */
    void PhysicsComponent::AABBCollisionUpdate(const std::vector<std::weak_ptr<AABBCollider>>& _AABBColliders)
    {
        onAABBCollisionUpdate(_AABBColliders);
    }

    /* Calls on inherited overridden Rigid Body update functions */
    void PhysicsComponent::onRigidBodyUpdate(){}
    
    /* Calls on inherited overridden Rigid Body update functions */
    void PhysicsComponent::onAABBCollisionUpdate(const std::vector<std::weak_ptr<AABBCollider>>& _AABBColliders){}
}