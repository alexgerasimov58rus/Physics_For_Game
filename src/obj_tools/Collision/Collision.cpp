
#include "Collision.hpp"
#include "../PointMass/PointMass.hpp"
#include "../Mesh/Mesh.hpp"
#include <math.h>

#define DIST_TOUCHING 1e-3
#define ZERO_TIME 1e-6

using namespace obj_tools;

COLLISION_STATUS Collision::colissionOccured(void) const {
    Vector3D distanceVector = obj1_->getLocation() - obj2_->getLocation();
    double distance = fabs(distanceVector.norm()) -
        obj1_->getBoundingSphereRadius() - 
        obj2_->getBoundingSphereRadius();

    if (fabs(distance) < DIST_TOUCHING) return COLLISION_STATUS::COLLISION_TOUCHING;
    if (distance  < 0.0 ) return COLLISION_STATUS::COLLISION_OVERLAPPING;

    return COLLISION_STATUS::COLLISION_NONE;
}

bool Collision::handleCollision(const float& dTime) {
    COLLISION_STATUS status = colissionOccured();

    switch (status) {
        case COLLISION_STATUS::COLLISION_TOUCHING: calcReactions(); return true;
        case COLLISION_STATUS::COLLISION_OVERLAPPING: handleOverlapping(dTime); return true;
    }

    return false;
}

void Collision::calcReactions(void){
    Vector3D distance = obj1_->getLocation() - obj2_->getLocation();
    Vector3D unitNormal = distance.normalize();

    float vel1 = (float)obj1_->getLinearVelocity().dot(unitNormal);
    float vel2 = (float)obj2_->getLinearVelocity().dot(unitNormal);

    float averageCoeffE = (obj1_->getCoeffElasticity() + obj2_->getCoeffElasticity()) / 2.0f;

    float finalVel1 = ((obj1_->getMass() - averageCoeffE * obj2_->getMass()) * vel1 + (1 + averageCoeffE) * obj2_->getMass() * vel2) / (obj1_->getMass() + obj2_->getMass());
    float finalVel2 = ((obj2_->getMass() - averageCoeffE * obj1_->getMass()) * vel2 + (1 + averageCoeffE) * obj1_->getMass() * vel1) / (obj1_->getMass() + obj2_->getMass());

    obj1_->setLinearVelocity((finalVel1 - vel1) * unitNormal + obj1_->getLinearVelocity());
    obj2_->setLinearVelocity((finalVel2 - vel2) * unitNormal + obj2_->getLinearVelocity());
}

void Collision::handleOverlapping(const float& dTime) {
    float dT = dTime;
    COLLISION_STATUS status = COLLISION_STATUS::COLLISION_OVERLAPPING;

    for(bool done = false; (!done) && !(fabs(dT) < ZERO_TIME); ) {
        switch (status) {
            case COLLISION_STATUS::COLLISION_OVERLAPPING:
                revertVelocityAndForce();
                obj1_->update(dT);
                obj2_->update(dT);
                dT /= 2.0f;

                revertVelocityAndForce();
                obj1_->update(dT);
                obj2_->update(dT);

                status = colissionOccured();

                break;

            case COLLISION_STATUS::COLLISION_TOUCHING:
                calcReactions();
                done = true;
                break;

            case COLLISION_STATUS::COLLISION_NONE:
                obj1_->update(dT);
                obj2_->update(dT);

                status = colissionOccured();
                
                break;
        }
    }

    if (fabs(dT) < ZERO_TIME) {
        calcReactions();
        obj1_->update(dT);
        obj2_->update(dT);
    }
}

void Collision::revertVelocityAndForce(void) {
    obj1_->setLinearVelocity(obj1_->getLinearVelocity() * -1.0f);
    obj2_->setLinearVelocity(obj2_->getLinearVelocity() * -1.0f);
    obj1_->force_.setForce(obj1_->force_.getForce() * -1.0f);
    obj2_->force_.setForce(obj2_->force_.getForce() * -1.0f);
}