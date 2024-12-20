#pragma once
#include "../GameEngine/GameEngineMasterHeader.h"
#include "../Physics/RigidBody.h"

using EntityPtr = std::shared_ptr<GameEngine::Entity>;
using ModulePtr = std::shared_ptr<GameEngine::Module>;
using TransformPtr = std::weak_ptr<GameEngine::Transform>;
using RigidBodyPtr = std::weak_ptr<PhysicsSystem::RigidBody>;

using namespace PhysicsSystem;
namespace GameEngine
{
    struct Hierarchy
    {
        static void initializeEntities(std::shared_ptr<Core> EngineCore);
    };
}