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
        glm::vec2 portalScale = glm::vec2(2.0f, 3.0f);
        float aspectRatio = portalScale.x / portalScale.y;
        float renderTextureWidth = 1280;
        float renderTextureHeight = renderTextureWidth / aspectRatio;

        EntityObj textureCameraEntity = defaultModule->addEntity();
        CameraObj camera = textureCameraEntity->addComponent<Camera>(CameraProjection::Perspective, PerspectiveParamaters{ 60.0f, 0.1f, 100.0f });
        camera.lock()->setShouldRender(false);
        textureCameraEntity->addComponent<CameraController>();

        /* Create Render Texture Using Created Camera */
        RenderTexture renderTexture = EngineCore->addRenderTexture(camera, 2048, 2048);

        /* Cube Making Use Of Render Texture */
        EntityObj portalOne = defaultModule->addEntity();
        portalOne->addComponent<ModelHandler>()
            ->setModel("Cube/PortalCube.obj")
            .setTexture(renderTexture)
            .setShaders("unlit/VertexShader.glsl", "unlit/FragmentShader.glsl");

        TransformObj transformPortalOne = portalOne->findComponent<Transform>();
        transformPortalOne.lock()->setRotation(glm::vec3(0.0f, 0.0f, 90.0f));
        transformPortalOne.lock()->setPosition(glm::vec3(10.0f, 3.3f, 0.0f));

        EntityObj portalTwo = defaultModule->addEntity();
        portalTwo->addComponent<ModelHandler>()
            ->setModel("Cube/Cube.obj")
            .setTexture(renderTexture)
            .setShaders("unlit/VertexShader.glsl", "unlit/FragmentShader.glsl");

        TransformObj transformPortalTwo = portalTwo->findComponent<Transform>();
        transformPortalTwo.lock()->setRotation(glm::vec3(90.0f, 0.0f, 0.0f));
        transformPortalTwo.lock()->setPosition(glm::vec3(-10.0f, 3.2f, 0.0f));
        transformPortalTwo.lock()->setScale(glm::vec3(portalScale.x, portalScale.y, 0.000001f));



        /* Player Character Entity */
        EntityObj character = defaultModule->addEntity();
        character->addComponent<ModelHandler>()
            ->setModel("Curuthers/Curuthers.obj")
            .setTexture("Curuthers/Curuthers.png")
            .setShaders("Lit/VertexShader.glsl", "Lit/FragmentShader.glsl");

        character->findComponent<Transform>().lock()
            ->setPosition(glm::vec3(10.0f, 0.0f, -16.0f));

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
        transformFloor.lock()->setPosition(glm::vec3(10.0f, -0.0f, -9.0f));
        transformFloor.lock()->setScale(glm::vec3(8.0f, 0.2f, 15.0f));

        BoxColliderObj boxCollider = floor->addComponent<AABBCollider>();
        boxCollider.lock()->setColliderSize(glm::vec3(16.0f, 0.4f, 30.0f));
        boxCollider.lock()->setRenderOutline(true);

        /* Floor Entity 2 */
        EntityObj floor2 = defaultModule->addEntity();
        floor2->addComponent<ModelHandler>()
            ->setModel("Cube/Cube.obj")
            .setTexture("Colours/GreenTexture.png")
            .setShaders("Lit/VertexShader.glsl", "Lit/FragmentShader.glsl");

        TransformObj transformFloor2 = floor2->findComponent<Transform>();
        transformFloor2.lock()->setPosition(glm::vec3(-10.0f, 0.0f, -9.0f));
        transformFloor2.lock()->setScale(glm::vec3(8.0f, 0.2f, 15.0f));

        BoxColliderObj boxCollider2 = floor2->addComponent<AABBCollider>();
        boxCollider2.lock()->setColliderSize(glm::vec3(16.0f, 0.4f, 30.0f));


        /* Cubes In Scene  */
        EntityObj cube = defaultModule->addEntity();
        cube->addComponent<ModelHandler>()
            ->setModel("Cube/Cube.obj")
            .setTexture("Floor/Tile_Diffuse.png")
            .setShaders("Lit/VertexShader.glsl", "Lit/FragmentShader.glsl");
        cube->findComponent<Transform>().lock()->setPosition(glm::vec3(-6.0f, 1.4f, -8.0f));

        cube = defaultModule->addEntity();
        cube->addComponent<ModelHandler>()
            ->setModel("Cube/Cube.obj")
            .setTexture("Floor/Tile_Diffuse.png")
            .setShaders("Lit/VertexShader.glsl", "Lit/FragmentShader.glsl");
        cube->findComponent<Transform>().lock()->setPosition(glm::vec3(6.0f, 1.4f, -8.0f));

        cube = defaultModule->addEntity();
        cube->addComponent<ModelHandler>()
            ->setModel("Cube/Cube.obj")
            .setTexture("Floor/Tile_Diffuse.png")
            .setShaders("Lit/VertexShader.glsl", "Lit/FragmentShader.glsl");
        cube->findComponent<Transform>().lock()->setPosition(glm::vec3(15.0f, 1.4f, -14.0f));

        cube = defaultModule->addEntity();
        cube->addComponent<ModelHandler>()
            ->setModel("Cube/Cube.obj")
            .setTexture("Floor/Tile_Diffuse.png")
            .setShaders("Lit/VertexShader.glsl", "Lit/FragmentShader.glsl");
        cube->findComponent<Transform>().lock()->setPosition(glm::vec3(-15.0f, 1.4f, -14.0f));


        /* Portal One Boarder Cubes */
        cube = defaultModule->addEntity();
        cube->addComponent<ModelHandler>()
            ->setModel("Cube/Cube.obj")
            .setTexture("Colours/BlackTexture.png")
            .setShaders("Lit/VertexShader.glsl", "Lit/FragmentShader.glsl");
        TransformObj transformcube = cube->findComponent<Transform>();
        transformcube.lock()->setPosition(glm::vec3(12.2f, 3.4f, 0.0f));
        transformcube.lock()->setScale(glm::vec3(0.2f, 3.2f, 0.1f));

        cube = defaultModule->addEntity();
        cube->addComponent<ModelHandler>()
            ->setModel("Cube/Cube.obj")
            .setTexture("Colours/BlackTexture.png")
            .setShaders("Lit/VertexShader.glsl", "Lit/FragmentShader.glsl");
        transformcube = cube->findComponent<Transform>();
        transformcube.lock()->setPosition(glm::vec3(8.05f, 3.4f, 0.0f));
        transformcube.lock()->setScale(glm::vec3(0.2f, 3.2f, 0.1f));

        cube = defaultModule->addEntity();
        cube->addComponent<ModelHandler>()
            ->setModel("Cube/Cube.obj")
            .setTexture("Colours/BlackTexture.png")
            .setShaders("Lit/VertexShader.glsl", "Lit/FragmentShader.glsl");
        transformcube = cube->findComponent<Transform>();
        transformcube.lock()->setPosition(glm::vec3(10.2f, 6.4f, 0.0f));
        transformcube.lock()->setScale(glm::vec3(2.0f, 0.2f, 0.1f));


        /* Portal Two Boarder Cubes */
        cube = defaultModule->addEntity();
        cube->addComponent<ModelHandler>()
            ->setModel("Cube/Cube.obj")
            .setTexture("Colours/BlackTexture.png")
            .setShaders("Lit/VertexShader.glsl", "Lit/FragmentShader.glsl");
        transformcube = cube->findComponent<Transform>();
        transformcube.lock()->setPosition(glm::vec3(-12.2f, 3.4f, 0.0f));
        transformcube.lock()->setScale(glm::vec3(0.2f, 3.2f, 0.1f));

        cube = defaultModule->addEntity();
        cube->addComponent<ModelHandler>()
            ->setModel("Cube/Cube.obj")
            .setTexture("Colours/BlackTexture.png")
            .setShaders("Lit/VertexShader.glsl", "Lit/FragmentShader.glsl");
        transformcube = cube->findComponent<Transform>();
        transformcube.lock()->setPosition(glm::vec3(-8.2f, 3.4f, 0.0f));
        transformcube.lock()->setScale(glm::vec3(0.2f, 3.2f, 0.1f));

        cube = defaultModule->addEntity();
        cube->addComponent<ModelHandler>()
            ->setModel("Cube/Cube.obj")
            .setTexture("Colours/BlackTexture.png")
            .setShaders("Lit/VertexShader.glsl", "Lit/FragmentShader.glsl");
        transformcube = cube->findComponent<Transform>();
        transformcube.lock()->setPosition(glm::vec3(-10.2f, 6.4f, 0.0f));
        transformcube.lock()->setScale(glm::vec3(2.0f, 0.2f, 0.1f));
    }
}