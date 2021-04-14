
#pragma once
#include "../tools_exp.hpp"
#include "Collision.hpp"
#include "../RigidBody/RigidBody.hpp"

namespace obj_tools {
    struct OBJ_TOOLS_EXPORT CollisionRigidBody: Collision
    {
        CollisionRigidBody(RigidBody* obj1, RigidBody* obj2)
            :Collision(obj1, obj2) {}

        protected: //_____________________________
        
        virtual void calcReactions(void);
        virtual void revertVelocityAndForce(void);
    };
}