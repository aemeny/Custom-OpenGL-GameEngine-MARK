/*
 *  File: Window.h
 *  Author: Alex Emeny
 *  Date: November 15th, 2024 (Last Edited)
 *  Description: This file contains the Window struct,
 *               which is responsible for initializing the window and creating SDL Context.
 *               The Window struct also stores SDL window information / data.
 */

#pragma once
#include "../Graphics/GraphicsMasterHeader.h"

namespace GameEngine
{
	struct Window
	{
		/* Initializes SDL window and context with passed window height & width */
		void initialize(int _width, int _height, int _windowSwapInterval);
		/* Deletes SDL Context and Destroys Window. 
		   QUITS SDL PROGRAM */
		~Window();

		/* Updates SDL_GL swap interval */
		void setWindowSwapInterval(int _value);
		/* Returns value of swap interval and prints set status in console */
		int getWindowSwapInterval();

		SDL_Window* m_window;
		SDL_GLContext m_context;

		int m_windowHeight, m_windowWidth;
	private:
		/* Holds status of current swap interval */
		int m_windowSwapInterval;
	};
}