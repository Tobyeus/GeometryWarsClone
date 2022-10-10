#include "Game.h"
#include <stdlib.h>

// Initializing the game
// creating the window
// spawning the player
void Game::init() {
	std::cout << "init starting" << std::endl;
	m_window.create(sf::VideoMode(m_wWidth, m_wLength), "Game Window");
	m_window.setFramerateLimit(60);
	spawnPlayer();
	srand((unsigned int) time(NULL));
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
	Vec2 speed(3 * 1.5 ,3);
	m_player->cShape = std::make_shared<CShape>(20, 10, playerColor, outlineColor, 5, position);
	m_player->cTransform = std::make_shared<CTransform>(position, speed, 0.0f);
	m_player->cInput = std::make_shared<CInput>();
	m_entities.update();
}

// Spawning enemies, similar to the above function
void Game::sEnemySpawner() {
	spawnEnemy();
}

// Main Game loop
void Game::run() {
	std::cout << "Game Loop starting" << std::endl;
	// Initialization
	init();

	// Gameloop
	while (m_running) {

		// Systems
		if (m_currentFrame % 80 == 0) {
			sEnemySpawner();
		}
		// spawnEnemies
		sUserInput();
		sMovement();
		sCollision();
		sRender();
		m_entities.update();
		m_currentFrame++;
	}
	std::cout << "Game Loop closing" << std::endl;
	m_window.close();
}

// Render will draw all active (alive) entites
// Make sure to clear before drawing
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
// TODO: Movement System can prolly completely be rewritten for performance
void Game::sMovement() {

	// Player movement
	// Player Input WASD

	if (m_player->cInput->movementUp) {
		// go up
		m_player->cTransform->position.y -= m_player->cTransform->speed.y;
	}
	if (m_player->cInput->movementDown) {
		// go down
		m_player->cTransform->position.y += m_player->cTransform->speed.y;;
	}
	if (m_player->cInput->movementLeft) {
		// go left
		m_player->cTransform->position.x -= m_player->cTransform->speed.x;
	}
	if (m_player->cInput->movementRight) {
		// go right
		m_player->cTransform->position.x += m_player->cTransform->speed.x;
	}

	// Player Boundaries

	if (m_player->cTransform->position.x <= 0) {
		m_player->cTransform->position.x = 0;
	}
	if (m_player->cTransform->position.x >= m_wWidth) {
		m_player->cTransform->position.x = m_wWidth;
	}
	if (m_player->cTransform->position.y <= 0) {
		m_player->cTransform->position.y = 0;
	}
	if (m_player->cTransform->position.y >= m_wLength) {
		m_player->cTransform->position.y = m_wLength;
	}

	m_player->cShape->shape.setPosition(m_player->cTransform->position.x, m_player->cTransform->position.y);

	// Movement of all entities except player
	// window boundaries are handled
	EntityVector ev = m_entities.getEntities();
	for (auto e : ev) {
		e->cShape->shape.rotate(2.0f);

		if (e->getTag() == "Enemy") {
			if (e->cTransform->position.x <= 0 + e->cShape->shape.getRadius()) {
				e->cTransform->speed.x = -e->cTransform->speed.x;
			}

			if (e->cTransform->position.y <= 0 + e->cShape->shape.getRadius()) {
				e->cTransform->speed.y = -e->cTransform->speed.y;
			}

			if (e->cTransform->position.x >= m_wWidth - e->cShape->shape.getRadius()) {
				e->cTransform->speed.x = -e->cTransform->speed.x;
			}

			if (e->cTransform->position.y >= m_wLength - e->cShape->shape.getRadius()) {
				e->cTransform->speed.y = -e->cTransform->speed.y;
			}
			e->cTransform->position.x += e->cTransform->speed.x;
			e->cTransform->position.y += e->cTransform->speed.y;
			e->cShape->shape.setPosition(e->cTransform->position.x, e->cTransform->position.y);
		}
		if (e->getTag() == "Bullet") {
			if (e->cTransform->position.x <= 0 - e->cShape->shape.getRadius()) {
				e->destroy();
			}

			if (e->cTransform->position.y <= 0 - e->cShape->shape.getRadius()) {
				e->destroy();
			}

			if (e->cTransform->position.x >= m_wWidth + e->cShape->shape.getRadius()) {
				e->destroy();
			}

			if (e->cTransform->position.y >= m_wLength + e->cShape->shape.getRadius()) {
				e->destroy();
			}
			e->cTransform->position.x += e->cTransform->speed.x;
			e->cTransform->position.y += e->cTransform->speed.y;
			e->cShape->shape.setPosition(e->cTransform->position.x, e->cTransform->position.y);
		}
	}
}

