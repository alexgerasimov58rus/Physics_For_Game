#pragma once

#include "../tools_exp.hpp"
#include "../Vector/Vector3D.hpp"
#include "../Matrix/Matrix3x3.hpp"

namespace obj_tools {

	struct Mesh;

	struct OBJ_TOOLS_EXPORT PointMass
	{
		PointMass(Mesh* mesh, const float& mass);
		
		void setForces  (const Vector3D& forces) { forces_ = forces;  }
		void setLocation(const Vector3D& location) { centerMass_ = location; }

		void update(const float& dTime);
		void render(void);
		void stop(void);

		private: //_____________________________
	
		Mesh* mesh_;
		float mass_;

		Vector3D centerMass_;
		Vector3D linearVel_;
		Vector3D linearAcc_;
		Vector3D forces_;

		Matrix3x3 matrix_;
	};
};