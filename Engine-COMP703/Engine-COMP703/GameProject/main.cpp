#include "../GameEngine/GameEngineMasterHeader.h"

using namespace GameEngine;

#undef main
int main()
{
    std::shared_ptr<Core> core = Core::initialize();

    return 0;
}