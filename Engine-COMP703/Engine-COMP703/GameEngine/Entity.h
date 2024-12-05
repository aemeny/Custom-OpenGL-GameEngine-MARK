#pragma once
#include "Component.h"

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

	private:
		/* Vector of game components which handle all their independant functions */
		std::vector<std::shared_ptr<Component>> m_components;
	};
}