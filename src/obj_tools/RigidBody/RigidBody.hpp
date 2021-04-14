
#pragma once

#include "../tools_exp.hpp"
#include "../PointMass/PointMass.hpp"

namespace obj_tools {

	struct OBJ_TOOLS_EXPORT RigidBody: PointMass
	{
		RigidBody(Mesh* mesh, const float& mass);

		void update(const float& dTime);
		void render(void);
		void stop(void);

		void setRotationInertia(const Vector3D& rotationInertia) { this->rotationInertia_ = rotationInertia; }
		void setAngularVelocity(const Vector3D& velocity) { this->angularVel_ = velocity; }

		const Vector3D& getAngularVelocity(void) const { return angularVel_; }
		const Vector3D& getRotationInertia(void) const { return rotationInertia_; }

		private: //_____________________________
	
		Vector3D orientation_;
		Vector3D angularVel_;
		Vector3D rotationInertia_;
	};
};