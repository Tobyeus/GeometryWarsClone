#include "EntityManager.h"

std::shared_ptr<Entity> EntityManager::addEntity(const std::string& tag) {
	auto e = std::shared_ptr<Entity>(new Entity(tag, m_totalEntities++));
	m_entitesToAdd.push_back(e);
	return e;
}

void EntityManager::update() {
	// newly create entities are added into the vector and map
	for (auto e: m_entitesToAdd) {
		m_entities.push_back(e);
		m_entityMap[e->getTag()].push_back(e);
	}

	// remove dead entities from m_entities (entity vector)
	removeDeadEntities(m_entities);

	for (auto& [tag, eVec] : m_entityMap) {
		// alive status is false
		if (eVec.data()->get()->getStatus() == false) {
			removeDeadEntities(eVec);
		}
	}

	m_entitesToAdd.clear();
}

void EntityManager::removeDeadEntities(EntityVector& eVec){

	EntityVector::iterator it = eVec.begin();
	while (it != eVec.end()) {
		// alive status is false, erase from Vec
		if (it->get()->getStatus() == false) {
			it = eVec.erase(it);
		}
		// alive status is true, increment iterator
		else {
			++it;
		}
	}
}

EntityVector& EntityManager::getEntities() { return m_entities; }