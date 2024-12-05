#include "Entity.h"
#include "Core.h"

namespace GameEngine
{
	Entity::Entity() {}

	void Entity::tick()
	{
		for (size_t ci = 0; ci < m_components.size(); ++ci)
		{
			m_components.at(ci)->tick();
		}
	}

	void Entity::display()
	{
		for (size_t ci = 0; ci < m_components.size(); ++ci)
		{
			m_components.at(ci)->display();
		}
	}

	void Entity::GUIDisplay()
	{
		for (size_t ci = 0; ci < m_components.size(); ++ci)
		{
			m_components.at(ci)->GUIRender();
		}
	}

	/* returns deltatime from Core */
	double Entity::getDeltaTime()
	{
		return m_modulePtr.lock()->getDeltaTime();
	}
}