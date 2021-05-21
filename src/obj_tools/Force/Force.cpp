
#include "Force.hpp"
#include "../Math/Math.hpp"
#include "math.h"

using namespace obj_tools;

Force::Force(void) {
    timeOfAction_ = -1.0f;
    isConstant_ = true;
}

void Force::applyConstantForce(const Vector3D& force) {
    forceVector_ = force;
    timeOfAction_ = 1.0f;
    isConstant_ = true;
}

void Force::applyImpulseForce(const Vector3D& force, const float& timeOfAction) {
    forceVector_ = force;
    timeOfAction_ = -timeOfAction;
    isConstant_ = false;
}

void Force::applyGravityForce(const float& mass) { 
    forceGravity_ = Vector3D(0.0f, -(float)Math::G * mass, 0.0f); 
}

void Force::update(const float& dT) {
    if (timeOfAction_ < 0.0f) {
        timeOfAction_ += dT;
    }
}

Vector3D Force::getForce(void) const {
    Vector3D force = forceVector_;

    if (!isConstant_) {
        force = (timeOfAction_ < 0.0f) ? forceVector_ : Vector3D();
    }

    return force + forceGravity_;
}

void Force::setForce(const Vector3D& force) {
    this->forceVector_ = force;
}