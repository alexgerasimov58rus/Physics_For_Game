
#include "PointMass.hpp"
#include "../Mesh/Mesh.hpp"

#ifdef WIN32
    #include <windows.h>
    #include <gl/gl.h>
#endif

using namespace obj_tools;
using namespace std;

PointMass::PointMass(Mesh* mesh, const float& mass) {
    this->mesh_ = mesh;
    this->mass_ = mass;
    this->coeffElasticity_ = 0.5f;
}

void PointMass::update(const float& dTime) {
    force_.update(dTime);

    Vector3D linearAcc = force_.getForce() * (1.0f / mass_);
    linearVel_  += linearAcc  * dTime;
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
}

