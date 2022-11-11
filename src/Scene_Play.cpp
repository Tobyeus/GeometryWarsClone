#include "Scene.h"

void Scene_Play::init() {

	// Reset entity manager
	m_entities = EntityManager();
	spawnPlayer();
	// register Actions
	registerAction(sf::Keyboard::W, "UP");
	registerAction(sf::Keyboard::S, "DOWN");
	registerAction(sf::Keyboard::A, "LEFT");
	registerAction(sf::Keyboard::D, "RIGHT");
	registerAction(sf::Keyboard::P, "PAUSE");
	registerAction(sf::Keyboard::Escape, "QUIT");

	// load level -> when level system is done
}

void Scene_Play::update() {
	if (m_currentFrame % 90 == 0 && m_currentFrame >= 120) {
		sEnemySpawner();
	}
	sRender();
	sMovement();
	sCollision();
	if (m_player->cProjectile->shoot) {
		sSpawnBullet();
	}
	m_entities.update();
	m_currentFrame++;
	m_player->cProjectile->shoot = false;
}

void Scene_Play::spawnPlayer() {
	m_player = m_entities.addEntity("Player");
	sf::Color playerColor(0, 0, 0);
	sf::Color outlineColor(255, 255, 255);
	Vec2 position(512.0f, 384.0f);
	Vec2 speed(3 * 1.5, 3);
	m_player->cShape = std::make_shared<CShape>(20, 10, playerColor, outlineColor, 5, position);
	m_player->cTransform = std::make_shared<CTransform>(position, speed, 0.0f);
	m_player->cInput = std::make_shared<CInput>();
	m_player->cScore = std::make_shared<CScore>();
	m_player->cProjectile = std::make_shared<CSpawnProjectile>();
}

void Scene_Play::sDoAction(Action& action) {
	if (action.getType() == "PRESS") {
		// Movement
		if (action.getName() == "UP") { m_player->cInput->movementUp = true; }
		if (action.getName() == "DOWN") { m_player->cInput->movementDown = true; }
		if (action.getName() == "LEFT") { m_player->cInput->movementLeft = true; }
		if (action.getName() == "RIGHT") { m_player->cInput->movementRight = true; }

		//if (action.getName() == "PAUSE") { m_pause = m_pause ? false : true; }
		if (action.getName() == "QUIT") { m_hadEnded = true; }
	}

	if (action.getType() == "RELEASE") {
		// Movement
		if (action.getName() == "UP") { m_player->cInput->movementUp = false; }
		if (action.getName() == "DOWN") { m_player->cInput->movementDown = false; }
		if (action.getName() == "LEFT") { m_player->cInput->movementLeft = false; }
		if (action.getName() == "RIGHT") { m_player->cInput->movementRight = false; }
	}
}

void Scene_Play::sMouseInput(sf::Event& event) {
	m_player->cProjectile->mousePos = Vec2(event.mouseButton.x, event.mouseButton.y);
	if (event.type == sf::Event::MouseButtonPressed) {
		if (event.mouseButton.button == sf::Mouse::Button::Left) { m_player->cProjectile->shoot = true; }
	}
	if (event.type == sf::Event::MouseButtonReleased) {
		if (event.mouseButton.button == sf::Mouse::Button::Left) { m_player->cProjectile->shoot = false; }
	}
}

void Scene_Play::sEnemySpawner() {
	auto enemy = m_entities.addEntity("Enemy");
	sf::Color enemyColor(hRandom(0, 255), hRandom(0, 255), hRandom(0, 255));
	sf::Color outlineColor(hRandom(0, 255), hRandom(0, 255), hRandom(0, 255));
	Vec2 position(hRandom(50, 1024 - 50), hRandom(50, 786 - 50));
	Vec2 speed(hRandom(2, 6), hRandom(2, 6));
	enemy->cShape = std::make_shared<CShape>(hRandom(10, 50), hRandom(3, 10), enemyColor, outlineColor, 5, position);
	enemy->cTransform = std::make_shared<CTransform>(position, speed, 0.0f);
	enemy->cShape->shape.setPosition(position.x, position.y);
	enemy->cShape->shape.setRotation(0.0f);
}

