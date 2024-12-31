/*
 * File: Environment.cpp
 * Author: Alex Emeny
 * Date: December 23rd, 2024 (Last Edited)
 * Description: This file implements the methods declared in Environment.h.
 *              It defines the functions for initializing delta time.
 *				Manages and updates delta time.
 */

#include "Environment.h"

namespace GameEngine
{
	/* Assigns values to default and calls for initialization */
	Environment::Environment() : m_deltaTime(0), m_physicsDeltaTime(0)
	{
		initialize();
	}

	/* Initializes last tick count as a start point before the first frame */
	void Environment::initialize()
	{
		m_lastTime = std::chrono::high_resolution_clock::now();
		m_lastPhysicsTime = std::chrono::high_resolution_clock::now();
	}
	
	/* Calls for Current tick count to compare from last frame to calculate deltaTime */
	void Environment::tickDeltaTime()
	{
		std::chrono::steady_clock::time_point currTime = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> diff = currTime - m_lastTime;

		m_deltaTime = diff.count();
		m_lastTime = currTime;
	}

	/* Calls for Current tick count to compare from last frame physics tick to calculate physicsDeltaTime */
	void Environment::tickPhysicsDeltaTime()
	{
		std::chrono::steady_clock::time_point currTime = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> diff = currTime - m_lastPhysicsTime;

		m_physicsDeltaTime = diff.count();
		m_lastPhysicsTime = currTime;
	}

	/* Returns deltaTime */
	double Environment::getDTAsDouble() const
	{
		return m_deltaTime;
	}
	float Environment::getDTAsFloat() const
	{
		return m_deltaTime;
	}

	/* Returns physicsDeltaTime */
	double Environment::getPhysDTAsDouble() const
	{
		return m_physicsDeltaTime;
	}
	float Environment::getPhysDTAsFloat() const
	{
		return m_physicsDeltaTime;
	}

}