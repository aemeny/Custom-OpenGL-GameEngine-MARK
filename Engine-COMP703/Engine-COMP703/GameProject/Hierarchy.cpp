#include "Hierarchy.h"

#include "CameraController.h"

namespace GameEngine
{
    void Hierarchy::initializeEntities(std::shared_ptr<Core> EngineCore)
    {

        /*   ---------- FOR USER USE. ----------
         *   All Modules, Entities and their components must be initialized within this script 
         */
         


        /* Return default created Module */
        ModuleObj defaultModule = EngineCore->getModule("Default");



        /* Camera Entity */
        EntityObj cameraEntity = defaultModule->addEntity();
        cameraEntity->addComponent<Camera>(CameraProjection::Perspective, PerspectiveParamaters{ 60.0f, 0.1f, 100.0f });

        cameraEntity->addComponent<CameraController>();



        /* Render Texture Camera Entity */
        EntityObj textureCameraEntity = defaultModule->addEntity();
        CameraObj camera = textureCameraEntity->addComponent<Camera>(CameraProjection::Perspective, PerspectiveParamaters{ 60.0f, 0.1f, 100.0f });
        camera.lock()->setShouldRender(false);
        textureCameraEntity->addComponent<CameraController>();

        /* Create Render Texture Using Created Camera */
        RenderTexture renderTexture = EngineCore->addRenderTexture(camera, 1000, 1000);

        /* Cube Making Use Of Render Texture */
        EntityObj portalOne = defaultModule->addEntity();
        portalOne->addComponent<ModelHandler>()
            ->setModel("Cube/Cube.obj")
            .setTexture(renderTexture)
            .setShaders("unlit/VertexShader.glsl", "unlit/FragmentShader.glsl");

        TransformObj transform = portalOne->findComponent<Transform>();
        transform.lock()->setRotation(glm::vec3(90.0f, 0.0f, 0.0f));
        transform.lock()->setPosition(glm::vec3(0.0f, 0.0f, 10.0f));
        transform.lock()->setScale(glm::vec3(4.0f, 4.0f, 0.00001f));



        /* Player Character Entity */
        EntityObj character = defaultModule->addEntity();
        character->addComponent<ModelHandler>()
            ->setModel("Curuthers/Curuthers.obj")
            .setTexture("Curuthers/Curuthers.png")
            .setShaders("Lit/VertexShader.glsl", "Lit/FragmentShader.glsl");

        character->findComponent<Transform>().lock()
            ->setPosition(glm::vec3(10.0f, 0.0f, 0.0f));

        character->addComponent<RigidBody>()->setMass(50.0f);

        BoxColliderObj characterCollider = character->addComponent<AABBCollider>();
        characterCollider.lock()->setColliderSize(glm::vec3(2.0f, 5.5f, 2.0f));
        characterCollider.lock()->setColliderOffset(glm::vec3(0.0f, 0.5f, 0.0f));



        /* Floor Entity */
        EntityObj floor = defaultModule->addEntity();
        floor->addComponent<ModelHandler>()
            ->setModel("Cube/Cube.obj")
            .setTexture("Colours/OrangeTexture.png")
            .setShaders("Lit/VertexShader.glsl", "Lit/FragmentShader.glsl");

        TransformObj transformFloor = floor->findComponent<Transform>();
        transformFloor.lock()->setPosition(glm::vec3(10.0f, -6.0f, 0.0f));
        transformFloor.lock()->setScale(glm::vec3(8.0f, 0.2f, 20.0f));

        BoxColliderObj boxCollider = floor->addComponent<AABBCollider>();
        boxCollider.lock()->setColliderSize(glm::vec3(16.0f, 0.4f, 40.0f));
        boxCollider.lock()->setRenderOutline(true);
    }
}