#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

#include <iostream>

class Vec2f {
public:
	float m_x, m_y;
	Vec2f(const float& x, const float& y) : m_x(x), m_y(y) {}
	Vec2f() : m_x(0), m_y(0) {}

	float length() { return sqrtf(m_x * m_x + m_y * m_y); }
	void normalize();

	void print() const;

	Vec2f* operator*(const float& scalar) {
		m_x *= scalar; m_y *= scalar;
		return this;
	}
	void operator+(const float& scalar) {
		m_x += scalar; m_y += scalar;
	}
};
