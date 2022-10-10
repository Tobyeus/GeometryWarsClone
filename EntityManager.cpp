#include "EntityManager.h"

std::shared_ptr<Entity> EntityManager::addEntity(const std::string& tag) {
	auto e = std::shared_ptr<Entity>(new Entity(tag, m_totalEntities++));
	m_EntitesToAdd.push_back(e);
	return e;
}

void EntityManager::update() {
	// Pushing new Elements
	for (auto e: m_EntitesToAdd) {
		m_entities.push_back(e);
		m_entityMap[e->getTag()].push_back(e);
	}

	{
		auto it = m_entities.begin();

		while (it != m_entities.end()) {
			//std::cout << "Vector: " << it->get()->getTag() << std::endl;
			if (!it->get()->getStatus()) {
				//std::cout << "Vector Erase: " << it->get()->getTag() << std::endl;
				it = m_entities.erase(it);
			}
			else {
				++it;
			}
		}
	}

	{
		auto it = m_entityMap.begin();

		while (it != m_entityMap.end()) {
			//std::cout << "Map: " << it->second.data()->get()->getTag() << std::endl;
			if (!it->second.data()->get()->getStatus()) {
				//std::cout << "Map Erase: " << it->first << std::endl;
				it = m_entityMap.erase(it);
			}
			else {
				++it;
			}
		}
	}

	m_EntitesToAdd.clear();
}

EntityVector& EntityManager::getEntities() { return m_entities; }