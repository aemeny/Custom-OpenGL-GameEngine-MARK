/*
 *  File: Core.cpp
 *  Author: Alex Emeny
 *  Date: December 3rd, 2024 (Last Edited)
 *  Description: This file implements the methods declared in Core.h.
 *               It implements the functions for initializing the Core variables, GLEW and SDL2.
 *				 It also takes care of the main game loop which is vital for the program to run.
 */

#include "Core.h"

namespace GameEngine
{
	/* Initializes essential libraries for the engine to run */
	std::shared_ptr<Core> Core::initialize()
	{
		std::shared_ptr<Core> rtn = std::make_shared<Core>();

		/* SDL Initialize */
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			/* Major fault: SDL_Init failed */
			throw std::runtime_error("Failed to initialize SDL");
		}

		/* SDL Window Initialize */
		int windowWidth = 800;
		int windowHeight = 800;
		rtn->m_windowContext = std::make_shared<Window>();
		rtn->m_windowContext->initialize(windowWidth, windowHeight);

		/* GLEW Initialize */
		GLenum err = glewInit();
		if (GLEW_OK != err)
		{
			/* Major fault: glewInit failed */
			fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		}
		fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

		/* Object variables Initialize */
		rtn->m_inputHandler = std::make_shared<InputHandler>(rtn->m_windowContext);
		rtn->m_environment = std::make_shared<Environment>();

		/* weak reference to its self to pass to its modules */
		rtn->m_self = rtn;

		/* Ensures the engine always has a module to build upon by default */
		rtn->addModule();

		/* returns core object to main() */
		return rtn;
	}

	/* Main engine game loop ticks all required engine components */
	void Core::run()
	{
		isGameRunning = true;

		// TEMP MODEL LOADING FOR TESTING
		std::shared_ptr<GraphicsRenderer::ModelHandler> model =
			std::make_shared<GraphicsRenderer::ModelHandler>("../Samples/Models/Curuthers/Curuthers.obj");

		std::shared_ptr<GraphicsRenderer::ShaderHandler> shader =
			std::make_shared<GraphicsRenderer::ShaderHandler>("../Shaders/Perspective/VertexShader.vs", "../Shaders/Perspective/FragmentShader.fs");

		std::shared_ptr<GraphicsRenderer::TextureHandler> texture =
			std::make_shared<GraphicsRenderer::TextureHandler>("../Samples/Textures/Curuthers/Curuthers.png");

		//std::shared_ptr<Camera> camera = std::make_shared<Camera>(
		//	CameraProjection::Perspective, PerspectiveParamaters{60.0f, 0.1f, 100.0f});


		while (isGameRunning)
		{
			//Clear depth buffer
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			//draw background
			glClearColor(0.42f, 0.5f, 0.68f, 1.0f);

			/* Tick environment for delta time */
			m_environment->tickDeltaTime();

			/* InputHandler tick, polls SDL for inputs */
			m_inputHandler->tick();

			/* Entity tick */
			for (size_t mi = 0; mi < m_modules.size(); ++mi)
			{
				m_modules.at(mi)->tick();
			}

			/* Entity render */
			for (size_t mi = 0; mi < m_modules.size(); ++mi)
			{
				m_modules.at(mi)->render();
			}

			/* GUI render */
			for (size_t mi = 0; mi < m_modules.size(); ++mi)
			{
				m_modules.at(mi)->GUIRender();
			}

			// TEMP ENTITY RENDERING
			//shader->bindShader(camera->getProjectionMatrix(), "u_Projection");
			shader->renderModel(model, texture);

			/* Built in escape method from window */
			if (m_inputHandler->isKeyPressed(SDLK_ESCAPE))
				isGameRunning = false;

			/* Clear frame dependent input */
			m_inputHandler->clear();

			/* Swap window */
			SDL_GL_SwapWindow(m_windowContext->m_window);
		}
	}

	/* Creates a new module, adds them to the core vector and returns for user use */
	std::shared_ptr<Module> Core::addModule()
	{
		std::shared_ptr<Module> rtn = std::make_shared<Module>();

		rtn->m_corePtr = m_self;
		rtn->m_self = rtn;

		/* Adds created module to vector storage in core */
		m_modules.push_back(rtn);

		/* Returns created module for user referencing and use */
		return rtn;
	}
}