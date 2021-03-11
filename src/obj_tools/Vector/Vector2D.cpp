
#include "Vector2D.hpp"
#include "../Matrix/Matrix2x2.hpp"
#include <math.h>

using namespace obj_tools;

Vector2D OBJ_TOOLS_EXPORT obj_tools::operator*(const float& s, const Vector2D& v) {
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

Vector2D Vector2D::operator +  (const Vector2D& v) const {
	return Vector2D(
		this->x_ + v.x_, 
		this->y_ + v.y_
	); 
}

Vector2D Vector2D::operator -  (const Vector2D& v) const {
	return Vector2D(
		this->x_ - v.x_, 
		this->y_ - v.y_
	); 
}

Vector2D Vector2D::operator *  (const float& s) const {
	return Vector2D(
		this->x_ * s, 
		this->y_ * s
	); 
}

Vector2D Vector2D::operator * (const Matrix2x2& m) const {
	return Vector2D(
		this->x_ * m.getElement(0, 0) + this->y_ * m.getElement(1 ,0),
		this->x_ * m.getElement(0, 1) + this->y_ * m.getElement(1, 1)
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

Vector2D& Vector2D::operator *= (const Matrix2x2& m) {
	float x = this->x_ * m.getElement(0, 0) + this->y_ * m.getElement(1, 0);
	float y = this->x_ * m.getElement(0, 1) + this->y_ * m.getElement(1, 1);

	this->x_ = x;
	this->y_ = y;

	return *this;
}

bool Vector2D::operator == (const Vector2D& v) const {
	return(
		this->x_ == v.x_ &&
		this->y_ == v.y_
	);
}

double Vector2D::dot(const Vector2D& v) const {
	return (
		this->x_ * (double)v.x_ + 
		this->y_ * (double)v.y_
	);
}

double Vector2D::norm		(void) const { return sqrt(normSquared()); }
double Vector2D::normSquared(void) const { return dot(*this); }

Vector2D Vector2D::normalize(const double& tolerance) const {
	Vector2D v;

	double length = this->norm();
	if (length >= tolerance) {
		v = *this * (float)(1.0 / length);
	}

	return v;
}

Vector2D Vector2D::floor(const int& accuracy) const {
	return Vector2D(
		(float)((int)(this->x_ * pow(10, accuracy)) / pow(10, accuracy)),
		(float)((int)(this->y_ * pow(10, accuracy)) / pow(10, accuracy))
	);
}