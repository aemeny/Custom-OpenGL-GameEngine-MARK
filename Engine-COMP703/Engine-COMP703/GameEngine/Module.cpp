/*
 *  File: Module.cpp
 *  Author: Alex Emeny
 *  Date: December 17th, 2024 (Last Edited)
 *  Description: This file implements the methods declared in Module.h,
 *               It implements the functions for for adding and calling on Entities.
 *
 *               MODULE can be seen as a modified version on Unity's "Scene" system.
 *               This allows mass loading or unloading of areas of entities.
 *               It can allow multiple loaded Modules at once with relative positions.
 */

#include "Core.h"
#include "Transform.h"

namespace GameEngine
{
	/* Creates a new Entity, adds them to the modules vector and returns for user use */
	std::shared_ptr<Entity> Module::addEntity()
	{
		std::shared_ptr rtn = std::make_shared<Entity>();

		/* Assign variables */
		rtn->m_modulePtr = m_self;
		rtn->m_corePtr = m_corePtr;
		rtn->m_self = rtn;
		rtn->m_active = true;

		/* Each Entity starts with a Transform Component */
		rtn->m_transformPtr = rtn->addComponent<Transform>();

		/* Adds created Entity to vector storage in this module */
		m_entities.push_back(rtn);

		/* Returns created Entity for user referencing and use */
		return rtn;
	}

	/* Loops through all Entities and calls tick on them */
	void Module::tick()
	{
		for (size_t ei = 0; ei < m_entities.size(); ++ei)
		{
			if (m_entities.at(ei)->getActiveStatus())
			{
				m_entities.at(ei)->tick();
			}
		}
	}

	/* Loops through all Entities and calls display on them */
	void Module::render()
	{
		for (size_t ei = 0; ei < m_entities.size(); ++ei)
		{
			if (m_entities.at(ei)->getActiveStatus())
			{
				m_entities.at(ei)->render();
			}
		}
	}

	/* Loops through all Entities and calls GUI on them to render */
	void Module::GUIRender()
	{
		for (size_t ei = 0; ei < m_entities.size(); ++ei)
		{
			if (m_entities.at(ei)->getActiveStatus())
			{
				m_entities.at(ei)->GUIRender();
			}
		}
	}

	/* Loads the entities within this module */
	void Module::load() 
	{
		/* Basic implementation just sets active status to true 
		and all entities within WILL be ticked and rendered */
		m_active = true;
	} 

	/* Unloads the entities within this module */
	void Module::unload()
	{
		/* Basic implementation just sets active status to false
		and all entities within WONT be ticked and rendered */
		m_active = false;
	}
}