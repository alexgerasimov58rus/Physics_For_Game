#pragma once

#include "../tools_exp.hpp"

namespace obj_tools {
	struct OBJ_TOOLS_EXPORT Matrix2x2
	{
		friend OBJ_TOOLS_EXPORT Matrix2x2 operator *  (const float& s, const Matrix2x2& m);

		Matrix2x2(void);
		Matrix2x2(const Matrix2x2& m);

		Matrix2x2& operator =(const Matrix2x2& m);

		float getElement(const int& row, const int& col) const;
		void  setElement(const int& row, const int& col, const float& value);

		Matrix2x2  operator +  (const Matrix2x2& m) const;
		Matrix2x2  operator -  (const Matrix2x2& m) const;
		Matrix2x2  operator *  (const float& s) const;
		Matrix2x2& operator += (const Matrix2x2& m);
		Matrix2x2& operator -= (const Matrix2x2& m);
		Matrix2x2& operator *= (const float& s);

		Matrix2x2  operator *  (const Matrix2x2& m) const;

		bool	   operator == (const Matrix2x2& m) const;

		Matrix2x2 transposition(void) const;
		Matrix2x2 inverse(void) const;

		float determinant(void) const;

		private: //__________________

		float elements_[2][2];
	};
};