
#include "Cloth.hpp"
#include "../Vector/Vector3D.hpp"
#include "../PointMass/PointMassBase.hpp"
#include "../Spring/Spring.hpp"

using namespace obj_tools;

Cloth::Cloth(
    const int& particleRows,
    const int& particleCols,
    PointMassBase* particle,
    const float& spaceBetweenParticles,
    const float& clothStiffnes,
    const float& dampeningFactor,
    const float& linearDampeningFactor,
    const Vector3D upLeftCorner) 
{
    linearDampeningCoeff_ = linearDampeningFactor;

    particles_.resize(particleRows);                    //TDDO need delete
    for (int i = 0; i < particleRows; i++){
        for (int j = 0; j < particleCols; j++){
            particles_[i].push_back(particle->clone());
        }
    }

    totalSprings_ =
        particleRows * (particleCols - 1) +
        particleCols * (particleRows - 1) + (particleRows - 1) * (particleCols - 1) * 2;
              
    for (int i = 0; i < totalSprings_; i++) {                           //TDDO need delete
        springs_.push_back(new Spring(clothStiffnes, dampeningFactor));
    }

    squares_.resize(particleRows - 1);
    for (int i = 0; i < particleRows - 1; i++) {
        for (int j = 0; j < particleCols - 1; j++) {
            squares_[i].push_back(cloth_square());
        }
    }

    Vector3D location = upLeftCorner;

    for (int i = 0; i < particleRows; i++) {
        for (int j = 0; j < particleCols; j++) {
            particles_[i][j]->setLocation(location);

            location.setX(location.getX() + spaceBetweenParticles);
        }

        location.setX(upLeftCorner.getX());
        location.setY(location.getY() - spaceBetweenParticles);
    }

    index_pair tempIndex;
    int currentSpring = 0;

    for (int i = 0; i < particleRows; i++){
        for (int j = 0; j < particleCols - 1; j++, currentSpring++){
            springs_[currentSpring]->setEndPoints(particles_[i][j], particles_[i][j + 1]);

            if (i < particleRows - 1) {
                squares_[i][j].springIndex[TOP_SPRING] = currentSpring;

                tempIndex.row = i;
                tempIndex.col = j;

                squares_[i][j].particleIndex[TOP_LEFT_PARTICLE] = tempIndex;
                tempIndex.col = j + 1;
                squares_[i][j].particleIndex[TOP_RIGHT_PARTICLE] = tempIndex;
            }

            if (i > 0) {
                squares_[i - 1][j].springIndex[BOTTOM_SPRING] = currentSpring;
                
                tempIndex.row = i;
                tempIndex.col = j;
                squares_[i - 1][j].particleIndex[BOTTOM_LEFT_PARTICLE] = tempIndex;

                tempIndex.col = j + 1;
                squares_[i - 1][j].particleIndex[BOTTOM_RIGHT_PARTICLE] = tempIndex;
            }
        }
    }

    for (int i = 0; i < particleRows - 1; i++){
        for (int j = 0; j < particleCols; j++, currentSpring++){
            springs_[currentSpring]->setEndPoints(particles_[i][j], particles_[i + 1][j]);

            if (j < particleCols - 1) {
                squares_[i][j].springIndex[LEFT_SPRING] = currentSpring;

                tempIndex.row = i;
                tempIndex.col = j;
                squares_[i][j].particleIndex[TOP_LEFT_PARTICLE] = tempIndex;
                tempIndex.row = i + 1;
                squares_[i][j].particleIndex[BOTTOM_LEFT_PARTICLE] = tempIndex;
            }

            if (j > 0) {
                squares_[i][j - 1].springIndex[RIGHT_SPRING] = currentSpring;

                tempIndex.row = i;
                tempIndex.col = j;
                squares_[i][j - 1].particleIndex[TOP_RIGHT_PARTICLE] = tempIndex;
                tempIndex.row = i + 1;
                squares_[i][j - 1].particleIndex[BOTTOM_RIGHT_PARTICLE] = tempIndex;
            }
        }
    }

    for (int i = 0; i < particleRows - 1; i++){
        for (int j = 0; j < particleCols - 1; j++){
            springs_[currentSpring]->setEndPoints(particles_[i][j], particles_[i + 1][j + 1]);
            squares_[i][j].springIndex[TOP_RIGHT_TO_BOTTOM_LEFT_SPRING] = currentSpring++;

            springs_[currentSpring]->setEndPoints(particles_[i][j + 1], particles_[i + 1][j]);
            squares_[i][j].springIndex[TOP_LEFT_TO_BOTTOM_RIGHT_SPRING] = currentSpring++;
        }
    }

    totalRows_ = particleRows;
    totalCols_ = particleCols;
}

