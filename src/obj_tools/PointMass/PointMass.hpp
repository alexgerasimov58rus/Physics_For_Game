#pragma once

#include "../tools_exp.hpp"
#include "../Vector/Vector3D.hpp"
#include "../Force/Force.hpp"

namespace obj_tools {

	struct Mesh;

	struct OBJ_TOOLS_EXPORT PointMass
	{
		static void handleCollision(PointMass* p1, PointMass* p2, const float& dTime);

		PointMass(Mesh* mesh, const float& mass);
		
		void setLocation(const Vector3D& location) { centerMass_ = location; }
		
		void setCoeffElasticity(const float& coeff) { coeffElasticity_ = coeff; }
		bool hasCollision(const PointMass& point) const;

		void update(const float& dTime);
		void render(void);
		void stop(void);

		Force force_;

		protected: //_____________________________
	
		Mesh* mesh_;
		float mass_;
		float coeffElasticity_;

		Vector3D centerMass_;
		Vector3D linearVel_;
		Vector3D linearAcc_;
	};
};