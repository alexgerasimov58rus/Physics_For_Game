
#pragma once

#include "../tools_exp.hpp"
#include "../Vector/Vector3D.hpp"
#include "../Force/Force.hpp"

namespace obj_tools {

	struct OBJ_TOOLS_EXPORT PointMassBase
	{
		PointMassBase(const float& mass);

		virtual void update(const float& dTime);
		virtual void render(void) {}
		virtual void stop(void);
		virtual PointMassBase* clone(void);

		const float& getMass(void) const { return mass_; }
		const float& getCoeffElasticity(void) const { return coeffElasticity_; }
		const Vector3D& getLocation(void) const { return  centerMass_; }
		const Vector3D& getLinearVelocity(void) const { return linearVel_; }

		float getBoundingSphereRadius(void) const { return this->boundingSphereRadius_; }

		void setLinearVelocity(const Vector3D& velocity) { linearVel_ = velocity; }
		void setLocation(const Vector3D& location) { centerMass_ = location; }
		void setCoeffElasticity(const float& coeff) { coeffElasticity_ = coeff; }
		void setBoundingSphereRadius(const float& bsphere) { this->boundingSphereRadius_ = bsphere; }

		Force force_;

		protected: //_____________________________

		float mass_;
		float coeffElasticity_;

		Vector3D centerMass_;
		Vector3D linearVel_;

		float boundingSphereRadius_;
	};
};