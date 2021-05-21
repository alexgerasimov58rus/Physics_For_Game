
#pragma once

#include "../tools_exp.hpp"
#include "../Vector/Vector3D.hpp"

namespace obj_tools {

	struct OBJ_TOOLS_EXPORT Force
	{
		Force(void);
		
		void applyConstantForce(const Vector3D& force);
		void applyImpulseForce(const Vector3D& force, const float& timeOfAction);

		void applyGravityForce(const float& mass);
		void undoGravityForce(void) { forceGravity_ = Vector3D(); }


		void setPointForceLocation(const Vector3D& point) { this->forceLocation_ = point; }
		void update(const float& dT);

		Vector3D getForce(void) const;
		Vector3D getPointLocation(void) const { return forceLocation_; }

		void setForce(const Vector3D& force);

		private: //_____________________________
	
		float timeOfAction_;
		bool isConstant_;

		Vector3D forceVector_;
		Vector3D forceLocation_;
		Vector3D forceGravity_;
	};
};