void Cloth::update(const float& dTime) {
    for (int i = 0; i < totalSprings_; i++){
        if (springs_[i]->isDisplaced()) {
            springs_[i]->update(dTime);
        }
    }

    for (int i = 0; i < totalRows_; i++){
        for (int j = 0; j < totalCols_; j++){

            for (int k = i; k < totalRows_; k++){
                for (int m = j + 1; m < totalCols_; m++){
                    Vector3D distance =
                        particles_[i][j]->getLocation() -
                        particles_[k][m]->getLocation();

                    double distanceSquared = distance.normSquared();

                    float minDistanceSquared =
                        particles_[i][j]->getBoundingSphereRadius() +
                        particles_[k][m]->getBoundingSphereRadius();

                    minDistanceSquared *= minDistanceSquared;

                    if (distanceSquared < minDistanceSquared) {
                        index_pair firstParticle, secondParticle;
                        firstParticle.row = i;
                        firstParticle.col = j;
                        secondParticle.row = k;
                        secondParticle.col = m;

                        handleCollision(distance, dTime, firstParticle, secondParticle);
                    }
                }
            }
        }
    }

    Vector3D dampening;
    for (int i = 0; i < totalRows_; i++){
        for (int j = 0; j < totalCols_; j++) {
            dampening = -linearDampeningCoeff_ * particles_[i][j]->getLinearVelocity();
            particles_[i][j]->setLinearVelocity(particles_[i][j]->getLinearVelocity() + dampening);
        }
    }

    for (int i = 0; i < totalRows_; i++) {
        for (int j = 0; j < totalCols_; j++) {
            particles_[i][j]->update(dTime);
        }
    }
}

void Cloth::render(void) {
    for (int i = 0; i < totalRows_; i++) {
        for (int j = 0; j < totalCols_; j++) {
            particles_[i][j]->render();
        }
    }
}

void Cloth::applyImpulseForce(int row, int col, const Vector3D& force, const float& timeOfAction) {
    if (row >= 0 && row < totalRows_ &&
        col >= 0 && col < totalCols_) {
        particles_[row][col]->force_.applyImpulseForce(force, timeOfAction);
    }
}

void Cloth::handleCollision(Vector3D separationDistance, float changeInTime, index_pair firstParticle, index_pair secondParticle){
    int row1 = firstParticle.row;
    int col1 = firstParticle.col;
    int row2 = secondParticle.row;
    int col2 = secondParticle.col;
    
    Vector3D unitNormal =
        separationDistance.normalize();

    float velocity1 = (float)particles_[row1][col1]->getLinearVelocity().dot(unitNormal);
    float velocity2 = (float)particles_[row2][col2]->getLinearVelocity().dot(unitNormal);

    float averageE = (particles_[row1][col1]->getCoeffElasticity() * particles_[row2][col2]->getCoeffElasticity()) / 2;

    float finalVelocity1 =
        (((particles_[row1][col1]->getMass() -
            (averageE       * particles_[row2][col2]->getMass())) * velocity1) +
            ((1 + averageE) * particles_[row2][col2]->getMass()   * velocity2)) / 
                             (particles_[row1][col1]->getMass() +
                              particles_[row2][col2]->getMass());
    
    float finalVelocity2 =
        (((particles_[row2][col2]->getMass() -
            (averageE       * particles_[row1][col1]->getMass())) * velocity2) +
            ((1 + averageE) * particles_[row1][col1]->getMass()   * velocity1)) /
                             (particles_[row1][col1]->getMass()   + 
                              particles_[row2][col2]->getMass());

    particles_[row1][col1]->setLinearVelocity( (finalVelocity1 - velocity1) * unitNormal + particles_[row1][col1]->getLinearVelocity());
    particles_[row2][col2]->setLinearVelocity( (finalVelocity2 - velocity2) * unitNormal + particles_[row1][col1]->getLinearVelocity());

    Vector3D acceleration1 = particles_[row1][col1]->getLinearVelocity() * (1.0f / changeInTime);
    Vector3D acceleration2 = particles_[row2][col2]->getLinearVelocity() * (1.0f / changeInTime);

    particles_[row1][col1]->force_.applyImpulseForce(
        particles_[row1][col1]->force_.getForce() + acceleration1 * particles_[row1][col1]->getMass(), changeInTime);
    particles_[row2][col2]->force_.applyImpulseForce(
        particles_[row2][col2]->force_.getForce() + acceleration2 * particles_[row2][col2]->getMass(), changeInTime);
}
