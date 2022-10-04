#include "EntityManager.h"

std::shared_ptr<Entity> EntityManager::addEntity(const std::string& tag) {
	auto e = std::make_shared<Entity>(Entity(tag, m_totalEntities++));
	m_toAdd.push_back(e);
	return e;
}

void EntityManager::update() {
	// Pushing new Elements
	for (auto e: m_toAdd) {
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

	m_toAdd.clear();
}

EntityVector& EntityManager::getEntities() { return m_entities; }