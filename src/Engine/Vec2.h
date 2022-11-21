#pragma once

class Vec2 {
public:
	float x = 0;
	float y = 0;

	Vec2() = default;
	Vec2(float xin, float yin): x(xin), y(yin) {};
	Vec2(int xin, int yin) : x(xin), y(yin) {};

	void print();
	float static magnitude(Vec2 v);

	Vec2 operator+(const Vec2& rhs) const;
	Vec2 operator-(const Vec2& rhs) const;

	Vec2 operator*(const float num) const;
	Vec2 operator/(const float num) const;

	void operator+=(const Vec2& rhs);
};