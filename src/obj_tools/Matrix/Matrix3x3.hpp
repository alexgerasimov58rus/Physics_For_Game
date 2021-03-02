#pragma once

#include "../tools_exp.hpp"

namespace obj_tools {
	struct OBJ_TOOLS_EXPORT Matrix3x3
	{
		friend Matrix3x3  operator *  (const float& s, const Matrix3x3& m);

		Matrix3x3(void);
		Matrix3x3(float elements[3][3]);
		Matrix3x3(const Matrix3x3& m);

		Matrix3x3& operator =(float elements[3][3]);
		Matrix3x3& operator =(const Matrix3x3& m);

		float getElement(const int& row, const int& col);
		void  setElement(const int& row, const int& col, const float& value);

		Matrix3x3  operator +  (const Matrix3x3& m);
		Matrix3x3  operator -  (const Matrix3x3& m);
		Matrix3x3& operator += (const Matrix3x3& m);
		Matrix3x3& operator -= (const Matrix3x3& m);
		Matrix3x3  operator *  (const float& s);
		Matrix3x3  operator *  (const Matrix3x3& m);

		Matrix3x3 transposition(void);
		Matrix3x3 inverse(void);

		float determinant(void);

	private: //__________________

		float elements_[3][3];
	};
};