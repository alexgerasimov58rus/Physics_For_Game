
#include "PointMass.hpp"
#include "../Mesh/Mesh.hpp"
#include "../Math/Math.hpp"

#ifdef WIN32
    #include <windows.h>
    #include <gl/gl.h>
#endif

using namespace obj_tools;
using namespace std;

PointMass::PointMass(Mesh* mesh, const float& mass): PointMassBase(mass) {
    this->mesh_ = mesh;
    boundingSphereRadius_ = mesh->getBoundingSphereRadius();
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

PointMassBase* PointMass::clone(void) {
    PointMassBase* p = new PointMass(mesh_, mass_);
    p->setCoeffElasticity(coeffElasticity_);
    p->setBoundingSphereRadius(boundingSphereRadius_);
    p->setLocation(centerMass_);
    p->setLinearVelocity(linearVel_);
    p->force_ = force_;
    
    return p;
}