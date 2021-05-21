
#include "Spring.hpp"
#include "../PointMass/PointMassBase.hpp"
#include "../Math/Math.hpp"

using namespace obj_tools;


Spring::Spring(const float& forceConstant, const float& dampeningFactor) {
	this->p1_ = 0;
	this->p2_ = 0;

	this->restLength_ = 1.0f;
	this->forceConstant_ = forceConstant;
	this->dampeningFactor_ = dampeningFactor;
}

void Spring::setEndPoints(PointMassBase* p1, PointMassBase* p2) {
	this->p1_ = p1;
	this->p2_ = p2;

	this->restLength_ = (float)(p1_->getLocation() - p2_->getLocation()).norm();
}

bool Spring::isDisplaced(void) {
	Vector3D currentLength = 
		p1_->getLocation() - 
		p2_->getLocation();
	
	double lengthDifference = 
		currentLength.normSquared() - ((double)restLength_ * restLength_);


	return !Math::isCloseToZero((float)lengthDifference);
}

void Spring::update(const float& dTime) {
	Vector3D currentLength =
		p1_->getLocation() -
		p2_->getLocation();

	float currentLengthMagnitude = (float)currentLength.norm();
	float changeInLength = currentLengthMagnitude - restLength_;

	if (Math::isCloseToZero(changeInLength)) changeInLength = 0.0f;

	float springForceMagnitude = forceConstant_ * changeInLength;

	float dampeningForceMagnitude;
	if (dTime < 1.0f){
		dampeningForceMagnitude =
			dampeningFactor_ * changeInLength * dTime;
	} else {
		dampeningForceMagnitude =
			dampeningFactor_ * changeInLength / dTime;
	}

	if (dampeningForceMagnitude > springForceMagnitude){
		dampeningForceMagnitude = springForceMagnitude;
	}

	float responseForceMagnitude = 
		springForceMagnitude - dampeningForceMagnitude;

	Vector3D responseForce = 
		responseForceMagnitude * currentLength.normalize();

	p1_->force_.applyImpulseForce(p1_->force_.getForce() - responseForce, dTime);
	p2_->force_.applyImpulseForce(p2_->force_.getForce() + responseForce, dTime);

//	p1_->force_.setForce(p1_->force_.getForce() - responseForce);
//	p2_->force_.setForce(p2_->force_.getForce() + responseForce);
}