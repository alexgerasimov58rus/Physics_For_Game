
#pragma once

#include "../tools_exp.hpp"

namespace obj_tools {
	struct OBJ_TOOLS_EXPORT Vector2D
	{
		friend OBJ_TOOLS_EXPORT Vector2D operator *(const float& s, const Vector2D& v);

		Vector2D(void);
		Vector2D(const float& x, const float& y);
		Vector2D(const Vector2D& v);

		void setX (const float& x) { this->x_ = x; }
		void setY (const float& y) { this->y_ = y; }

		float getX(void) const { return this->x_; }
		float getY(void) const { return this->y_; }

		Vector2D& operator =  (const Vector2D& v);

		Vector2D  operator +  (const Vector2D& v) const;
		Vector2D  operator -  (const Vector2D& v) const;
		Vector2D  operator *  (const float& s)    const;

		Vector2D& operator += (const Vector2D& v);
		Vector2D& operator -= (const Vector2D& v);
		Vector2D& operator *= (const float& s);

		bool	  operator == (const Vector2D& v) const;

		double dot(const Vector2D& v) const;
		double norm(void) const;
		double normSquared(void) const;

		Vector2D normalize(const double& tolerance = 1e-6) const;

		private: //_______________________________

		float x_, y_;
	};
};