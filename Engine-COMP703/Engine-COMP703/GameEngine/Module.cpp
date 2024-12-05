#include "Module.h"
#include "Core.h"

namespace GameEngine
{
	Module::Module(std::weak_ptr<Core> _corePtr) : 
		m_relativePosition(0), m_corePtr(_corePtr) {}

	/* Creates a new Entity, adds them to the modules vector and returns for user use */
	std::shared_ptr<Entity> Module::addEntity()
	{
		std::shared_ptr rtn = std::make_shared<Entity>();

		/* Adds created Entity to vector storage in this module */
		m_entities.push_back(rtn);

		/* Returns created Entity for user referencing and use */
		return rtn;
	}

	/* Loops through all Entities and calls tick on them */
	void Module::tick()
	{
		for (std::shared_ptr<Entity> entity : m_entities)
		{
			entity->tick();
		}
	}

	/* Loops through all Entities and calls display on them */
	void Module::display()
	{
		for (std::shared_ptr<Entity> entity : m_entities)
		{
			entity->display();
		}
	}

	/* Loads and Unloads the entites within this module */
	void Module::load(){} /// Currently not in use
	void Module::unload(){} /// Currently not in use
}