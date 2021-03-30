
#include "PointMass.hpp"
#include "../Mesh/Mesh.hpp"

#ifdef WIN32
    #include <windows.h>
    #include <gl/gl.h>
#endif

using namespace obj_tools;
using namespace std;

void PointMass::handleCollision(PointMass* p1, PointMass* p2, const float& dTime) {
    Vector3D distance = p1->centerMass_ - p2->centerMass_;
    Vector3D unitNormal = distance.normalize();

    float vel1 = (float)p1->linearVel_.dot(unitNormal);
    float vel2 = (float)p2->linearVel_.dot(unitNormal);

    float averageCoeffE = (p1->coeffElasticity_ + p2->coeffElasticity_) / 2.0f;

    float finalVel1 = ( (p1->mass_ - averageCoeffE * p2->mass_) * vel1 + (1 + averageCoeffE) * p2->mass_ * vel2) / (p1->mass_ + p2->mass_);
    float finalVel2 = ( (p2->mass_ - averageCoeffE * p1->mass_) * vel2 + (1 + averageCoeffE) * p1->mass_ * vel1) / (p1->mass_ + p2->mass_);

    p1->linearVel_ = (finalVel1 - vel1) * unitNormal + p1->linearVel_;
    p2->linearVel_ = (finalVel2 - vel2) * unitNormal + p2->linearVel_;

    Vector3D velNormalize1 = p1->linearVel_.normalize();
    Vector3D velNormalize2 = p2->linearVel_.normalize();

    p1->forces_ = Vector3D(
        (float)fabs(p1->forces_.getX()) * velNormalize1.getX(), 
        (float)fabs(p1->forces_.getY()) * velNormalize1.getY(),
        (float)fabs(p1->forces_.getZ()) * velNormalize1.getZ());

    p2->forces_ = Vector3D(
        (float)fabs(p2->forces_.getX()) * velNormalize2.getX(),
        (float)fabs(p2->forces_.getY()) * velNormalize2.getY(),
        (float)fabs(p2->forces_.getZ()) * velNormalize2.getZ());
}

PointMass::PointMass(Mesh* mesh, const float& mass) {
    this->mesh_ = mesh;
    this->mass_ = mass;
    this->coeffElasticity_ = 0.5f;
}

bool PointMass::hasCollision(const PointMass& point) const {
    double distanceSquared = (centerMass_ - point.centerMass_).normSquared();
    double minDistanceSquared = mesh_->getBoundingSphereRadius() + point.mesh_->getBoundingSphereRadius();
    minDistanceSquared *= minDistanceSquared;

    return distanceSquared < minDistanceSquared;
}

void PointMass::update(const float& dTime) {
    linearAcc_   = forces_ * (1.0f / mass_);
    linearVel_  += linearAcc_ * dTime;
    centerMass_ += linearVel_ * dTime;
}

void PointMass::render(void) {
    float homogeneousMatrix[16] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        centerMass_.getX(), centerMass_.getY(), centerMass_.getZ(), 1.0f
    };

    glPushMatrix();        
        glMatrixMode(GL_MODELVIEW);
        glLoadMatrixf(homogeneousMatrix);
        mesh_->render();
    glPopMatrix();
}

void PointMass::stop(void) {
    linearVel_ = Vector3D();
    linearAcc_ = Vector3D();
}