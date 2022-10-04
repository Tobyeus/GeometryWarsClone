#include "Game.h"

// Initializing the game
// creating the window
// spawning the player
void Game::init() {
	std::cout << "init starting" << std::endl;
	m_window.create(sf::VideoMode(1024, 768), "Game Window");
	m_window.setFramerateLimit(60);
	spawnPlayer();
	sEnemySpawner();
	std::cout << "init done" << std::endl;
}

// Spawning the player
// create and add entity
// set a shape, color, position and orientation
void Game::spawnPlayer() {
	m_player = m_entities.addEntity("Player");
	sf::Color playerColor(0, 0, 0);
	sf::Color outlineColor(255, 255, 255);
	Vec2 position(512.0f, 384.0f);
	Vec2 speed(2,3);
	m_player->cShape = std::make_shared<CShape>(20, 10, playerColor, outlineColor, 5);
	m_player->cTransform = std::make_shared<CTransform>(position, speed, 0.0f);
	m_player->cShape->shape.setPosition(position.x, position.y);
	m_player->cShape->shape.setRotation(0.0f);
	m_entities.update();
}

// Spawning enemies, similar to the above function
void Game::sEnemySpawner() {
	auto enemy = m_entities.addEntity("Enemy");
	sf::Color enemyColor(255, 255, 255);
	sf::Color outlineColor(177, 23, 131);
	Vec2 position(512.0f, 100.0f);
	Vec2 speed(-1.0f, 0.0f);
	enemy->cShape = std::make_shared<CShape>(20, 5, enemyColor, outlineColor, 2);
	enemy->cTransform = std::make_shared<CTransform>(position, speed, 0.0f);
	enemy->cShape->shape.setPosition(position.x,position.y);
	enemy->cShape->shape.setRotation(0.0f);
	m_entities.update();
}

// Main Game loop
void Game::run() {
	std::cout << "Game Loop starting" << std::endl;
	// Initialization
	init();

	// Gameloop
	while (m_running) {

		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (m_window.pollEvent(event)) {
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed) {
				std::cout << "Pressed Close" << std::endl;
				m_window.close();
			}
		}
		// Systems
		// spawnEnemies
		// Collision
		sMovement();
		sRender();
	}
	std::cout << "Game Loop closing" << std::endl;
	m_window.close();
}

// Render will draw all active (alive) entites
void Game::sRender() {
	m_window.clear();

	EntityVector ev = m_entities.getEntities();
	for (auto e: ev) {
	m_window.draw(e->cShape->shape);
	}

	m_window.display();
}

// Position is handling the position in regards to the speed
// rotation of objects is also controlled here
void Game::sMovement() {
	m_player->cTransform->calculateMovement();
	Vec2 position(m_player->cTransform->position);
	m_player->cShape->shape.setPosition(position.x, position.y);
	EntityVector ev = m_entities.getEntities();
	for (auto e : ev) {
		if (e->cTransform->position.x <= 0 + e->cShape->shape.getRadius()) {
			e->cTransform->speed.x = -e->cTransform->speed.x;
		}

		if (e->cTransform->position.y <= 0 + e->cShape->shape.getRadius()) {
			e->cTransform->speed.y = -e->cTransform->speed.y;
		}

		if (e->cTransform->position.x >= 1024 - e->cShape->shape.getRadius()) {
			e->cTransform->speed.x = -e->cTransform->speed.x;
		}

		if (e->cTransform->position.y >= 768 - e->cShape->shape.getRadius()) {
			e->cTransform->speed.y = -e->cTransform->speed.y;
		}

		e->cTransform->calculateMovement();
		Vec2 position(e->cTransform->position);
		e->cShape->shape.setPosition(position.x, position.y);
		e->cShape->shape.rotate(1.0f);
	}
}