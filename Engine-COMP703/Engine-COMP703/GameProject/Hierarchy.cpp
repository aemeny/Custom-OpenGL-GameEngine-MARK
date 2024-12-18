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
            ->setPosition(glm::vec3(0.0f, 0.0f, -10.0f));
    }
}