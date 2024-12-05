#include "Component.h"

namespace GameEngine
{
	Component::Component(){}

	void Component::tick()
	{
		onTick();
	}

	void Component::display()
	{
		onDisplay();
	}

	void Component::onTick() {}
	void Component::onDisplay() {}
}