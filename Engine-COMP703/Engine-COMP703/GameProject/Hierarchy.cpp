#include "Hierarchy.h"

#include "CameraController.h"
#include "Portal.h"
#include "PortalTeleportationHandler.h"

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
        transformCameraEntity.lock()->setPosition(glm::vec3(13.0f, 5.5f, -4.0f));

        RigidBodyObj rigidBody = cameraEntity->addComponent<RigidBody>();
        rigidBody.lock()->setMass(1.0f);
        //rigidBody.lock()->setGravity(glm::vec3(0.0f, -19.6f, 0.0f));
        rigidBody.lock()->setGravity(glm::vec3(0.0f, 0.0f, 0.0f));
        camController.lock()->m_rigidBody = rigidBody;

        BoxColliderObj characterCollider = cameraEntity->addComponent<AABBCollider>();
        characterCollider.lock()->setColliderSize(glm::vec3(1.0f, 2.5f, 1.0f));
        characterCollider.lock()->setColliderOffset(glm::vec3(0.0f, 0.0f, 0.0f));
        camController.lock()->m_boxCollider = characterCollider;



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
        transformPortalOne.lock()->setPosition(glm::vec3(15.0f, 2.3f, 2.85f));

        BoxColliderObj portalCollider = portalOne->addComponent<AABBCollider>();
        portalCollider.lock()->setColliderSize(glm::vec3(6.0f, 4.0f, 0.01f));
        portalCollider.lock()->setColliderOffset(glm::vec3(0.0f, 0.2f, -0.4f));
        portalCollider.lock()->setTriggerCollider(true);
        portalCollider.lock()->setKinematicState(true);

        /* Cube 2 Making Use Of Render Texture */
        EntityObj portalTwo = defaultModule->addEntity();
        portalTwo->addComponent<ModelHandler>()
            ->setModel("Cube/PortalCube.obj")
            .setTexture(renderTexture2)
            .setShaders("unlit/VertexShader.glsl", "unlit/FragmentShader.glsl");

        TransformObj transformPortalTwo = portalTwo->findComponent<Transform>();
        transformPortalTwo.lock()->setRotation(glm::vec3(0.0f, 0.0f, 90.0f));
        transformPortalTwo.lock()->setPosition(glm::vec3(5.0f, 2.3f, 2.85f));


        /* Wall 1 */
        EntityObj wall1 = defaultModule->addEntity();
        wall1->addComponent<ModelHandler>()
            ->setModel("Cube/Cube.obj")
            .setTexture("Props/Portal/concrete_modular_wall001a.png")
            .setShaders("Lit/VertexShader-Wall.glsl", "Lit/FragmentShader.glsl");
        TransformObj transformcube1 = wall1->findComponent<Transform>();
        transformcube1.lock()->setPosition(glm::vec3(10.0f, 6.2f, 3.0f));
        transformcube1.lock()->setScale(glm::vec3(12.0f, 6.0f, 0.1f));
        BoxColliderObj wallCollider = wall1->addComponent<AABBCollider>();
        wallCollider.lock()->setColliderSize(glm::vec3(24.0f, 12.0f, 1.0f));
        wallCollider.lock()->setKinematicState(true);

        /* Wall 2 */
        EntityObj wall2 = defaultModule->addEntity();
        wall2->addComponent<ModelHandler>()
            ->setModel("Cube/Cube.obj")
            .setTexture("Props/Portal/concrete_modular_wall001a.png")
            .setShaders("Lit/VertexShader-Wall.glsl", "Lit/FragmentShader.glsl");
        TransformObj transformcube2 = wall2->findComponent<Transform>();
        transformcube2.lock()->setRotation(glm::vec3(0.0f, 90.0f, 0.0f));
        transformcube2.lock()->setPosition(glm::vec3(-2.0f, 6.2f, -9.0f));
        transformcube2.lock()->setScale(glm::vec3(12.0f, 6.0f, 0.1f));

        wallCollider = wall2->addComponent<AABBCollider>();
        wallCollider.lock()->setColliderSize(glm::vec3(1.0f, 12.0f, 24.0f));
        wallCollider.lock()->setKinematicState(true);


        /* Player Character Entity */
        EntityObj character = defaultModule->addEntity();
        character->addComponent<ModelHandler>()
            ->setModel("Curuthers/Curuthers.obj")
            .setTexture("Props/Curuthers/Curuthers.png")
            .setShaders("Lit/VertexShader.glsl", "Lit/FragmentShader.glsl");

        TransformObj playerTransform = character->findComponent<Transform>();
        playerTransform.lock()->setScale(glm::vec3(0.5f));

        camController.lock()->m_playerCharacter = playerTransform;


        /* Portal scripts setup */
        portalTwo->setStillTickStatus(true);
        std::weak_ptr<Portal> portal2 = portalTwo->addComponent<Portal>();
        portal2.lock()->m_portalEntity = portalTwo;
        portal2.lock()->m_portalTransform = transformPortalTwo;
        portal2.lock()->m_cameraTransform = transformTextureCameraEntity;
        portal2.lock()->m_playerTransform = transformCameraEntity;
        portal2.lock()->m_linkedPortalTransform = transformPortalOne;
        portal2.lock()->m_portalWall = wall1;
        portal2.lock()->m_characterEntity = character;

        

        portalOne->setStillTickStatus(true);
        std::weak_ptr<Portal> portal1 = portalOne->addComponent<Portal>();
        portal1.lock()->m_portalEntity = portalOne;
        portal1.lock()->m_portalTransform = transformPortalOne;
        portal1.lock()->m_cameraTransform = transformTextureCameraEntity2;
        portal1.lock()->m_playerTransform = transformCameraEntity;
        portal1.lock()->m_linkedPortalTransform = transformPortalTwo;
        portal1.lock()->m_portalWall = wall1;
        portal1.lock()->m_characterEntity = character;

        std::weak_ptr<PortalTeleportationHandler> portalHandler1 = portalOne->addComponent<PortalTeleportationHandler>();
        portalHandler1.lock()->m_playerTransform = transformCameraEntity;
        portalHandler1.lock()->m_linkedPortalTransform = transformPortalTwo;
        portalHandler1.lock()->m_portalCollider = portalCollider;
        portalHandler1.lock()->m_playerCollider = characterCollider;


        /* Floor Entity */
        EntityObj floor = defaultModule->addEntity();
        floor->addComponent<ModelHandler>()
            ->setModel("Cube/Cube.obj")
            .setTexture("Props/Portal/concrete_modular_floor001a.png")
            .setShaders("Lit/VertexShader-Floor.glsl", "Lit/FragmentShader.glsl");

        TransformObj transformFloor = floor->findComponent<Transform>();
        transformFloor.lock()->setPosition(glm::vec3(10.0f, 0.1f, -9.0f));
        transformFloor.lock()->setScale(glm::vec3(12.0f, 0.2f, 12.0f));

        BoxColliderObj boxCollider = floor->addComponent<AABBCollider>();
        boxCollider.lock()->setColliderSize(glm::vec3(24.0f, 0.5f, 24.0f));
        boxCollider.lock()->setKinematicState(true);

        /* Roof Entity */
        EntityObj roof = defaultModule->addEntity();
        roof->addComponent<ModelHandler>()
            ->setModel("Cube/Cube.obj")
            .setTexture("Props/Portal/concrete_modular_floor001a.png")
            .setShaders("Lit/VertexShader-Floor.glsl", "Lit/FragmentShader.glsl");

        TransformObj transformRoof = roof->findComponent<Transform>();
        transformRoof.lock()->setPosition(glm::vec3(10.0f, 12.1f, -9.0f));
        transformRoof.lock()->setScale(glm::vec3(12.0f, 0.2f, 12.0f));

        boxCollider = roof->addComponent<AABBCollider>();
        boxCollider.lock()->setColliderSize(glm::vec3(24.0f, 0.4f, 24.0f));
        boxCollider.lock()->setKinematicState(true);



        /* Cubes In Scene  */
        EntityObj cube = defaultModule->addEntity();
        cube->addComponent<ModelHandler>()
            ->setModel("Cube/Cube.obj")
            .setTexture("Props/compcube.png")
            .setShaders("Lit/VertexShader.glsl", "Lit/FragmentShader.glsl");
        TransformObj transformcube = cube->findComponent<Transform>();
        transformcube.lock()->setPosition(glm::vec3(6.5f, 1.1f, -4.5f));
        transformcube.lock()->setScale(glm::vec3(0.8f));

        cube = defaultModule->addEntity();
        cube->addComponent<ModelHandler>()
            ->setModel("Cube/Cube.obj")
            .setTexture("Props/compcube.png")
            .setShaders("Lit/VertexShader.glsl", "Lit/FragmentShader.glsl");
        transformcube = cube->findComponent<Transform>();
        transformcube.lock()->setPosition(glm::vec3(15.0f, 1.2f, -14.0f));
        transformcube.lock()->setScale(glm::vec3(0.9f));


        /* Portal One Boarder Cubes */
        cube = defaultModule->addEntity();
        cube->addComponent<ModelHandler>()
            ->setModel("Cube/Cube.obj")
            .setTexture("Colours/BlueTexture.png")
            .setShaders("UnLit/VertexShader.glsl", "UnLit/FragmentShader.glsl");
        transformcube = cube->findComponent<Transform>();
        transformcube.lock()->setPosition(glm::vec3(18.2f, 2.4f, 2.9f));
        transformcube.lock()->setScale(glm::vec3(0.2f, 2.2f, 0.1f));

        cube = defaultModule->addEntity();
        cube->addComponent<ModelHandler>()
            ->setModel("Cube/Cube.obj")
            .setTexture("Colours/BlueTexture.png")
            .setShaders("UnLit/VertexShader.glsl", "UnLit/FragmentShader.glsl");
        transformcube = cube->findComponent<Transform>();
        transformcube.lock()->setPosition(glm::vec3(11.8f, 2.4f, 2.9f));
        transformcube.lock()->setScale(glm::vec3(0.2f, 2.2f, 0.1f));

        cube = defaultModule->addEntity();
        cube->addComponent<ModelHandler>()
            ->setModel("Cube/Cube.obj")
            .setTexture("Colours/BlueTexture.png")
            .setShaders("UnLit/VertexShader.glsl", "UnLit/FragmentShader.glsl");
        transformcube = cube->findComponent<Transform>();
        transformcube.lock()->setPosition(glm::vec3(15.0f, 4.5f, 2.9f));
        transformcube.lock()->setScale(glm::vec3(3.4f, 0.2f, 0.1f));


        /* Portal Two Boarder Cubes */
        cube = defaultModule->addEntity();
        cube->addComponent<ModelHandler>()
            ->setModel("Cube/Cube.obj")
            .setTexture("Colours/OrangeTexture.png")
            .setShaders("UnLit/VertexShader.glsl", "UnLit/FragmentShader.glsl");
        transformcube = cube->findComponent<Transform>();
        transformcube.lock()->setPosition(glm::vec3(8.2f, 2.4f, 2.9f));
        transformcube.lock()->setScale(glm::vec3(0.2f, 2.2f, 0.1f));

        cube = defaultModule->addEntity();
        cube->addComponent<ModelHandler>()
            ->setModel("Cube/Cube.obj")
            .setTexture("Colours/OrangeTexture.png")
            .setShaders("UnLit/VertexShader.glsl", "UnLit/FragmentShader.glsl");
        transformcube = cube->findComponent<Transform>();
        transformcube.lock()->setPosition(glm::vec3(1.8f, 2.4f, 2.9f));
        transformcube.lock()->setScale(glm::vec3(0.2f, 2.2f, 0.1f));

        cube = defaultModule->addEntity();
        cube->addComponent<ModelHandler>()
            ->setModel("Cube/Cube.obj")
            .setTexture("Colours/OrangeTexture.png")
            .setShaders("UnLit/VertexShader.glsl", "UnLit/FragmentShader.glsl");
        transformcube = cube->findComponent<Transform>();
        transformcube.lock()->setPosition(glm::vec3(5.0f, 4.5f, 2.9f));
        transformcube.lock()->setScale(glm::vec3(3.4f, 0.2f, 0.1f));

        /* Wall 3 */
        EntityObj wall = defaultModule->addEntity();
        wall->addComponent<ModelHandler>()
            ->setModel("Cube/Cube.obj")
            .setTexture("Props/Portal/concrete_modular_wall001a.png")
            .setShaders("Lit/VertexShader-Wall.glsl", "Lit/FragmentShader.glsl");
        TransformObj transformWall = wall->findComponent<Transform>();
        transformWall.lock()->setRotation(glm::vec3(0.0f, 90.0f, 0.0f));
        transformWall.lock()->setPosition(glm::vec3(22.0f, 6.2f, -9.0f));
        transformWall.lock()->setScale(glm::vec3(12.0f, 6.0f, 0.1f));

        wallCollider = wall->addComponent<AABBCollider>();
        wallCollider.lock()->setColliderSize(glm::vec3(1.0f, 12.0f, 24.0f));
        wallCollider.lock()->setKinematicState(true);
        wallCollider.lock()->setRenderOutline(true);

        /* Wall 4 */
        wall = defaultModule->addEntity();
        wall->addComponent<ModelHandler>()
            ->setModel("Cube/Cube.obj")
            .setTexture("Props/Portal/concrete_modular_wall001a.png")
            .setShaders("Lit/VertexShader-Wall.glsl", "Lit/FragmentShader.glsl");
        transformWall = wall->findComponent<Transform>();
        transformWall.lock()->setPosition(glm::vec3(10.0f, 6.2f, -21.0f));
        transformWall.lock()->setScale(glm::vec3(12.0f, 6.0f, 0.1f));

        wallCollider = wall->addComponent<AABBCollider>();
        wallCollider.lock()->setColliderSize(glm::vec3(24.0f, 12.0f, 1.0f));
        wallCollider.lock()->setKinematicState(true);
        wallCollider.lock()->setRenderOutline(true);
    }
}