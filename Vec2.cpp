#include "Vec2.h"
#include <iostream>

void Vec2::print() {
	std::cout << x << " " << y << std::endl;
}

Vec2 Vec2::operator+(const Vec2& rhs) const {
	return Vec2(x + rhs.x, y + rhs.y);
}

void Vec2::operator+=(const Vec2& rhs) {
	x += rhs.x;
	y += rhs.y;
}