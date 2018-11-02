#include "Vec2f.h"

void Vec2f::print() const {
	std::cout << "[" << mx << ", " << my << "]" << std::endl;
}

void Vec2f::normalize() {
	float l = length();
	mx /= l;
	my /= l;
}