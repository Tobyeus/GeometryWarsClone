#pragma once

#include <SFML/Graphics.hpp>
#include "EntityManager.h"
#include "Entity.h"

class Game {
	sf::RenderWindow m_window;
	EntityManager m_entities;
	std::shared_ptr<Entity> m_player;
	bool m_pause = false;
	bool m_running = true;
public:
	void run();
private:
	void init();
	void setPause();
	// Systems
	void sMovement();
	void sUserInput();
	void sRender();
	void sEnemySpawner();
	void sCollision();

	// Helper Functions
	void spawnPlayer();
};