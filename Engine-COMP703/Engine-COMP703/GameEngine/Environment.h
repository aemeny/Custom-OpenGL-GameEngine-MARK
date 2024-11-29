/*
 *  File: Environment.h
 *  Author: Alex Emeny
 *  Date: November 27th, 2024
 *  Description: This file contains the Environment struct,
 *               which is responsible for managing delta time within the engine.
 */

#pragma once

namespace GameEngine
{
	struct Core;

	struct Environment
	{
		/* Assigns values to default and calls for initialization */
		Environment();

	private:
		/* Allow only the engines core to retrieve and tick deltaTime */
		friend Core;

		/* Initializes last tick count as a start point before the first frame */
		void initialize();
		/* Calls for Current tick count to compare from last frame to calculate deltaTime */
		void tickDeltaTime();

		/* returns deltaTime */
		double getDeltaTime() const;

		/* Last frame tick count and deltatime for the frame variables */
		double m_last;
		double m_deltaTime;
	};
}