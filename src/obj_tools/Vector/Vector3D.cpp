
#include "Vector3D.hpp"
#include <math.h>

using namespace obj_tools;

Vector3D obj_tools::operator*(const float& s, const Vector3D& v) {
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

Vector3D Vector3D::operator +  (const Vector3D& v) {
	return Vector3D(
		this->x_ + v.x_,
		this->y_ + v.y_,
		this->z_ + v.z_
	);
}

Vector3D Vector3D::operator -  (const Vector3D& v) {
	return Vector3D(
		this->x_ - v.x_,
		this->y_ - v.y_,
		this->z_ - v.z_
	);
}

Vector3D Vector3D::operator *  (const float& s) {
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

double Vector3D::dot(const Vector3D& v) {
	return (
		this->x_ * (double)v.x_ + 
		this->y_ * (double)v.y_ + 
		this->z_ * (double)v.z_
	);
}

double Vector3D::norm(void) { return sqrt(normSquared()); }
double Vector3D::normSquared(void) { return dot(*this); }

Vector3D Vector3D::normalize(const float& tolerance) {
	Vector3D v;

	double length = this->norm();
	if (length >= tolerance) {
		v = *this * (1 / length);
	}

	return v;
}

Vector3D Vector3D::cross(const Vector3D& v){
	return Vector3D(
		this->y_ * v.z_ - v.z_ * this->y_,
		this->z_ * v.x_ - v.x_ * this->z_,
		this->x_ * v.y_ - v.y_ * this->x_
	);
}