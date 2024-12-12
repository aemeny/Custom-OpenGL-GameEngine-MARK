#include "../GameEngine/GameEngineMasterHeader.h"

using namespace GameEngine;

#undef main
int main(int argc, char* argv[])
{
    std::shared_ptr<Core> core = Core::initialize();

    core->run();

    return 0;
}


/* ############# TO-DO ############# */
// COMMENT MODEL HANDLER.H/CPP
// FINISH UP TRANSFORM.H
// MAKE TRANSFORM A DEFAULT FOR ALL ENTITIES
// ALLOW ALL COMPONENTS TO ACCESS ITS TRANSFORM EASILY
// MAKE USE OF TRANSFORM.H WITHIN MODEL HANDLER

// CAMERA FREE MOVEMENT / GAMEPROJECT FILES
