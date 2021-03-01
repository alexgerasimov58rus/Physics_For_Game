
#pragma once

#include "../tools_exp.hpp"

namespace obj_tools {
	struct OBJ_TOOLS_EXPORT Vector2D
	{
		friend Vector2D operator *(const float& s, const Vector2D& v);

		Vector2D(void);
		Vector2D(const float& x, const float& y);
		Vector2D(const Vector2D& v);

		void setX (const float& x) { this->x_ = x; }
		void setY (const float& y) { this->y_ = y; }

		float getX(void) { return this->x_; }
		float getY(void) { return this->y_; }

		Vector2D& operator =  (const Vector2D& v);

		Vector2D  operator +  (const Vector2D& v);
		Vector2D  operator -  (const Vector2D& v);
		Vector2D  operator *  (const float& s);

		Vector2D& operator += (const Vector2D& v);
		Vector2D& operator -= (const Vector2D& v);
		Vector2D& operator *= (const float& s);

		double dot(const Vector2D& v);
		double norm(void);
		double normSquared(void);

		Vector2D normalize(const float& tolerance);

		private: //_______________________________

		float x_, y_;
	};
};