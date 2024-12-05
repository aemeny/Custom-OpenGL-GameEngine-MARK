#include "Core.h"

namespace GameEngine
{
	Module::Module() : m_relativePosition(0) {}

	/* Creates a new Entity, adds them to the modules vector and returns for user use */
	std::shared_ptr<Entity> Module::addEntity()
	{
		std::shared_ptr rtn = std::make_shared<Entity>();

		/* Assign variables */
		rtn->m_modulePtr = m_self;
		rtn->m_self = rtn;

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
	void Module::display()
	{
		for (size_t ei = 0; ei < m_entities.size(); ++ei)
		{
			m_entities.at(ei)->display();
		}
	}

	void Module::GUIDisplay()
	{
		for (size_t ei = 0; ei < m_entities.size(); ++ei)
		{
			m_entities.at(ei)->GUIDisplay();
		}
	}

	/* returns deltatime from Core */
	double Module::getDeltaTime()
	{
		return m_corePtr.lock()->m_environment->getDeltaTime();
	}

	/* Loads and Unloads the entities within this module */
	void Module::load(){} /// Currently not in use
	void Module::unload(){} /// Currently not in use
}