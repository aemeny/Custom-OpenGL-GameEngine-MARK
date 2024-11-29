#pragma once
#include "Component.h"

namespace GameEngine
{
	struct Module;

	struct Entity
	{
		Entity();

		std::vector<std::shared_ptr<Component> > m_components;
	};
}