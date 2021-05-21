#pragma once

#include "../tools_exp.hpp"
#include "PointMassBase.hpp"

namespace obj_tools {

	struct Mesh;

	struct OBJ_TOOLS_EXPORT PointMass: PointMassBase
	{
		PointMass(Mesh* mesh, const float& mass);

		virtual void render(void);
		virtual PointMassBase* clone(void);
		
		Mesh* mesh_;
	};
};