/*
 *  File: Entity.h
 *  Author: Alex Emeny
 *  Date: December 19th, 2024 (Last Edited)
 *  Description: This file contains the Entity struct,
 *               It defines functions for adding, finding and calling on Components.
 *               This struct handles storing and managing it's Components.
 */

#pragma once
#include "../Physics/PhysicsComponent.h"

#include <vector>
#include <stdexcept>

namespace PhysicsSystem { struct PhysicsCore; struct AABBCollider; struct RigidBody; }
namespace GameEngine
{
	struct Module;
	struct Transform;

	struct Entity
	{
		/* Setter and getter for the active status of this entity */
		bool getActiveStatus() { return m_active; }
		void setActiveStatus(bool _active) { m_active = _active; }

		/* Returns a Component of any type that is passed into it.
		 * Checks through all Components within the Entity for a matching type. */
		template <typename T>
		std::weak_ptr<T> findComponent()
		{
			for (size_t i = 0; i < m_components.size(); ++i)
			{
				// Returns Component if found with matching type
				if (m_components.at(i)->m_componentType == typeid(T).name())
				{
					return std::dynamic_pointer_cast<T>(m_components.at(i));
				}
			}
			for (size_t i = 0; i < m_physicsComponents.size(); ++i)
			{
				// Returns Component if found with matching type
				if (m_physicsComponents.at(i)->m_componentType == typeid(T).name())
				{
					return std::dynamic_pointer_cast<T>(m_physicsComponents.at(i));
				}
			}
		}

		/* Initializes a new Component of type passed and add it to this Entities vector.
		 * All Components have an initialize override which is called here
		 * in par with setting the required variables shared. */
		template <typename T>
		std::shared_ptr<T> addComponent() 
		{
			/* Create shared pointer */
			std::shared_ptr<T> rtn = std::make_shared<T>();

			/* Check whether incoming component is a physics component or game engine component */
			if constexpr (std::is_base_of<PhysicsSystem::PhysicsComponent, T>::value)
			{
				/* Adds new Component to list of physics components */
				if constexpr (std::is_same<T, PhysicsSystem::AABBCollider>::value)
				{
					/* Add to the specialized AABB list */
					m_corePtr.lock()->m_physicsCore->m_AABBColliders.push_back(
						std::dynamic_pointer_cast<PhysicsSystem::AABBCollider>(rtn)
					);
				}

				m_physicsComponents.push_back(rtn);

				/* Pass this entity to the physics core to be added as a physics entity*/
				m_corePtr.lock()->m_physicsCore->addPhysicsEntity(m_self);
			}
			else if constexpr (std::is_base_of<Component, T>::value)
			{
				/* Check to see if camera creation is attempted within the wrong function */
				if (typeid(T).name() == "Camera")
				{
					throw std::invalid_argument("Camera type should call addComponent(CameraProjection)");
					return NULL;
				}

				/* Adds new Component to list of components */
				m_components.push_back(rtn);
			}
			else
			{
				/* throw error if neither */
				static_assert(std::is_base_of<GameEngine::Component, T>::value ||
					std::is_base_of<PhysicsSystem::PhysicsComponent, T>::value,
					"Passed object must inherit from either GameEngine::Component or PhysicsSystem::PhysicsComponent");
				return NULL;
			}

			/* Objects variables Initialize */
			rtn->m_entity = m_self;
			rtn->m_corePtr = m_corePtr;
			rtn->m_componentType = typeid(T).name();
			rtn->initialize();

			return rtn;
		}

		/* Initialize polymorphism for the Camera Component for it's required variables */
		template <typename T>
		std::shared_ptr<Camera> addComponent(CameraProjection _projectionType, std::optional<PerspectiveParamaters> _perspectibeParams = std::nullopt) 
		{
			std::shared_ptr<T> rtn = std::make_shared<T>();

			/* Objects variables Initialize */
			rtn->m_entity = m_self;
			rtn->m_corePtr = m_corePtr;
			rtn->m_componentType = typeid(T).name();
			rtn->initialize(_projectionType, rtn, _perspectibeParams);

			/* Adds Camera to list of components */
			m_components.push_back(rtn);

			/* Add the new camera as a weak ref in core */
			m_corePtr.lock()->m_cameras.push_back(rtn);

			return rtn;
		}

	private:
		friend Module;
		friend Camera;
		friend Component;
		friend PhysicsSystem::PhysicsCore;
		friend struct ModelHandler;

		/* Loops through all Components and calls tick on them */
		void tick();

		/* Loops through all Components and calls render on them */
		void render();

		/* Loops through all Components and calls GUI on them to render */
		void GUIRender();

		/* Loops through all Components and calls lateTick on them */
		void lateTick();

		/* If the entity is active, deactivated entities won't call render or tick */
		bool m_active;

		/* Vector of game components which handle all their independent functions */
		std::vector<std::shared_ptr<Component>> m_components;

		/* Vector of game physics components which handles all their independent functions */
		std::vector<std::shared_ptr<PhysicsSystem::PhysicsComponent>> m_physicsComponents;

		/* Weak reference to Module parent to call for any required functions */
		std::weak_ptr<Module> m_modulePtr;

		/* Weak reference to its self to pass to its Components */
		std::weak_ptr<Entity> m_self;

		/* Weak reference to core to call for any required functions e.g. deltatime */
		std::weak_ptr<Core> m_corePtr;

		/* Weak reference to its assigned transform component to return to its Components */
		std::weak_ptr<Transform> m_transformPtr;
	};
}