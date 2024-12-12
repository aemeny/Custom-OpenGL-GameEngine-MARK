/*
 *  File: Core.h
 *  Author: Alex Emeny
 *  Date: December 6th, 2024 (Last Edited)
 *  Description: This file contains the Core struct,
 *               The core of the game engine, this struct holds the main game loop within and is vital
 *				 for the program to run. It contains references to every other module, entity and component in the engine.
 *				 This struct also handles the initialization of GLEW and SDL2.
 */

#pragma once
#include "Window.h"
#include "Environment.h"
#include "Resources.h"
#include "Input.h"
#include "Module.h"
#include "Camera.h"

namespace GameEngine
{
	struct Core
	{
		/* Initializes essential libraries for the engine to run */
		static std::shared_ptr<Core> initialize();

		/* Main engine game loop ticks all required engine components */
		void run();

		/* Creates a new module, adds them to the core vector and returns for user use */
		std::shared_ptr<Module> addModule();

		/* Returns the camera that is currently set to render */
		std::weak_ptr<Camera> getActiveRenderingCamera() { return m_activeRenderingCamera; }
	private:
		friend Component;
		friend Entity;
		friend Camera;
		friend struct ModelHandler;

		/* Object constants required for the engine to run */
		std::shared_ptr<InputHandler> m_inputHandler; // Uses SDL to handle inputs and expose them to the engine
		std::shared_ptr<Window> m_windowContext; // Sets up and initializes runtime window using SDL
		std::shared_ptr<Environment> m_environment; // Handles deltatime processing
		std::shared_ptr<Resources> m_resources; // Handles storing and loading all resources

		/* Vector of game entity modules which handle sections of grouped entities */
		std::vector<std::shared_ptr<Module>> m_modules;

		/* List of all created cameras within the engine */
		std::vector<std::weak_ptr<Camera>> m_cameras;
		/* Current rendering camera passed as a weak ref to model renderer's */
		std::weak_ptr<Camera> m_activeRenderingCamera;
		/* Main camera set to render GUI */
		std::weak_ptr<Camera> m_mainCamera;

		/* weak reference to its self to pass to its modules */
		std::weak_ptr<Core> m_self;

		/* Keeps the main game loop running while true */
		bool isGameRunning; 
	};
}