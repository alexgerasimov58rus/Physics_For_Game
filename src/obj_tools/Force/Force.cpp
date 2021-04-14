
#include "Force.hpp"
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

void Force::applyProvisionalForce(const Vector3D& force, const float& timeOfAction) {
    forceVector_ = force;
    timeOfAction_ = -timeOfAction;
    isConstant_ = false;
}

void Force::update(const float& dT) {
    if (timeOfAction_ < 0.0f) {
        timeOfAction_ += dT;
    }
}

Vector3D Force::getForce(void) const {
    if (!isConstant_) {
        return (timeOfAction_ < 0.0f) ? forceVector_ : Vector3D();
    }

    return forceVector_;
}

void Force::setForce(const Vector3D& force) {
    this->forceVector_ = force;
}