// Input from the user is registered here
// Most of the inputs will be send to the cInput component
void Game::sUserInput(){

	sf::Event event;
	while (m_window.pollEvent(event)) {
		// "close requested" event: we close the window
		if (event.type == sf::Event::Closed) {
			m_window.close();
		}

		// Keyboard Inputs
		if (event.type == sf::Event::KeyPressed) {
			switch (event.key.code) {
				// WASD
				case sf::Keyboard::W:
					std::cout << "W pressed" << std::endl;
					m_player->cInput->movementUp = true;
					break;
				case sf::Keyboard::S:
					std::cout << "S pressed" << std::endl;
					m_player->cInput->movementDown = true;
					break;
				case sf::Keyboard::A:
					std::cout << "A pressed" << std::endl;
					m_player->cInput->movementLeft = true;
					break;
				case sf::Keyboard::D:
					std::cout << "D pressed" << std::endl;
					m_player->cInput->movementRight = true;
					break;
				// Add new keys here

				// Close with Escape
				case sf::Keyboard::Escape:
					m_window.close();
					break;
				default: break;
			}
		}
		if (event.type == sf::Event::KeyReleased) {
			switch (event.key.code) {
				case sf::Keyboard::W:
					std::cout << "W released" << std::endl;
					m_player->cInput->movementUp = false;
					break;
				case sf::Keyboard::S:
					std::cout << "S released" << std::endl;
					m_player->cInput->movementDown = false;
					break;
				case sf::Keyboard::A:
					std::cout << "A released" << std::endl;
					m_player->cInput->movementLeft = false;
					break;
				case sf::Keyboard::D:
					std::cout << "D released" << std::endl;
					m_player->cInput->movementRight = false;
					break;
				default: break;
			}
		}

		// Mouse Inputs
		if (event.type == sf::Event::MouseButtonPressed) {
			switch (event.key.code) {
				case sf::Mouse::Button::Left:
					std::cout << "Left Mouse Button pressed" << std::endl;
					spawnBullet();
			}
		}
		if (event.type == sf::Event::MouseButtonReleased) {
			switch (event.key.code) {
				case sf::Mouse::Button::Left:
					std::cout << "Left Mouse Button pressed" << std::endl;
			}
		}
	}
}

void Game::sCollision() {
	auto entities = m_entities.getEntities();
	for (auto e1 : entities) {
		for (auto e2 : entities) {
			float dist = distanceTwoPoints(e1->cTransform->position, e2->cTransform->position);
			float collisiondist = e1->cShape->shape.getRadius() + e2->cShape->shape.getRadius();
			if (dist <= collisiondist) {
				// Bullet hits enemy
				if (e1->getTag() == "Bullet" && e2->getTag() == "Enemy") {
					e2->destroy();
				}
				if (e1->getTag() == "Enemy" && e2->getTag() == "Bullet") {
					e1->destroy();
				}
				// Player hits enemy
				if (e1->getTag() == "Player" && e2->getTag() == "Enemy") {
					e1->destroy();
				}
				if (e1->getTag() == "Enemy" && e2->getTag() == "Player") {
					e2->destroy();
				}
			}
		}
	}
}


	/*	if (e1->getTag() == "Enemy") {
			float dist = distanceTwoPoints(e->cTransform->position, m_player->cTransform->position);
			float collisionDist = (float) (e->cShape->shape.getRadius() + m_player->cShape->shape.getRadius() + 0.2 * m_player->cShape->shape.getRadius());
			if (dist <= collisionDist) {
				e->destroy();
			}
		}
	}
}*/

// Function to spawn a bullet at the position of the player
// Next TODO: Since Origin of the coord system is not in the middle some transformation has to be done.
void Game::spawnBullet() {
	auto bullet = m_entities.addEntity("Bullet");
	sf::Color bulletFill(255, 255, 255);
	Vec2 bulletPos = m_player->cTransform->position;
	Vec2 mousePos(sf::Mouse::getPosition(m_window).x, sf::Mouse::getPosition(m_window).y);
	Vec2 bulletSpeed = ((mousePos - bulletPos) / (mousePos - bulletPos).magnitude()) * 10;
	bullet->cShape = std::make_shared<CShape>(CShape(5, 20, bulletFill, bulletFill, 0.0f, bulletPos));
	bullet->cTransform = std::make_shared<CTransform>(CTransform(bulletPos, bulletSpeed, 0.0f));
}

void Game::spawnEnemy() {
	auto enemy = m_entities.addEntity("Enemy");
	sf::Color enemyColor(random(0,255), random(0, 255), random(0, 255));
	sf::Color outlineColor(random(0, 255), random(0, 255), random(0, 255));
	Vec2 position(random(50,1024 - 50), random(50, 786 - 50));
	Vec2 speed(random(2,6), random(2,6));
	enemy->cShape = std::make_shared<CShape>(random(10,50), random(3,10), enemyColor, outlineColor, 5, position);
	enemy->cTransform = std::make_shared<CTransform>(position, speed, 0.0f);
	enemy->cShape->shape.setPosition(position.x, position.y);
	enemy->cShape->shape.setRotation(0.0f);
}

int Game::random(int min, int max) {
	return min + (rand() % (1 + max - min));
}

float Game::distanceTwoPoints(Vec2& v1, Vec2& v2) {
	return abs(sqrt(((v1.x - v2.x) * (v1.x - v2.x)) + ((v1.y - v2.y) * (v1.y - v2.y))));
}