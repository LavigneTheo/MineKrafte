#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

#include <iostream>

class Vec2f {
public:
	float mx, my;
	Vec2f(const float& x, const float& y) : mx(x), my(y) {}
	Vec2f() : mx(0), my(0) {}

	float length() { return sqrtf(mx * mx + my * my); }
	void normalize();

	void print() const;

	Vec2f* operator*(const float& scalar) {
		mx *= scalar; my *= scalar;
		return this;
	}
	void operator+(const float& scalar) {
		mx += scalar; my += scalar;
	}
};
