/*
 *  File: Main.cpp
 *  Author: Alex Emeny
 *  Date: December 18th, 2024 (Last Edited)
 *  Description: This file is the main of the program, it is the first called upon function.
 *               It takes care of initializing the engines core, entities made by the user and starting the main game loop.
 */

#include "../GameProject/Hierarchy.h"

#undef main
int main(int argc, char* argv[])
{
    /* Initialize the engine core with GLEW / SDL2 */
    std::shared_ptr<GameEngine::Core> core = GameEngine::Core::initialize();

    /* Initialize all entities created by the user */
    GameEngine::Hierarchy::initializeEntities(core);

    /* Run the main game loop within core */
    core->run();


    return 0;
}