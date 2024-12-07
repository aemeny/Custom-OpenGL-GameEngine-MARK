/*
 *  File: Module.cpp
 *  Author: Alex Emeny
 *  Date: December 6th, 2024 (Last Edited)
 *  Description: This file implements the methods declared in Module.h,
 *               It implements the functions for for adding and calling on Entites.
 *
 *               MODULE can be seen as a modified version on Unity's "Scene" system.
 *               This allows mass loading or unloading of areas of entities.
 *               It can allow multiple loaded Modules at once with relative positions.
 */

#include "Core.h"
#include "Transform.h"

namespace GameEngine
{
	Module::Module() : m_relativePosition(0) {}

	/* Creates a new Entity, adds them to the modules vector and returns for user use */
	std::shared_ptr<Entity> Module::addEntity()
	{
		std::shared_ptr rtn = std::make_shared<Entity>();

		/* Assign variables */
		rtn->m_modulePtr = m_self;
		rtn->m_corePtr = m_corePtr;
		rtn->m_self = rtn;

		/* Each Entity starts with a Transform Component */
		rtn->addComponent<Transform>();

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
			m_entities.at(ei)->tick();
		}
	}

	/* Loops through all Entities and calls display on them */
	void Module::render()
	{
		for (size_t ei = 0; ei < m_entities.size(); ++ei)
		{
			m_entities.at(ei)->render();
		}
	}

	/* Loops through all Entities and calls GUI on them to render */
	void Module::GUIRender()
	{
		for (size_t ei = 0; ei < m_entities.size(); ++ei)
		{
			m_entities.at(ei)->GUIRender();
		}
	}

	/* Loads and Unloads the entities within this module */
	void Module::load(){} /// Currently not in use
	void Module::unload(){} /// Currently not in use
}