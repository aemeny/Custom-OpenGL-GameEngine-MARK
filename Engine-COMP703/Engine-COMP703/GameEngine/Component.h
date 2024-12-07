/*
 *  File: Component.h
 *  Author: Alex Emeny
 *  Date: December 6th, 2024 (Last Edited)
 *  Description: This file contains the Component struct,
 *               It defines functions for initializing and calling on inherited Components.
 *               This struct is a parent for any Component that will be added to an Entity.
 */

#pragma once
#include "CameraTypes.h"

#include <memory>
#include <string>
#include <optional>

namespace GameEngine
{
	struct Entity;
	struct Core;
	struct Camera;
	struct Window;

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

		/* Weak reference to core to call for any required functions e.g. deltatime */
		std::weak_ptr<Core> m_corePtr;

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

	protected:
		/* returns deltatime from Core */
		double getDeltaTime();

		/* returns Window handler from Core */
		std::weak_ptr<Window> getWindowFromCore();

		/* Object reference to the parent entity */
		std::weak_ptr<Entity> m_entity;
	};
}