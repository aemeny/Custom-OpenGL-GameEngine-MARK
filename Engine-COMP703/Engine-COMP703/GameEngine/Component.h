#pragma once
#include "Camera.h"

#include <glm/glm.hpp>
#include <memory>
#include <string>

namespace GameEngine
{
	struct Entity;

	struct Component
	{
		/* Calls the override function onTick() for all child components */
		void tick();
		/* Calls the override function onDisplay() for all child components */
		void display();
		/* Calls the override function onGUIRender() for all child components */
		void GUIRender();
		
		/* Holds the name of a child component type */
		std::string m_componentType;
	private:
		friend Entity;

		/* Object reference to the parent entity */
		std::weak_ptr<Entity> m_entity;

		/* Calls on inherited overridden initialize functions */
		virtual void initialize();
		/* Calls on inherited overridden initialize function for the Camera */
		virtual void initialize(CameraProjection _projectionType, std::optional<PerspectiveParamaters> _perspectibeParams);

		/* Calls on inherited overridden tick functions */
		virtual void onTick();

		/* Calls on inherited overridden display functions */
		virtual void onDisplay();

		/* Calls on inherited overridden GUI render functions */
		virtual void onGUIRender();

		/* returns deltatime from Core */
		double getDeltaTime();
	};
}