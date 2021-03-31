
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

		private: //_____________________________
	
		Vector3D orientation_;
		Vector3D angularVel_;
		Vector3D rotationInertia_;
	};
};