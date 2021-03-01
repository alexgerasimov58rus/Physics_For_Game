#pragma once

#include "../tools_exp.hpp"

namespace obj_tools {
	struct OBJ_TOOLS_EXPORT Matrix2x2
	{
		Matrix2x2(void);
		Matrix2x2(float elements[2][2]);
		Matrix2x2(const Matrix2x2& m);

		Matrix2x2& operator =(float elements[2][2]);
		Matrix2x2& operator =(const Matrix2x2& m);

		float getElement(const int& row, const int& col);
		void  setElement(const int& row, const int& col, const float& value);

		private: //__________________

		float elements_[2][2];
	};
};