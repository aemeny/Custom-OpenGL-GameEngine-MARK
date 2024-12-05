#include "Entity.h"

namespace GameEngine
{
	Entity::Entity() {}

	void Entity::tick()
	{
		for (std::shared_ptr<Component> component : m_components)
		{
			
		}
	}

	void Entity::display()
	{
		for (std::shared_ptr<Component> component : m_components)
		{

		}
	}
}