/*
 * File: PhysicsCore.cpp
 * Author: Alex Emeny
 * Date: December 19th, 2024 (Last Edited)
 * Description: This file implements the methods declared in PhysicsCore.h.
 *              It implements the functions for initializing and updating physicals based handling.
 */

#include "PhysicsCore.h"
#include "../GameEngine/Entity.h"

namespace PhysicsSystem
{
    PhysicsCore::PhysicsCore(){}

    /* Ticks through all Entities with Physics Components */
    void PhysicsCore::physicsTick()
    {
        /* For all the physics entities tick their Rigid Body update first then AABB collision */
        for (int ei = 0; ei < m_physicsBasedEntities.size(); ++ei)
        {
            for (int ci = 0; ci < m_physicsBasedEntities.at(ei).lock()->m_physicsComponents.size(); ++ci)
            {
                m_physicsBasedEntities.at(ei).lock()->m_physicsComponents.at(ci)->rigidBodyUpdate();
            }
            for (int ci = 0; ci < m_physicsBasedEntities.at(ei).lock()->m_physicsComponents.size(); ++ci)
            {
                m_physicsBasedEntities.at(ei).lock()->m_physicsComponents.at(ci)->AABBCollisionUpdate(m_AABBColliders);
            }
        }
    }

    /* Adds non duplicate entities to the vector for physics tick updates */
    void PhysicsCore::addPhysicsEntity(const std::weak_ptr<GameEngine::Entity>& _passedEntity)
    {
        /* Check whether the entity is already stored within the vector */
        for (int ei = 0; ei < m_physicsBasedEntities.size(); ++ei)
        {
            if (_passedEntity.lock() == m_physicsBasedEntities.at(ei).lock())
            {
                return;
            }
        }

        /* Add new entity to vector of physics based entity to be updated */
        m_physicsBasedEntities.push_back(_passedEntity);
    }
}