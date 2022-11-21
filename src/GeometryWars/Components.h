#pragma once
#include "../Engine/Vec2.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

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

	// Parameters:
	// radius -> radius of the cirlce
	// points -> points of the shape, take atleast 3 to get a triangle
	// fill -> color inside the shape
	// outline -> color of the border
	// thickness -> size of the border
	// position -> position of the shape
	CShape(float radius, size_t points, const sf::Color& fill, sf::Color& outline, float thickness, Vec2 position) : shape(radius, points) {
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

	// posIn -> initial position
	// speed -> initial speed
	// angleIn -> initial angle
	CTransform(Vec2& posIn, Vec2& speedIn, float angleIn) : position(posIn), speed(speedIn), angle(angleIn) {};
};

class CScore {
public:
	int score = 0;
};

// Collision works with the radius of the shapes
class CCollision {
	float m_parameter = 1.1;
public:
	sf::CircleShape hitbox;
	CCollision(float radius, Vec2 position) : hitbox(radius * m_parameter, 20) {
		hitbox.setOrigin(radius * m_parameter, radius * m_parameter);
		hitbox.setOutlineThickness(1.0f);
		hitbox.setOutlineColor(sf::Color::White);
		hitbox.setPosition(position.x, position.y);
		hitbox.setFillColor(sf::Color(0,0,0,0));
	};
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

class CRespawn {
public:
	int respawnFrame = -1;
	int invincibleTime = 60;
};

class CLives {
public:
	int lives;
	CLives(int lives) : lives(lives) {};
};

class CLifespan {
public:
	int time;
	CLifespan(int lifespan) : time(lifespan) {};
};