void Scene_Play::sRender() {
	m_window->clear();
	//window.draw(hud); // Later for Text 
	EntityVector ev = m_entities.getEntities();
	for (auto e : ev) {
		m_window->draw(e->cShape->shape);
	}
	m_window->display();
}

// Movement System
// TODO: Movement System can prolly completely be rewritten for performance
void Scene_Play::sMovement() {

	// Player movement
	if (m_player->cInput->movementUp) {
		m_player->cTransform->position.y -= m_player->cTransform->speed.y;
	}
	if (m_player->cInput->movementDown) {
		m_player->cTransform->position.y += m_player->cTransform->speed.y;;
	}
	if (m_player->cInput->movementLeft) {
		m_player->cTransform->position.x -= m_player->cTransform->speed.x;
	}
	if (m_player->cInput->movementRight) {
		m_player->cTransform->position.x += m_player->cTransform->speed.x;
	}

	// Player Boundaries
	if (m_player->cTransform->position.x <= 0) {
		m_player->cTransform->position.x = 0;
	}
	if (m_player->cTransform->position.x >= 1024) {
		m_player->cTransform->position.x = 1024;
	}
	if (m_player->cTransform->position.y <= 0) {
		m_player->cTransform->position.y = 0;
	}
	if (m_player->cTransform->position.y >= 768) {
		m_player->cTransform->position.y = 768;
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

			if (e->cTransform->position.x >= 1024 - e->cShape->shape.getRadius()) {
				e->cTransform->speed.x = -e->cTransform->speed.x;
			}

			if (e->cTransform->position.y >= 768 - e->cShape->shape.getRadius()) {
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

			if (e->cTransform->position.x >= 1024 + e->cShape->shape.getRadius()) {
				e->destroy();
			}

			if (e->cTransform->position.y >= 768 + e->cShape->shape.getRadius()) {
				e->destroy();
			}
			e->cTransform->position.x += e->cTransform->speed.x;
			e->cTransform->position.y += e->cTransform->speed.y;
			e->cShape->shape.setPosition(e->cTransform->position.x, e->cTransform->position.y);
		}
	}
}

// Collision System
void Scene_Play::sCollision() {
	auto entities = m_entities.getEntities();
	for (auto e1 : entities) {
		for (auto e2 : entities) {
			float dist = hDistanceTwoPoints(e1->cTransform->position, e2->cTransform->position);
			float collisiondist = e1->cShape->shape.getRadius() + e2->cShape->shape.getRadius();
			if (dist <= collisiondist) {
				// Bullet hits enemy
				if (e1->getTag() == "Bullet" && e2->getTag() == "Enemy") {
					m_player->cScore->score += (int) e2->cShape->shape.getRadius();
					e2->destroy();
				}
				// Player hits enemy
				if (e1->getTag() == "Player" && e2->getTag() == "Enemy") {
					e1->destroy();
				}
			}
		}
	}
}

// Spawn projectile
void Scene_Play::sSpawnBullet() {
	auto bullet = m_entities.addEntity("Bullet");
	sf::Color bulletFill(255, 255, 255);
	Vec2 bulletSpeed = ((m_player->cProjectile->mousePos - m_player->cTransform->position) / (m_player->cProjectile->mousePos - m_player->cTransform->position).magnitude()) * 10;
	bullet->cTransform = std::make_shared<CTransform>(CTransform(m_player->cTransform->position, bulletSpeed, 0.0f));
	bullet->cShape = std::make_shared<CShape>(CShape(5, 20, bulletFill, bulletFill, 0.0f, m_player->cTransform->position));
	m_player->cProjectile->shoot = false;
}
	 
// Helper Functions

int Scene_Play::hRandom(int min, int max) {
	return min + (rand() % (1 + max - min));
}

float Scene_Play::hDistanceTwoPoints(Vec2& v1, Vec2& v2) {
	return abs(sqrt(((v1.x - v2.x) * (v1.x - v2.x)) + ((v1.y - v2.y) * (v1.y - v2.y))));
}