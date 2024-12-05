#pragma once
#include "Core.h"

namespace GameEngine
{
	struct Component
	{
		/* Object reference to the parent entity */
		std::weak_ptr<Entity> m_entity;

		void tick();
		void display();
	private:
		friend Entity;

		/* Calls display on inherited overrided tick functions */
		virtual void onTick();

		/* Calls display on inherited overrided display functions */
		virtual void onDisplay();

		/* returns deltatime from Core */
		double getDeltaTime() { return /*m_entity.lock()->;*/ 0.0f; } // IMPLEMENT
	};
}