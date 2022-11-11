#pragma once

#include "Vec2.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

// Components for the Entities are defined here
// Components are basically pure data stored for the entities
// They give functionality to the Entities i.e. shape, Transform, Collision
// the functionality is handled in other helper or system functions


// Shapes handles the drawn object
// points has direct influence in the appearence
// 3 points -> triangle, 4 points -> square, 5 points -> pentagon...
// SetOrigin will set the position to the mid point of the circle
class CShape {
public:
	sf::CircleShape shape;

	CShape(float radius, size_t points, const sf::Color& fill, sf::Color& outline, float thickness, Vec2 position)
		: shape(radius, points) {
		shape.setFillColor(fill);
		shape.setOutlineColor(outline);
		shape.setOutlineThickness(thickness);
		shape.setOrigin(radius, radius);
		shape.setPosition(position.x, position.y);
		shape.setRotation(0.0f);
	}
};

// Transform holds the position and speed vector, angle describes the orientation
class CTransform {
public:
	Vec2 position = { 0.0f, 0.0f };
	Vec2 speed = { 0.0f, 0.0f };
	float angle = 0.0f;

	CTransform(Vec2& posIn, Vec2& speedIn, float angleIn) : position(posIn), speed(speedIn), angle(angleIn) {};
};

class CScore {
public:
	int score = 0;
};

class CCollision {
public:
	float radius;
};

class CInput {
public:
	bool movementUp = false;
	bool movementDown = false;
	bool movementRight = false;
	bool movementLeft = false;

	bool mouseLeft = false;
	bool mouseRight = false;
};

class CSpawnProjectile {
public:
	bool shoot = false;
	Vec2 mousePos;
};