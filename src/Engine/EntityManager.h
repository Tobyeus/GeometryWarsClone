#pragma once

#include "Entity.h"

typedef std::vector<std::shared_ptr<Entity>> EntityVector;
typedef std::map<std::string, EntityVector> EntityMap;

class EntityManager {
	EntityVector m_entities;
	EntityVector m_entitesToAdd;
	EntityMap m_entityMap;
	size_t m_totalEntities = 0;
private:
	void init();
public:
	EntityManager(){};
	~EntityManager(){};
	void update();
	void removeDeadEntities(EntityVector& eVec);
	std::shared_ptr<Entity> addEntity(std::shared_ptr<Entity>& e);
	std::shared_ptr<Entity> addEntity(const std::string& string);
	EntityVector& getEntities();
	EntityVector& getEntities(const std::string& tag);
};