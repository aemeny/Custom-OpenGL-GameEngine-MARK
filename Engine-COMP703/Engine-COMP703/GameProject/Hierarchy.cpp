#include "Hierarchy.h"

#include "CameraController.h"
#include "Portal.h"

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
        std::weak_ptr<CameraController> camController = cameraEntity->addComponent<CameraController>();
        TransformObj transformCameraEntity = cameraEntity->findComponent<Transform>();


        /* Render Texture Camera Entity */
        EntityObj textureCameraEntity = defaultModule->addEntity();
        CameraObj camera = textureCameraEntity->addComponent<Camera>(CameraProjection::Perspective, PerspectiveParamaters{ 60.0f, 0.1f, 100.0f });
        camera.lock()->setShouldRender(false);
        TransformObj transformTextureCameraEntity = textureCameraEntity->findComponent<Transform>();
        
        /* Render Texture Camera Entity 2 */
        EntityObj textureCameraEntity2 = defaultModule->addEntity();
        CameraObj camera2 = textureCameraEntity2->addComponent<Camera>(CameraProjection::Perspective, PerspectiveParamaters{ 60.0f, 0.1f, 100.0f });
        camera2.lock()->setShouldRender(false);
        TransformObj transformTextureCameraEntity2 = textureCameraEntity2->findComponent<Transform>();




        /* Create Render Texture Using Created Camera */
        RenderTexture renderTexture = EngineCore->addRenderTexture(camera, 1920, 1080);
        RenderTexture renderTexture2 = EngineCore->addRenderTexture(camera2, 1920, 1080);


        /* Cube Making Use Of Render Texture */
        EntityObj portalOne = defaultModule->addEntity();
        portalOne->addComponent<ModelHandler>()
            ->setModel("Cube/PortalCube.obj")
            .setTexture(renderTexture)
            .setShaders("unlit/VertexShader.glsl", "unlit/FragmentShader.glsl");

        TransformObj transformPortalOne = portalOne->findComponent<Transform>();
        transformPortalOne.lock()->setRotation(glm::vec3(0.0f, 0.0f, 90.0f));
        transformPortalOne.lock()->setPosition(glm::vec3(10.0f, 2.3f, 0.0f));


        /* Cube 2 Making Use Of Render Texture */
        EntityObj portalTwo = defaultModule->addEntity();
        portalTwo->addComponent<ModelHandler>()
            ->setModel("Cube/PortalCube.obj")
            .setTexture(renderTexture2)
            .setShaders("unlit/VertexShader.glsl", "unlit/FragmentShader.glsl");

        TransformObj transformPortalTwo = portalTwo->findComponent<Transform>();
        transformPortalTwo.lock()->setRotation(glm::vec3(0.0f, 0.0f, 90.0f));
        transformPortalTwo.lock()->setPosition(glm::vec3(-10.0f, 2.3f, 0.0f));


        /* Portal 1 wall */
        EntityObj portal1Wall = defaultModule->addEntity();
        portal1Wall->addComponent<ModelHandler>()
            ->setModel("Cube/Cube.obj")
            .setTexture("Colours/OrangeTexture.png")
            .setShaders("Lit/VertexShader.glsl", "Lit/FragmentShader.glsl");
        TransformObj transformcube1 = portal1Wall->findComponent<Transform>();
        transformcube1.lock()->setPosition(glm::vec3(10.0f, 4.8f, 0.2f));
        transformcube1.lock()->setScale(glm::vec3(8.0f, 4.5f, 0.1f));

        /* Portal 2 wall */
        EntityObj portal2Wall = defaultModule->addEntity();
        portal2Wall->addComponent<ModelHandler>()
            ->setModel("Cube/Cube.obj")
            .setTexture("Colours/GreenTexture.png")
            .setShaders("Lit/VertexShader.glsl", "Lit/FragmentShader.glsl");
        TransformObj transformcube2 = portal2Wall->findComponent<Transform>();
        transformcube2.lock()->setPosition(glm::vec3(-10.0f, 4.8f, 0.2f));
        transformcube2.lock()->setScale(glm::vec3(8.0f, 4.5f, 0.1f));


        /* Player Character Entity */
        EntityObj character = defaultModule->addEntity();
        character->addComponent<ModelHandler>()
            ->setModel("Curuthers/Curuthers.obj")
            .setTexture("Curuthers/Curuthers.png")
            .setShaders("Lit/VertexShader.glsl", "Lit/FragmentShader.glsl");

        TransformObj playerTransform = character->findComponent<Transform>();
        playerTransform.lock()->setScale(glm::vec3(0.5f));

        //character->addComponent<RigidBody>()->setMass(50.0f);

        //BoxColliderObj characterCollider = character->addComponent<AABBCollider>();
        //characterCollider.lock()->setColliderSize(glm::vec3(2.0f, 5.5f, 2.0f));
        //characterCollider.lock()->setColliderOffset(glm::vec3(0.0f, 0.5f, 0.0f));


        camController.lock()->m_playerCharacter = playerTransform;


        /* Portal scripts setup */
        portalTwo->setStillTickStatus(true);
        std::weak_ptr<Portal> portal2 = portalTwo->addComponent<Portal>();
        portal2.lock()->m_portalEntity = portalTwo;
        portal2.lock()->m_portalTransform = transformPortalTwo;
        portal2.lock()->m_cameraTransform = transformTextureCameraEntity;
        portal2.lock()->m_playerTransform = transformCameraEntity;
        portal2.lock()->m_linkedPortalTransform = transformPortalOne;
        portal2.lock()->m_portalWall = portal1Wall;
        portal2.lock()->m_characterEntity = character;

        portalOne->setStillTickStatus(true);
        std::weak_ptr<Portal> portal1 = portalOne->addComponent<Portal>();
        portal1.lock()->m_portalEntity = portalOne;
        portal1.lock()->m_portalTransform = transformPortalOne;
        portal1.lock()->m_cameraTransform = transformTextureCameraEntity2;
        portal1.lock()->m_playerTransform = transformCameraEntity;
        portal1.lock()->m_linkedPortalTransform = transformPortalTwo;
        portal1.lock()->m_portalWall = portal2Wall;
        portal1.lock()->m_characterEntity = character;



        /* Floor Entity */
        EntityObj floor = defaultModule->addEntity();
        floor->addComponent<ModelHandler>()
            ->setModel("Cube/Cube.obj")
            .setTexture("Colours/OrangeTexture.png")
            .setShaders("Lit/VertexShader.glsl", "Lit/FragmentShader.glsl");

        TransformObj transformFloor = floor->findComponent<Transform>();
        transformFloor.lock()->setPosition(glm::vec3(10.0f, 0.1f, -9.0f));
        transformFloor.lock()->setScale(glm::vec3(8.0f, 0.2f, 15.0f));

        BoxColliderObj boxCollider = floor->addComponent<AABBCollider>();
        boxCollider.lock()->setColliderSize(glm::vec3(16.0f, 0.4f, 30.0f));

        /* Floor Entity 2 */
        EntityObj floor2 = defaultModule->addEntity();
        floor2->addComponent<ModelHandler>()
            ->setModel("Cube/Cube.obj")
            .setTexture("Colours/GreenTexture.png")
            .setShaders("Lit/VertexShader.glsl", "Lit/FragmentShader.glsl");

        TransformObj transformFloor2 = floor2->findComponent<Transform>();
        transformFloor2.lock()->setPosition(glm::vec3(-10.0f, 0.1f, -9.0f));
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
        transformcube.lock()->setPosition(glm::vec3(13.2f, 2.4f, 0.0f));
        transformcube.lock()->setScale(glm::vec3(0.2f, 2.2f, 0.1f));

        cube = defaultModule->addEntity();
        cube->addComponent<ModelHandler>()
            ->setModel("Cube/Cube.obj")
            .setTexture("Colours/BlackTexture.png")
            .setShaders("Lit/VertexShader.glsl", "Lit/FragmentShader.glsl");
        transformcube = cube->findComponent<Transform>();
        transformcube.lock()->setPosition(glm::vec3(7.05f, 2.4f, 0.0f));
        transformcube.lock()->setScale(glm::vec3(0.2f, 2.2f, 0.1f));

        cube = defaultModule->addEntity();
        cube->addComponent<ModelHandler>()
            ->setModel("Cube/Cube.obj")
            .setTexture("Colours/BlackTexture.png")
            .setShaders("Lit/VertexShader.glsl", "Lit/FragmentShader.glsl");
        transformcube = cube->findComponent<Transform>();
        transformcube.lock()->setPosition(glm::vec3(10.2f, 4.4f, 0.0f));
        transformcube.lock()->setScale(glm::vec3(3.0f, 0.2f, 0.1f));


        /* Portal Two Boarder Cubes */
        cube = defaultModule->addEntity();
        cube->addComponent<ModelHandler>()
            ->setModel("Cube/Cube.obj")
            .setTexture("Colours/BlackTexture.png")
            .setShaders("Lit/VertexShader.glsl", "Lit/FragmentShader.glsl");
        transformcube = cube->findComponent<Transform>();
        transformcube.lock()->setPosition(glm::vec3(-13.2f, 2.4f, 0.0f));
        transformcube.lock()->setScale(glm::vec3(0.2f, 2.2f, 0.1f));

        cube = defaultModule->addEntity();
        cube->addComponent<ModelHandler>()
            ->setModel("Cube/Cube.obj")
            .setTexture("Colours/BlackTexture.png")
            .setShaders("Lit/VertexShader.glsl", "Lit/FragmentShader.glsl");
        transformcube = cube->findComponent<Transform>();
        transformcube.lock()->setPosition(glm::vec3(-7.2f, 2.4f, 0.0f));
        transformcube.lock()->setScale(glm::vec3(0.2f, 2.2f, 0.1f));

        cube = defaultModule->addEntity();
        cube->addComponent<ModelHandler>()
            ->setModel("Cube/Cube.obj")
            .setTexture("Colours/BlackTexture.png")
            .setShaders("Lit/VertexShader.glsl", "Lit/FragmentShader.glsl");
        transformcube = cube->findComponent<Transform>();
        transformcube.lock()->setPosition(glm::vec3(-10.2f, 4.4f, 0.0f));
        transformcube.lock()->setScale(glm::vec3(3.0f, 0.2f, 0.1f));
    }
}