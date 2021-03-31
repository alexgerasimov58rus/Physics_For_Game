
#include "RigidBody.hpp"
#include "../Mesh/Mesh.hpp"
#include "../Matrix/Matrix3x3.hpp"

#ifdef WIN32
    #include <windows.h>
    #include <gl/gl.h>
#endif

using namespace obj_tools;

RigidBody::RigidBody(Mesh* mesh, const float& mass) :PointMass(mesh, mass) {
    rotationInertia_ = Vector3D(1.0f, 1.0f, 1.0f);
}

void RigidBody::update(const float& dTime) {
    PointMass::update(dTime);
    Vector3D torque = (force_.getForce()).cross(force_.getPointLocation());

    Vector3D angularAcc = Vector3D(
        torque.getX() / rotationInertia_.getX(),
        torque.getY() / rotationInertia_.getY(),
        torque.getZ() / rotationInertia_.getZ()
    );

    angularVel_ += angularAcc * dTime;

    orientation_ = Vector3D(
        orientation_.getX() + angularVel_.getX() * dTime,
        orientation_.getY() + angularVel_.getY() * dTime,
        orientation_.getZ() + angularVel_.getZ() * dTime
    );
}

void RigidBody::render(void) {
    Matrix3x3 rot= 
        Matrix3x3::createRotateXMatrix(orientation_.getX()) * 
        Matrix3x3::createRotateYMatrix(orientation_.getY()) *
        Matrix3x3::createRotateZMatrix(orientation_.getZ());

    float homogeneousMatrix[16] = {
        rot.getElement(0, 0), rot.getElement(1, 0)  , rot.getElement(2, 0)  , 0.0f,
        rot.getElement(0, 1), rot.getElement(1, 1)  , rot.getElement(2, 1)  , 0.0f,
        rot.getElement(0, 2), rot.getElement(1, 2)  , rot.getElement(2, 2)  , 0.0f,
        centerMass_.getX(  ), centerMass_.getY(  )  , centerMass_.getZ(  )  , 1.0f
    };

    glPushMatrix();
        glMatrixMode(GL_MODELVIEW);
        glLoadMatrixf(homogeneousMatrix);
        mesh_->render();
    glPopMatrix();
}

void RigidBody::stop(void) {
    PointMass::stop();

    orientation_ = Vector3D();
    angularVel_  = Vector3D();
}