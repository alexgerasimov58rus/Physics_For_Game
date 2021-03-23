
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