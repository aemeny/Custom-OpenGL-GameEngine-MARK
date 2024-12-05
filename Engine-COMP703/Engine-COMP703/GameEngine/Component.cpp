#include "Component.h"
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
		onDisplay();
	}

	/* returns deltatime from Core */
	double Component::getDeltaTime()
	{
		return m_entity.lock()->getDeltaTime();
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