/*
 *  File: Core.h
 *  Author: Alex Emeny
 *  Date: November 27th, 2024
 *  Description: This file contains the Core struct,
 *               The core of the game engine, this struct holds the main game loop within and is vital
 *				 for the program to run. It contains references to every other entity and component in the engine.
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

	private:
		/*  */
		std::shared_ptr<InputHandler> m_inputHandler;
		std::shared_ptr<Window> m_windowContext;
		std::shared_ptr<Environment> m_environment;

		bool isGameRunning;
	};
}