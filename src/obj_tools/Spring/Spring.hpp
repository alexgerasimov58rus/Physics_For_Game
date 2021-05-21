
#pragma once

#include "../tools_exp.hpp"

namespace obj_tools {

	struct PointMassBase;

	struct OBJ_TOOLS_EXPORT Spring
	{
		Spring(const float& forceConstant, const float& dampeningFactor);

		void setEndPoints(PointMassBase* p1, PointMassBase* p2);
		
		bool isDisplaced(void);
		void update(const float& dTime);

		private: //_____________________________

		float restLength_;
		float forceConstant_;
		float dampeningFactor_;

		PointMassBase* p1_;
		PointMassBase* p2_;
	};
}