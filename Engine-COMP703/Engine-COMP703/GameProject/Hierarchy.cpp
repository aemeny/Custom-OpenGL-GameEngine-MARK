#include "Hierarchy.h"

namespace GameEngine
{
    void Hierarchy::initializeEntities(std::shared_ptr<Core> EngineCore)
    {

        /*   ---------- FOR USER USE. ----------
         *   All Modules, Entities and their components must be initialized within this script 
         */
         

        /* Return default created Module */
        ModulePtr defaultModule = EngineCore->getModule("Default");


        /* Camera Entity */
        defaultModule->addEntity()->addComponent
            <Camera>(CameraProjection::Perspective, PerspectiveParamaters{ 60.0f, 0.1f, 100.0f });


        /* Player Character Entity */
        EntityPtr character = defaultModule->addEntity();
        character->addComponent<ModelHandler>()
            ->setModel("Curuthers/Curuthers.obj")
            .setTexture("Curuthers/Curuthers.png")
            .setShaders("Perspective/VertexShader.glsl", "Perspective/FragmentShader.glsl");

        character->findComponent<Transform>().lock()
            ->setPosition(glm::vec3(0.0f, 5.0f, -10.0f));

        character->addComponent<RigidBody>()->setMass(50.0f);

        character->addComponent<AABBCollider>()->setColliderSize(glm::vec3(2.0f, 5.5f, 2.0f));


        /* Floor Entity */
        EntityPtr floor = defaultModule->addEntity();
        floor->addComponent<ModelHandler>()
            ->setModel("Cube/Cube.obj")
            .setTexture("Floor/Tile_Diffuse.png")
            .setShaders("Perspective/VertexShader.glsl", "Perspective/FragmentShader.glsl");

        floor->findComponent<Transform>().lock()
            ->setPosition(glm::vec3(0.0f, -5.0f, -10.0f));

        floor->addComponent<AABBCollider>();
    }
}