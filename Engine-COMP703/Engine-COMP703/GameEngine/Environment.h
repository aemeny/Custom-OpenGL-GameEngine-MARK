/*
 *  File: Environment.h
 *  Author: Alex Emeny
 *  Date: December 23rd, 2024 (Last Edited)
 *  Description: This file contains the Environment struct,
 *               which is responsible for managing delta time within the engine.
 */

#pragma once
#include <chrono>

namespace GameEngine
{
	struct Core;

	struct Environment
	{
		/* Assigns values to default and calls for initialization */
		Environment();

		/* returns deltaTime */
		double getDTAsDouble() const;
		float getDTAsFloat() const;
		double getPhysDTAsDouble() const;
		float getPhysDTAsFloat() const;
	private:
		friend Core;

		/* Initializes last tick count as a start point before the first frame */
		void initialize();

		/* Calls for Current tick count to compare from last frame to calculate deltaTime */
		void tickDeltaTime();

		/* Calls for Current tick count to compare from last frame physics tick to calculate physicsDeltaTime */
		void tickPhysicsDeltaTime();

		/* Last frame tick count and deltatime for the frame variables */
		std::chrono::high_resolution_clock::time_point m_lastTime;
		double m_deltaTime;

		/* Last physics frame tick count and physicsDeltatime for the physics frame variables */
		std::chrono::high_resolution_clock::time_point m_lastPhysicsTime;
		double m_physicsDeltaTime;
	};
}