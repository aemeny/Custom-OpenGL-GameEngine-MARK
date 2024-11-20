#include "../GameEngine/GameEngineMasterHeader.h"

using namespace GameEngine;

#undef main
int main(int argc, char* argv[])
{
    std::shared_ptr<Core> core = Core::initialize();

    core->run();

    return 0;
}