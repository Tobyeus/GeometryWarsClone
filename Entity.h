#pragma once

#include <iostream>
#include "Components.h"

class Entity {
	friend class EntityManager;

	const size_t m_id = 0;
	const std::string m_tag	= "Default";
	bool m_active = true;

	// Constructor
	Entity(const std::string& tag, size_t id) : m_id(id), m_tag(tag) {};

public:
	// Components
	std::shared_ptr<CTransform> cTransform;
	std::shared_ptr<CShape> cShape;
	std::shared_ptr<CCollision> cCollision;
	std::shared_ptr<CInput> cInput;
	std::shared_ptr<CScore> cScore;
	std::shared_ptr<CLives> cLives;
	//CLifespan* cLifespan;

	size_t getId() { return m_id; };
	std::string getTag() const { return m_tag; };
	bool getStatus() { return m_active; };
	void destroy() { m_active = false; };
};