#pragma once
#include "EntityManager.h"
#include <stdlib.h>
#include "SFML/Graphics.hpp"
#include "Action.h"

class Scene{
public:
	EntityManager m_entities;
	//GameEngine engine;
	int m_currentFrame = 0;
	std::map<int, std::string> m_actionMap;
	bool m_pause = false;
	bool m_hadEnded = false;
	sf::RenderWindow* m_window;

	Scene(sf::RenderWindow* window) : m_window(window) {};

	virtual void update() = 0;
	virtual void sDoAction(Action& action) = 0;
	virtual void sMouseInput(sf::Event& event) = 0;
	virtual void sRender() = 0;

	void simulate(int number);
	void doAction(Action action);
	void mouseInput(sf::Event& event);
	void registerAction(int keyCode, std::string actionName);
};

class Scene_Play : public Scene {
	//std::string levelPath;
	std::shared_ptr<Entity> m_player;
	//PlayerConfig playerConfig

public:
	void init();
	void update();

	Scene_Play(sf::RenderWindow* window) : Scene(window) { init(); };

	// Systems
	void sAnimation();
	void sMovement();
	void sEnemySpawner();
	void sCollision();
	void sRender();
	void sMouseInput(sf::Event& event);
	void sDoAction(Action& action);
	void sDebug();
	void sSpawnBullet();

	// Helper Functions
	void spawnPlayer();
	int hRandom(int min, int max);
	float hDistanceTwoPoints(Vec2& v1, Vec2& v2);
};

class Scene_Menu : Scene {
	std::vector<std::string> menuStrings;
	sf::Text menuText;
	std::vector<std::string> levelPaths;
	int menuIndex;

	void init();

	// Systems
	void sRender();
	void sDoAction(Action action);

public:
	void update();
};