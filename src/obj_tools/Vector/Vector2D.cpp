
#include "Vector2D.hpp"
#include <math.h>

using namespace obj_tools;

Vector2D obj_tools::operator*(const float& s, const Vector2D& v) {
	return Vector2D(
		s * v.x_, 
		s * v.y_
	);
}

Vector2D::Vector2D(void) {
	this->x_ = 0.0f; 
	this->y_ = 0.0f;
}

Vector2D::Vector2D(const float& x, const float& y) {
	this->x_ = x; 
	this->y_ = y;
}

Vector2D::Vector2D(const Vector2D& v) {
	this->x_ = v.x_;
	this->y_ = v.y_;
}

Vector2D& Vector2D::operator = (const Vector2D& v){
	this->x_ = v.x_;
	this->y_ = v.y_;

	return *this;
}

Vector2D Vector2D::operator +  (const Vector2D& v) { 
	return Vector2D(
		this->x_ + v.x_, 
		this->y_ + v.y_
	); 
}

Vector2D Vector2D::operator -  (const Vector2D& v) {	
	return Vector2D(
		this->x_ - v.x_, 
		this->y_ - v.y_
	); 
}

Vector2D Vector2D::operator *  (const float& s) { 
	return Vector2D(
		this->x_ * s, 
		this->y_ * s
	); 
}

Vector2D& Vector2D::operator += (const Vector2D& v){
	this->x_ += v.x_;
	this->y_ += v.y_;

	return *this;
}

Vector2D& Vector2D::operator -= (const Vector2D& v) {
	this->x_ -= v.x_;
	this->y_ -= v.y_;

	return *this;
}

Vector2D& Vector2D::operator *= (const float& s) {
	this->x_ *= s;
	this->y_ *= s;

	return *this;
}

double Vector2D::dot(const Vector2D& v) {
	return (
		this->x_ * (double)v.x_ + 
		this->y_ * (double)v.y_
	);
}

double Vector2D::norm		(void) { return sqrt(normSquared()); }
double Vector2D::normSquared(void) { return dot(*this); }

Vector2D Vector2D::normalize(const float& tolerance){
	Vector2D v;

	double length = this->norm();
	if (length >= tolerance) {
		v = *this * (1 / length);
	}

	return v;
}