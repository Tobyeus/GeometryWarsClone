#include "Scene.h"

void Scene::registerAction(int keyCode, std::string actionName) {
	m_actionMap.insert(std::make_pair(keyCode, actionName));
}

void Scene::doAction(Action action) {
	sDoAction(action);
}

void Scene::mouseInput(sf::Event& event) {
	sMouseInput(event);
}