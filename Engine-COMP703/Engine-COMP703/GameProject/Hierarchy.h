#pragma once
#include "../GameEngine/GameEngineMasterHeader.h"
#include "../Physics/RigidBody.h"
#include "CameraController.h"

using ModuleObj = std::shared_ptr<GameEngine::Module>;
using EntityObj = std::shared_ptr<GameEngine::Entity>;
using TransformObj = std::weak_ptr<GameEngine::Transform>;
using RigidBodyObj = std::weak_ptr<PhysicsSystem::RigidBody>;

using namespace PhysicsSystem;
namespace GameEngine
{
    struct Hierarchy
    {
        static void initializeEntities(std::shared_ptr<Core> EngineCore);
    };
}