
#include "Vector3D.hpp"
#include <math.h>

using namespace obj_tools;

Vector3D OBJ_TOOLS_EXPORT obj_tools::operator*(const float& s, const Vector3D& v) {
	return Vector3D(
		s * v.x_,
		s * v.y_,
		s * v.z_
	);
}

Vector3D::Vector3D(void) {
	this->x_ = 0.0f;
	this->y_ = 0.0f;
	this->z_ = 0.0f;
}

Vector3D::Vector3D(const float& x, const float& y, const float& z) {
	this->x_ = x;
	this->y_ = y;
	this->z_ = z;
}

Vector3D::Vector3D(const Vector3D& v) {
	this->x_ = v.x_;
	this->y_ = v.y_;
	this->z_ = v.z_;
}

Vector3D& Vector3D::operator = (const Vector3D& v){
	this->x_ = v.x_;
	this->y_ = v.y_;
	this->z_ = v.z_;

	return *this;
}

Vector3D Vector3D::operator +  (const Vector3D& v) const {
	return Vector3D(
		this->x_ + v.x_,
		this->y_ + v.y_,
		this->z_ + v.z_
	);
}

Vector3D Vector3D::operator -  (const Vector3D& v) const {
	return Vector3D(
		this->x_ - v.x_,
		this->y_ - v.y_,
		this->z_ - v.z_
	);
}

Vector3D Vector3D::operator *  (const float& s) const {
	return Vector3D(
		this->x_ * s,
		this->y_ * s,
		this->z_ * s
	);
}

Vector3D& Vector3D::operator += (const Vector3D& v) {
	this->x_ += v.x_;
	this->y_ += v.y_;
	this->z_ += v.z_;

	return *this;
}

Vector3D& Vector3D::operator -= (const Vector3D& v) {
	this->x_ -= v.x_;
	this->y_ -= v.y_;
	this->z_ -= v.z_;

	return *this;
}

Vector3D& Vector3D::operator *= (const float& s) {
	this->x_ *= s;
	this->y_ *= s;
	this->z_ *= s;

	return *this;
}

bool Vector3D::operator == (const Vector3D& v) const {
	return(
		this->x_ == v.x_ &&
		this->y_ == v.y_ &&
		this->z_ == v.z_
	);
}

double Vector3D::dot(const Vector3D& v) const {
	return (
		this->x_ * (double)v.x_ + 
		this->y_ * (double)v.y_ + 
		this->z_ * (double)v.z_
	);
}

double Vector3D::norm(void) const { return sqrt(normSquared()); }
double Vector3D::normSquared(void) const { return dot(*this); }

Vector3D Vector3D::normalize(const float& tolerance) const {
	Vector3D v;

	double length = this->norm();
	if (length >= tolerance) {
		v = *this * (float)(1.0 / length);
	}

	return v;
}

Vector3D Vector3D::cross(const Vector3D& v) const {
	return Vector3D(
		this->y_ * v.z_ - v.y_ * this->z_,
		this->z_ * v.x_ - v.z_ * this->x_,
		this->x_ * v.y_ - v.x_ * this->y_
	);
}

Vector3D Vector3D::floor(const int& accuracy) const {
	return Vector3D(
		(float)((int)(this->x_ * pow(10, accuracy)) / pow(10, accuracy)),
		(float)((int)(this->y_ * pow(10, accuracy)) / pow(10, accuracy)),
		(float)((int)(this->z_ * pow(10, accuracy)) / pow(10, accuracy))
	);
}