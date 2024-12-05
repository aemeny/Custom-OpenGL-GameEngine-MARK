#pragma once
#include "Entity.h"

namespace GameEngine
{
	struct Core;

	struct Module
	{
		friend Core;

		/* Basic constructor that passes a pointer to the engines core */
		Module(std::weak_ptr<Core> _corePtr);

		/* Creates a new Entity, adds them to the modules vector and returns for user use */
		std::shared_ptr<Entity> addEntity();

		/* Loops through all Entities and calls tick on them */
		void tick();

		/* Loops through all Entities and calls display on them */
		void display();

		/* Loads and Unloads the entites within this module */
		void load(); /// Currently not in use
		void unload(); /// Currently not in use

		/* Relative positon of the module of entities so they can be loaded ahead of time within the same world at different locations */
		glm::vec3 m_relativePosition;

	private:
		/* Vector of game entities which handle all their relevant components */
		std::vector<std::shared_ptr<Entity>> m_entities;

		/* weak reference to core to call for any required functions e.g. deltatime */
		std::weak_ptr<Core> m_corePtr;
	};
}