#pragma once
#include "../GameEngine/Component.h"

namespace PhysicsSystem
{
    struct PhysicsComponent : GameEngine::Component
    {
        /* Calls the override function onPhysicsUpdate() for all child entities */
        void physicsUpdate();

    protected:
        /* Calls on inherited overridden Physics update functions */
        virtual void onPhysicsUpdate();
    };
}