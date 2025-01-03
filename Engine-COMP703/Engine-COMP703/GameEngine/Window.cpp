/*
 * File: Window.cpp
 * Author: Alex Emeny
 * Date: November 15th, 2024 (Last Edited)
 * Description: This file implements the methods declared in Window.h.
 *              It defines the functions for initializing the window and creating SDL Context.
 *				Cleans up SDL with Deleting Context and Destroying Window to finally Quit SDL
 */

#include "Window.h"
#include <iostream>

namespace GameEngine
{
	/* Initializes SDL window and context with passed window height & width */
	void Window::initialize(int _width, int _height, int _windowSwapInterval)
	{
		m_windowWidth = _width;
		m_windowHeight = _height;

		if (!(m_window = SDL_CreateWindow("WINDOW",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			m_windowWidth, m_windowHeight, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL)))
		{
			SDL_Quit();
			throw std::runtime_error("Failed to create Window");
		}

		if (!(m_context = SDL_GL_CreateContext(m_window)))
		{
			SDL_DestroyWindow(m_window);
			SDL_Quit();
			throw std::runtime_error("Failed to create OpenGL context");
		}

		setWindowSwapInterval(_windowSwapInterval);
	}

	/* Deletes SDL Context and Destroys Window.
		   QUITS SDL PROGRAM */
	Window::~Window()
	{
		if (m_context)
		{
			std::cout << "\nSDL_GL_DeleteContext \n" << std::endl;
			SDL_GL_DeleteContext(m_context);
		}
		if (m_window)
		{
			std::cout << "SDL_DestroyWindow \n" << std::endl;
			SDL_DestroyWindow(m_window);

			std::cout << "SDL_Quit \n" << std::endl;
			SDL_Quit();
		}
	}

	/* Updates SDL_GL swap interval */
	void Window::setWindowSwapInterval(int _value)
	{
		/* Validate input : -1 (adaptive VSync), 0 (no VSync), 1 (Standard VSync) */
		if (_value >= -1 && _value <= 1)
		{
			int result = SDL_GL_SetSwapInterval(_value);
			m_windowSwapInterval = _value;

			if (result == -1) // If adaptive vsync isn't available on this device switch to standard Vsync
			{
				SDL_GL_SetSwapInterval(1);
				std::cout << "Adaptive VSync not available, standard VSync will be activated as fall back\n";
				m_windowSwapInterval = 1;
			}
		}
		else
		{
			std::cout << "\n **** INVALID SWAP INTERVAL ENTERED **** \n";
			std::cout << "Immediate updates (no VSync) have been activated as a fall back. \n\n";
			SDL_GL_SetSwapInterval(0);
			m_windowSwapInterval = 0;
		}

		getWindowSwapInterval(); // Prints result to console
	}

	/* Returns value of swap interval and prints set status in console */
	int Window::getWindowSwapInterval()
	{
		switch (m_windowSwapInterval)
		{
		case -1:
			std::cout << "Swap Interval: Adaptive VSync is active\n";
			break;
		case 0:
			std::cout << "Swap Interval: Immediate updates is active (no VSync)\n";
			break;
		case 1:
			std::cout << "Swap Interval: standard VSync is active\n";
			break;
		}

		return m_windowSwapInterval;
	}
}