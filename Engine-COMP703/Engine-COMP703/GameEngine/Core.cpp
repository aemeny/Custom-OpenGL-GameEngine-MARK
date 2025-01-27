/*
 *  File: Core.cpp
 *  Author: Alex Emeny
 *  Date: December 19th, 2024 (Last Edited)
 *  Description: This file implements the methods declared in Core.h.
 *               It implements the functions for initializing the Core variables, GLEW and SDL2.
 *				 It also takes care of the main game loop which is vital for the program to run.
 */

#include "Core.h"
#include <iostream>

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
		int windowWidth = 1920;
		int windowHeight = 1080;
		int swapInterval = 0;
		rtn->m_windowContext = std::make_shared<Window>();
		rtn->m_windowContext->initialize(windowWidth, windowHeight, swapInterval);
		rtn->m_windowContext->setWindowSwapInterval(0);

		/* GLEW Initialize */
		GLenum err = glewInit();
		if (GLEW_OK != err)
		{
			/* Major fault: glewInit failed */
			fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		}
		fprintf(stdout, "\nStatus: Using GLEW %s\n\n", glewGetString(GLEW_VERSION));

		/* Object variables Initialize */
		rtn->m_inputHandler = std::make_shared<InputHandler>(rtn->m_windowContext);
		rtn->m_environment = std::make_shared<Environment>();
		rtn->m_resources = std::make_shared<Resources>();
		rtn->m_lineRenderer = std::make_shared<LineRenderer>(rtn);
		rtn->m_physicsCore = std::make_shared<PhysicsSystem::PhysicsCore>();

		/* weak reference to its self to pass to its modules */
		rtn->m_self = rtn;

		/* Ensures the engine always has a module to build upon by default */
		rtn->addModule()->m_name = "Default";

		/* Returns core object to main() */
		return rtn;
	}

	/* Main engine game loop ticks all required engine components */
	void Core::run()
	{
		m_isGameRunning = true;

		/* Physics time steps */
		const double fixedTimeStep = 0.02; // 20 ms
		double physicsTimeAccumulator = 0.0;

		/* FPS tracker */
		int tickCount = 0;
		double DTCount = 0;

		while (m_isGameRunning)
		{
			/* Clear depth buffer */
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			/* Draw background */
			glClearColor(0.42f, 0.5f, 0.68f, 1.0f);


			/* Tick environment for delta time */
			m_environment->tickDeltaTime();
			tickCount++;
			DTCount += m_environment->getDTAsDouble();
			physicsTimeAccumulator += m_environment->getDTAsDouble();

			/* InputHandler tick, polls SDL for inputs */
			m_inputHandler->tick();


			/* Entity tick */
			for (size_t mi = 0; mi < m_modules.size(); ++mi)
			{
				if (m_modules.at(mi)->getActiveStatus())
				{
					m_modules.at(mi)->tick();
				}
			}


			/* Physics tick */
			while (physicsTimeAccumulator >= fixedTimeStep)
			{
				m_environment->tickPhysicsDeltaTime();

				m_physicsCore->physicsTick();

				physicsTimeAccumulator -= fixedTimeStep;
			}

			/* Render to any render textures in the scene */
			for (size_t rti = 0; rti < m_renderTextures.size(); ++rti)
			{
				m_renderTextures.at(rti)->bind();
				/* Clear texture from last frame */
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				/* Set default colour when rendering with no generated texture */
				if (m_renderTextures.at(rti)->getDirty()) // Only required on first pass
				{
					glm::vec3 clearColour = m_renderTextures.at(rti)->getClearColour();
					glClearColor(clearColour.x, clearColour.y, clearColour.z, 1.0f);
				}

				/* Entity Render */
				m_activeRenderingCamera = m_renderTextures.at(rti)->getRenderingCamera();
				if (m_activeRenderingCamera.lock()->getShouldRender())
				{
					for (size_t mi = 0; mi < m_modules.size(); ++mi)
					{
						if (m_modules.at(mi)->getActiveStatus())
						{
							m_modules.at(mi)->render();
						}
					}
					/* Debug Lines Render */
					m_lineRenderer->renderDebugLines(m_self);

					m_renderTextures.at(rti)->generateMipmaps();
				}

				m_renderTextures.at(rti)->unbind();
			}

			/* Entity late tick */
			for (size_t mi = 0; mi < m_modules.size(); ++mi)
			{
				if (m_modules.at(mi)->getActiveStatus())
				{
					m_modules.at(mi)->lateTick();
				}
			}

			/* Entity render */
			for (size_t ci = 0; ci < m_cameras.size(); ++ci)
			{
				/* Only render camera needed to the main screen */
				if (m_cameras.at(ci).lock()->getShouldRender())
				{
					/* Only render with the camera if the entity it is within is active */
					if (m_cameras.at(ci).lock()->m_entity.lock()->getActiveStatus())
					{
						m_activeRenderingCamera = m_cameras.at(ci);
						for (size_t mi = 0; mi < m_modules.size(); ++mi)
						{
							if (m_modules.at(mi)->getActiveStatus())
							{
								m_modules.at(mi)->render();
							}
						}

						/* Debug Lines Render */
						m_lineRenderer->renderDebugLines(m_self);
					}
				}
			}


			/* GUI render */
			m_activeRenderingCamera = m_mainCamera; // Only main camera renders GUI
			for (size_t mi = 0; mi < m_modules.size(); ++mi)
			{
				if (m_modules.at(mi)->getActiveStatus())
				{
					m_modules.at(mi)->GUIRender();
				}
			}


			/* Built in escape method from window */
			if (m_inputHandler->isKeyPressed(SDLK_ESCAPE))
				m_isGameRunning = false;


			/* Clear frame dependent input */
			m_inputHandler->clear();


			/* Swap window */
			SDL_GL_SwapWindow(m_windowContext->m_window);
			
			if (DTCount >= 1.0)
			{
				std::cout << tickCount << std::endl;

				DTCount -= 1.0;
				tickCount = 0;
			}
		}
	}

	/* Creates a new module, adds them to the core vector and returns for user use */
	std::shared_ptr<Module> Core::addModule()
	{
		std::shared_ptr<Module> rtn = std::make_shared<Module>();

		rtn->m_corePtr = m_self;
		rtn->m_self = rtn;
		rtn->m_active = true;

		/* Adds created module to vector storage in core */
		m_modules.push_back(rtn);

		/* Returns created module for user referencing and use */
		return rtn;
	}

	std::shared_ptr<Module> Core::getModule(std::string _name)
	{
		for (int mi = 0; mi < m_modules.size(); ++mi)
		{
			if (m_modules.at(mi)->m_name == _name)
			{
				return m_modules.at(mi);
			}
		}
		fprintf(stderr, "Error: No Module found with given name\n");
		return NULL;
	}

	std::shared_ptr<Module> Core::getModule(int _index)
	{
		if (_index < m_modules.size())
			return m_modules.at(_index);
		
		fprintf(stderr, "Error: No Module found within index range\n");
		return NULL;
	}

	std::weak_ptr<GraphicsRenderer::RenderTextureHandler> Core::addRenderTexture(std::weak_ptr<Camera> _renderingCamera, int _textureWidth, int _textureHeight)
	{
		std::shared_ptr<GraphicsRenderer::RenderTextureHandler> rtn
			= std::make_shared<GraphicsRenderer::RenderTextureHandler>(_renderingCamera, _textureWidth, _textureHeight);

		m_renderTextures.push_back(rtn);

		return rtn;
	}
}