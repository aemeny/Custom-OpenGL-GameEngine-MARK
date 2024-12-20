/*
 *  File: PhysicsCore.h
 *  Author: Alex Emeny
 *  Date: December 19th, 2024 (Last Edited)
 *  Description: This file contains the PhysicsCore struct,
 *               It defines functions for initializing and updating physicals based handling.
 *               This struct handles calling on physics based components and storing them.
 */

#pragma once
#include "BoxCollider.h"
#include "RigidBody.h"

#include <vector>

namespace GameEngine { struct Core; struct Entity; } /// Forward declaring
namespace PhysicsSystem
{
    struct PhysicsCore
    {
        PhysicsCore();

    private:
        friend struct GameEngine::Core;
        friend struct GameEngine::Entity;

        /* Ticks through all Entities with Physics Components */
        void physicsTick();
        
        /* Adds non duplicate entities to the vector for physics tick updates */
        void addPhysicsEntity(const std::weak_ptr<GameEngine::Entity>& _passedEntity);

        /* Vector of entities which contains at least one physics component */
        std::vector<std::weak_ptr<GameEngine::Entity>> m_physicsBasedEntities;

        /* Vector of all the AABB created */
        std::vector<std::weak_ptr<AABBCollider>> m_AABBColliders;
    };
}