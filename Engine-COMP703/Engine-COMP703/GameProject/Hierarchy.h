#pragma once
#include "../GameEngine/GameEngineMasterHeader.h"
#include "../Physics/RigidBody.h"
#include "../Graphics/GraphicsRenderTextureHandler.h"

using ModuleObj = std::shared_ptr<GameEngine::Module>;
using EntityObj = std::shared_ptr<GameEngine::Entity>;
using TransformObj = std::weak_ptr<GameEngine::Transform>;
using CameraObj = std::weak_ptr<GameEngine::Camera>;
using RigidBodyObj = std::weak_ptr<PhysicsSystem::RigidBody>;
using BoxColliderObj = std::weak_ptr<PhysicsSystem::AABBCollider>;
using LineRendererObj = std::weak_ptr<GameEngine::LineRenderer>;
using RenderTexture = std::weak_ptr<GraphicsRenderer::RenderTextureHandler>;

using namespace PhysicsSystem;
using namespace GraphicsRenderer;
namespace GameEngine
{
    struct Hierarchy
    {
        static void initializeEntities(std::shared_ptr<Core> EngineCore);
    };
}