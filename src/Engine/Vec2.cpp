#include "Vec2.h"
#include <iostream>

void Vec2::print() {
	std::cout << x << " " << y << std::endl;
}

float Vec2::magnitude(Vec2 v) {
	return sqrt((v.x * v.x) + (v.y * v.y));
}

Vec2 Vec2::operator+(const Vec2& rhs) const {
	return Vec2(x + rhs.x, y + rhs.y);
}

Vec2 Vec2::operator-(const Vec2& rhs) const {
	return Vec2(x - rhs.x, y - rhs.y);
}

Vec2 Vec2::operator*(const float num) const {
	return Vec2(x * num, y * num);
}

Vec2 Vec2::operator/(const float num) const {
	return Vec2(x / num, y / num);
}

void Vec2::operator+=(const Vec2& rhs) {
	x += rhs.x;
	y += rhs.y;
}