
#pragma once

#include "../tools_exp.hpp"

namespace obj_tools {
	struct OBJ_TOOLS_EXPORT Vector3D
	{
		friend Vector3D operator *(const float& s, const Vector3D& v);

		Vector3D(void);
		Vector3D(const float& x, const float& y, const float& z);
		Vector3D(const Vector3D& v);

		void setX(const float& x) { this->x_ = x; }
		void setY(const float& y) { this->y_ = y; }
		void setZ(const float& z) { this->z_ = z; }

		float getX(void) { return this->x_; }
		float getY(void) { return this->y_; }
		float getZ(void) { return this->z_; }

		Vector3D& operator =  (const Vector3D& v);

		Vector3D  operator +  (const Vector3D& v);
		Vector3D  operator -  (const Vector3D& v);
		Vector3D  operator *  (const float& s);

		Vector3D& operator += (const Vector3D& v);
		Vector3D& operator -= (const Vector3D& v);
		Vector3D& operator *= (const float& s);

		double dot(const Vector3D& v);
		double norm(void);
		double normSquared(void);

		Vector3D normalize(const float& tolerance);
		Vector3D cross(const Vector3D& v);

		private: //_____________________________

		float x_, y_, z_;
	};
};