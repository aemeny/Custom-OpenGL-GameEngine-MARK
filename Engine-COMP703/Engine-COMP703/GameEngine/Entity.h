#pragma once
#include "Component.h"

#include <vector>
#include <optional>

namespace GameEngine
{
	struct Module;

	struct Entity
	{
		/* Basic constructor as placeholder */
		Entity();

		/* Loops through all Components and calls tick on them */
		void tick();

		/* Loops through all Components and calls display on them */
		void display();

		/* Loops through all Components and calls GUI on them to render */
		void GUIDisplay();

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
		}

		/* Initializes a new Component of type passed and add it to this Entities vector.
		 * All Components have an initialize override which is called here
		 * in par with setting the required variables shared. */
		template <typename T>
		std::shared_ptr<T> addComponent()
		{
			std::shared_ptr<T> rtn = std::make_shared<T>();

			rtn->m_entity = m_self;
			rtn->m_componentType = typeid(T).name();
			rtn->initialize();

			m_components.push_back(rtn);

			return rtn;
		}

		/* Initialize polymorphism for the Camera Component for it's required variables */
		template <typename T>
		std::shared_ptr<Camera> addComponent(CameraProjection _projectionType, std::optional<PerspectiveParamaters> _perspectibeParams = std::nullopt) 
		{
			std::shared_ptr<T> rtn = std::make_shared<T>();

			rtn->m_entity = m_self;
			rtn->m_componentType = typeid(T).name();
			rtn->initialize(_projectionType, _perspectibeParams);

			m_components.push_back(rtn);

			return rtn;
		}

	private:
		friend Component;
		friend Module;

		/* returns deltatime from Core */
		double getDeltaTime();

		/* Vector of game components which handle all their independent functions */
		std::vector<std::shared_ptr<Component>> m_components;

		/* Weak reference to Module parent to call for any required functions */
		std::weak_ptr<Module> m_modulePtr;

		/* Weak reference to its self to pass to its Components */
		std::weak_ptr<Entity> m_self;
	};
}