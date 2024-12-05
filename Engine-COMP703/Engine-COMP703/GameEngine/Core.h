/*
 *  File: Core.h
 *  Author: Alex Emeny
 *  Date: December 3rd, 2024 (Last Edited)
 *  Description: This file contains the Core struct,
 *               The core of the game engine, this struct holds the main game loop within and is vital
 *				 for the program to run. It contains references to every other module, entity and component in the engine.
 *				 This struct also handles the initialization of GLEW and SDL2.
 */

#pragma once
#include "Window.h"
#include "Environment.h"
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

	private:
		/* Object constants required for the engine to run */
		std::shared_ptr<InputHandler> m_inputHandler; // Uses SDL to handle inputs and expose them to the engine
		std::shared_ptr<Window> m_windowContext; // Sets up and initializes runtime window using SDL
		std::shared_ptr<Environment> m_environment; // Handles deltatime processing

		/* Vector of game entity modules which handle sections of grouped entities */
		std::vector<std::shared_ptr<Module>> m_modules;

		/* Keeps the main game loop running while true */
		bool isGameRunning; 
	};
}