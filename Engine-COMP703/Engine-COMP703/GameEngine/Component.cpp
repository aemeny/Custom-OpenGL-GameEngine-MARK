/*
 *  File: Component.cpp
 *  Author: Alex Emeny
 *  Date: December 6th, 2024 (Last Edited)
 *  Description: This file implements the methods declared in Component.h
 *               It implements the functions for initializing and calling on inherited Components,
 */

#include "Core.h"

namespace GameEngine
{
	/* Calls the override function onTick() for all child components */
	void Component::tick()
	{
		onTick();
	}

	/* Calls the override function onDisplay() for all child components */
	void Component::display()
	{
		onDisplay();
	}

	/* Calls the override function onGUIRender() for all child components */
	void Component::GUIRender()
	{
		onGUIRender();
	}

	/* returns deltatime from Core */
	double Component::getDeltaTime()
	{
		return m_corePtr.lock()->m_environment->getDeltaTime();
	}

	std::weak_ptr<Window> Component::getWindowFromCore()
	{
		return m_corePtr.lock()->m_windowContext;
	}

	/* Calls on inherited overridden initialize functions */
	void Component::initialize(){}

	/* Calls on inherited overridden initialize function for the Camera */
	void Component::initialize(CameraProjection _projectionType, std::optional<PerspectiveParamaters> _perspectibeParams = std::nullopt){}

	/* Calls on inherited overridden tick functions */
	void Component::onTick(){}

	/* Calls on inherited overridden display functions */
	void Component::onDisplay(){}

	/* Calls on inherited overridden GUI render functions */
	void Component::onGUIRender(){}
}