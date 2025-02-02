/*
 *  File: Core.h
 *  Author: Alex Emeny
 *  Date: December 19th, 2024 (Last Edited)
 *  Description: This file contains the Core struct,
 *               The core of the game engine, this struct holds the main game loop within and is vital
 *				 for the program to run. It contains references to every other module, entity and component in the engine.
 *				 This struct also handles the initialization of GLEW and SDL2.
 */

#pragma once
#include "Window.h"
#include "Environment.h"
#include "../Physics/PhysicsCore.h"
#include "Resources.h"
#include "Module.h"
#include "Camera.h"
#include "LineRenderer.h"

namespace GameEngine
{
	struct Core
	{
		/* Initializes essential libraries for the engine to run */
		static std::shared_ptr<Core> initialize();

		/* Main engine game loop ticks all required engine components */
		void run();

		/* Returns the camera that is currently set to render */
		std::weak_ptr<Camera> getActiveRenderingCamera() { return m_activeRenderingCamera; }

		/* Creates a new module, adds them to the core vector and returns for user use */
		std::shared_ptr<Module> addModule();
	
		/* Returns the pointer to a module based on the passed name or index */
		std::shared_ptr<Module> getModule(std::string _name);
		std::shared_ptr<Module> getModule(int _index);

		/* Returns a weak pointer to a newly created render texture */
		std::weak_ptr<GraphicsRenderer::RenderTextureHandler> addRenderTexture(std::weak_ptr<Camera> _renderingCamera, int _textureWidth, int _textureHeight);

		/* Stops the program from running the core loop */
		void stopProgram() { m_isGameRunning = false; }

	private:
		friend Component;
		friend Entity;
		friend Camera;
		friend struct ModelHandler;
		friend struct QuadRenderer;
		friend struct LineRenderer;
		friend PhysicsSystem::AABBCollider;

		/* Object constants required for the engine to run */
		std::shared_ptr<InputHandler> m_inputHandler; // Uses SDL to handle inputs and expose them to the engine
		std::shared_ptr<Window> m_windowContext; // Sets up and initializes runtime window using SDL
		std::shared_ptr<Environment> m_environment; // Handles deltatime processing
		std::shared_ptr<Resources> m_resources; // Handles storing and loading all resources
		std::shared_ptr<LineRenderer> m_lineRenderer; // Handles Debug line rendering
		std::shared_ptr<PhysicsSystem::PhysicsCore> m_physicsCore; // Handles all physics based events

		/* Vector of game entity modules which handle sections of grouped entities */
		std::vector<std::shared_ptr<Module>> m_modules;

		/* Vector of all created render textures to draw to */
		std::vector<std::shared_ptr<GraphicsRenderer::RenderTextureHandler>> m_renderTextures;

		/* List of all created cameras within the engine */
		std::vector<std::weak_ptr<Camera>> m_cameras;
		/* Current rendering camera passed as a weak ref to model renderer's */
		std::weak_ptr<Camera> m_activeRenderingCamera;
		/* Main camera set to render GUI */
		std::weak_ptr<Camera> m_mainCamera;

		/* weak reference to its self to pass to its modules */
		std::weak_ptr<Core> m_self;

		/* Keeps the main game loop running while true */
		bool m_isGameRunning;
	};
}