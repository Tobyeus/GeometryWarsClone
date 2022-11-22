#pragma once
#include "EntityManager.h"
#include <iostream>
#include "Action.h"

class Scene{
public:
	EntityManager m_entities;
	//GameEngine engine;
	int m_currentFrame = 0;
	std::map<int, std::string> m_actionMap;
	bool m_pause = false;
	bool m_hadEnded = false;
	bool m_restart = false;
	sf::RenderWindow* m_window;
	bool hitboxActive = false;

	Scene(sf::RenderWindow* window) : m_window(window) {};

	virtual void update() = 0;
	virtual void sDoAction(Action& action) = 0;
	virtual void sMouseInput(sf::Event& event) = 0;
	virtual void sRender() = 0;
	virtual void sDebug() = 0;

	void debug();
	void simulate(int number);
	void doAction(Action action);
	void mouseInput(sf::Event& event);
	void registerAction(int keyCode, std::string actionName);
};