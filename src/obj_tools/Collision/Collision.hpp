
#pragma once
#include "../tools_exp.hpp"

namespace obj_tools {

    struct PointMass;

    enum class COLLISION_STATUS {
        COLLISION_NONE,
        COLLISION_TOUCHING,
        COLLISION_OVERLAPPING
    };

    struct OBJ_TOOLS_EXPORT Collision
    {
        Collision(PointMass* obj1, PointMass* obj2) { this->obj1_ = obj1; this->obj2_ = obj2; }

        COLLISION_STATUS colissionOccured(void) const;
        bool handleCollision(const float& dT);

        protected: //_____________________________
        
        void handleOverlapping(const float& dTime);

        virtual void calcReactions(void);
        virtual void revertVelocityAndForce(void);

        PointMass* obj1_;
        PointMass* obj2_;
    };
}