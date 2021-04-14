
#include "CollisionRigidBody.hpp"
#include "../Mesh/Mesh.hpp"

#define DIST_TOUCHING 1e-3
#define ZERO_TIME 1e-6

using namespace obj_tools;

void CollisionRigidBody::calcReactions(void) {
    Collision::calcReactions();
}

void CollisionRigidBody::revertVelocityAndForce(void) {
    RigidBody* obj1 = (RigidBody*)obj1_;
    RigidBody* obj2 = (RigidBody*)obj2_;

    obj1->setLinearVelocity(obj1->getLinearVelocity() * -1.0f);
    obj2->setLinearVelocity(obj2->getLinearVelocity() * -1.0f);

    obj1->setAngularVelocity(obj1->getAngularVelocity() * -1.0f);
    obj2->setAngularVelocity(obj2->getAngularVelocity() * -1.0f);

    obj1->force_.setForce(obj1->force_.getForce() * -1.0f);
    obj2->force_.setForce(obj2->force_.getForce() * -1.0f);
}