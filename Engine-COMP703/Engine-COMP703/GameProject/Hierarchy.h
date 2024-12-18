#pragma once
#include "../GameEngine/GameEngineMasterHeader.h"

using EntityPtr = std::shared_ptr<GameEngine::Entity>;
using ModulePtr = std::shared_ptr<GameEngine::Module>;
using TransformPtr = std::weak_ptr<GameEngine::Transform>;

namespace GameEngine
{
    struct Hierarchy
    {
        static void initializeEntities(std::shared_ptr<Core> EngineCore);
    };
}