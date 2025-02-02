/*
 *  File: Entity.cpp
 *  Author: Alex Emeny
 *  Date: December 6th, 2024 (Last Edited)
 *  Description: This file implements the methods declared in Entity.h
 *               It implements the functions for calling on it's Components,
 */

#include "Entity.h"

namespace GameEngine
{
	/* Loops through all Components and calls tick on them */
	void Entity::tick()
	{
		for (size_t ci = 0; ci < m_components.size(); ++ci)
		{
			m_components.at(ci)->tick();
		}
		for (size_t pci = 0; pci < m_physicsComponents.size(); pci++)
		{
			m_physicsComponents.at(pci)->tick();
		}
	}

	/* Loops through all Components and calls display on them */
	void Entity::render()
	{
		for (size_t ci = 0; ci < m_components.size(); ++ci)
		{
			m_components.at(ci)->display();
		}
		for (size_t pci = 0; pci < m_physicsComponents.size(); pci++)
		{
			m_physicsComponents.at(pci)->display();
		}
	}

	/* Loops through all Components and calls GUI on them to render */
	void Entity::GUIRender()
	{
		for (size_t ci = 0; ci < m_components.size(); ++ci)
		{
			m_components.at(ci)->GUIRender();
		}
		for (size_t pci = 0; pci < m_physicsComponents.size(); pci++)
		{
			m_physicsComponents.at(pci)->GUIRender();
		}
	}

	/* Loops through all Components and calls lateTick on them */
	void Entity::lateTick()
	{
		for (size_t ci = 0; ci < m_components.size(); ++ci)
		{
			m_components.at(ci)->lateTick();
		}
		for (size_t pci = 0; pci < m_physicsComponents.size(); pci++)
		{
			m_physicsComponents.at(pci)->lateTick();
		}
	}
}