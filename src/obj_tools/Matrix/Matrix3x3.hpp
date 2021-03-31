#pragma once

#include "../tools_exp.hpp"

namespace obj_tools {
	struct OBJ_TOOLS_EXPORT Matrix3x3
	{
		friend OBJ_TOOLS_EXPORT Matrix3x3  operator *  (const float& s, const Matrix3x3& m);

		static Matrix3x3 createScaleMatrix(const float& dx, const float& dy, const float& dz);
		
		static Matrix3x3 createRotateXMatrix(const double& rad);
		static Matrix3x3 createRotateYMatrix(const double& rad);
		static Matrix3x3 createRotateZMatrix(const double& rad);

		Matrix3x3(void);
		Matrix3x3(const Matrix3x3& m);

		Matrix3x3& operator =(const Matrix3x3& m);

		float getElement(const int& row, const int& col) const;
		void  setElement(const int& row, const int& col, const float& value);

		Matrix3x3  operator +  (const Matrix3x3& m) const;
		Matrix3x3  operator -  (const Matrix3x3& m) const;
		Matrix3x3  operator *  (const float& s) const;
		Matrix3x3& operator += (const Matrix3x3& m);
		Matrix3x3& operator -= (const Matrix3x3& m);
		Matrix3x3  operator *= (const float& s);
		
		Matrix3x3  operator *  (const Matrix3x3& m) const;

		bool	   operator == (const Matrix3x3& m) const;

		Matrix3x3 transposition(void) const;
		Matrix3x3 inverse(void) const;

		float determinant(void) const;

	private: //__________________

		float elements_[3][3];
	};
};