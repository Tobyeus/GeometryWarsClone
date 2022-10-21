#pragma once

#include <SFML/Graphics.hpp>
#include "EntityManager.h"
#include "Entity.h"

class Game {
	sf::RenderWindow m_window;
	int m_wWidth = 1024;
	int m_wLength = 768;
	EntityManager m_entities;
	std::shared_ptr<Entity> m_player;
	bool m_pause = false;
	bool m_running = true;
	int m_currentFrame = 0;
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
	void respawnPlayer();
	void spawnEnemy();
	void spawnBullet(std::shared_ptr<Entity>& entity, Vec2 mousePos);
	// Functions, abstract later
	int random(int min, int max);
	float distanceTwoPoints(Vec2& v1, Vec2& v2);
};