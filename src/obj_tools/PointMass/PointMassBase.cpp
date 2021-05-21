
#include "PointMassBase.hpp"

using namespace obj_tools;

PointMassBase::PointMassBase(const float& mass) {
    this->mass_ = mass;
    this->coeffElasticity_ = 0.5f;
    boundingSphereRadius_ = 0.0f;
}

void PointMassBase::update(const float& dTime) {
    force_.update(dTime);

    Vector3D linearAcc = force_.getForce() * (1.0f / mass_);

    linearVel_ += linearAcc * dTime;
    centerMass_ += linearVel_ * dTime;
}

void PointMassBase::stop(void) {
    linearVel_ = Vector3D();
}

PointMassBase* PointMassBase::clone(void) {
    PointMassBase* p = new PointMassBase(mass_);
    p->setCoeffElasticity(coeffElasticity_);
    p->setBoundingSphereRadius(boundingSphereRadius_);
    p->setLocation(centerMass_);
    p->setLinearVelocity(linearVel_);
    p->force_ = force_;

    return p;
}