#include "Vec2f.h"

void Vec2f::print() const {
	std::cout << "[" << m_x << ", " << m_y << "]" << std::endl;
}

void Vec2f::normalize() {
	float l = length();
	m_x /= l;
	m_y /= l;
}