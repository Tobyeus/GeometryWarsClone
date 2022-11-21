#include "Scene_Play.h"
#include "ImGui.h"
#include "imgui-SFML.h"

void Scene_Play::init() {

	// Reset entity manager
	m_entities = EntityManager();
	spawnPlayer();
	sEnemySpawner();
	sEnemySpawner();
	sEnemySpawner();
	// register Actions
	registerAction(sf::Keyboard::W, "UP");
	registerAction(sf::Keyboard::S, "DOWN");
	registerAction(sf::Keyboard::A, "LEFT");
	registerAction(sf::Keyboard::D, "RIGHT");
	registerAction(sf::Keyboard::P, "PAUSE");
	registerAction(sf::Keyboard::Escape, "QUIT");
	// Set Font
	if (!m_font.loadFromFile(".\\assets\\fonts\\arial.ttf")) {
		std::cout << "Loading Font didnt work!" << std::endl;
	}
	// Text overlay
	m_font.loadFromFile(".\\assets\\fonts\\arial.ttf");
	m_scoreText.setFont(m_font);
	m_scoreText.setPosition(5,740);
	m_scoreText.setCharacterSize(24);
	m_livesText.setFont(m_font);
	m_livesText.setCharacterSize(24);
	m_livesText.setPosition(5, 716);
}

void Scene_Play::update() {

	if (m_currentFrame % 90 == 0 && m_currentFrame >= 120) {
		sEnemySpawner();
	}
	sMovement();
	sCollision();
	m_entities.update();
	sDebug();
	sRender();
	m_currentFrame++;
	m_player->cProjectile->shoot = false;
}

void Scene_Play::sGameOver() {
	sf::Text gameOver;
	gameOver.setFont(m_font);
	gameOver.setOrigin(60, 100);
	gameOver.setString("You died :(");
	gameOver.setPosition(512, 384);
	gameOver.setCharacterSize(30);
	m_window->draw(gameOver);
}

void Scene_Play::spawnPlayer() {
	m_player = m_entities.addEntity("Player");
	sf::Color playerColor(0, 0, 0);
	sf::Color outlineColor(255, 255, 255);
	Vec2 position(512.0f, 384.0f);
	Vec2 speed(4.5f, 3.0f);
	m_player->cShape = std::make_shared<CShape>(20, 10, playerColor, outlineColor, 5, position);
	m_player->cTransform = std::make_shared<CTransform>(position, speed, 0.0f);
	m_player->cInput = std::make_shared<CInput>();
	m_player->cScore = std::make_shared<CScore>();
	m_player->cProjectile = std::make_shared<CSpawnProjectile>();
	m_player->cCollision = std::make_shared<CCollision>(m_player->cShape->shape.getRadius(), position);
	m_player->cLives = std::make_shared<CLives>(3.0f);
	m_player->cRespawn = std::make_shared<CRespawn>();
}

void Scene_Play::sDoAction(Action& action) {
	if (action.getType() == "PRESS") {
		// Movement
		if (action.getName() == "UP") { m_player->cInput->movementUp = true; }
		if (action.getName() == "DOWN") { m_player->cInput->movementDown = true; }
		if (action.getName() == "LEFT") { m_player->cInput->movementLeft = true; }
		if (action.getName() == "RIGHT") { m_player->cInput->movementRight = true; }

		if (action.getName() == "PAUSE") { m_pause = !m_pause; }
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
		if (event.mouseButton.button == sf::Mouse::Button::Left) { m_player->cProjectile->shoot = true; }
	}
}

void Scene_Play::sEnemySpawner() {
	auto enemy = m_entities.addEntity("Enemy");
	sf::Color enemyColor(hRandom(0, 255), hRandom(0, 255), hRandom(0, 255));
	sf::Color outlineColor(hRandom(0, 255), hRandom(0, 255), hRandom(0, 255));
	Vec2 position(hRandom(50, 1024 - 50), hRandom(50, 786 - 50));
	Vec2 speed(hRandom(-6, 6), hRandom(-6, 6));
	enemy->cShape = std::make_shared<CShape>(hRandom(10, 50), hRandom(3, 10), enemyColor, outlineColor, 5, position);
	enemy->cTransform = std::make_shared<CTransform>(position, speed, 0.0f);
	enemy->cShape->shape.setPosition(position.x, position.y);
	enemy->cShape->shape.setRotation(0.0f);
	enemy->cCollision = std::make_shared<CCollision>(enemy->cShape->shape.getRadius(),enemy->cTransform->position);
}

void Scene_Play::sRender() {
	m_window->clear(sf::Color::Black);
	EntityVector ev = m_entities.getEntities();
	for (auto e : ev) {
		if (hitboxActive) {
			m_window->draw(e->cCollision->hitbox);
		}
		m_window->draw(e->cShape->shape);
	}
	m_scoreText.setString("Score " + std::to_string(m_player->cScore->score));
	m_livesText.setString("Lives: " + std::to_string(m_player->cLives->lives));
	m_window->draw(m_scoreText);
	m_window->draw(m_livesText);
	if (m_hadEnded) {
		sGameOver();
	}
	ImGui::SFML::Render(*m_window);
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

	// Player shooting bullet
	if (m_player->cProjectile->shoot && m_player->getStatus()) {
		sSpawnBullet();
	}

	// Respawn Player
	if (m_currentFrame == m_player->cRespawn->respawnFrame) {
		m_entities.addEntity(m_player);
		m_player->setAlive();
		m_player->cTransform->position = Vec2{ 512.0f, 384.0f };
	}

	m_player->cShape->shape.setPosition(m_player->cTransform->position.x, m_player->cTransform->position.y);
	m_player->cCollision->hitbox.setPosition(m_player->cTransform->position.x, m_player->cTransform->position.y);

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
			e->cCollision->hitbox.setPosition(e->cTransform->position.x, e->cTransform->position.y);
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
			e->cCollision->hitbox.setPosition(e->cTransform->position.x, e->cTransform->position.y);
			e->cLifespan->time--;
			if (e->cLifespan->time <= 0) {
				e->destroy();
			}
		}
	}
}

// Collision System
void Scene_Play::sCollision() {
	auto entities = m_entities.getEntities();
	for (auto e1 : entities) {
		if (e1->cCollision == NULL) {
			continue;
		}
		for (auto e2 : entities) {
			float dist = hDistanceTwoPoints(e1->cTransform->position, e2->cTransform->position);
			float collisiondist = e1->cCollision->hitbox.getRadius() + e2->cCollision->hitbox.getRadius();
			if (dist <= collisiondist) {
				// Bullet hits enemy
				if (e1->getTag() == "Bullet" && e2->getTag() == "Enemy") {
					m_player->cScore->score += (int) e2->cShape->shape.getRadius();
					e2->destroy();
				}
				// Player hits enemy
				if (e1->getTag() == "Player" && e2->getTag() == "Enemy") {
					e1->cLives->lives--;
					if (e1->cLives->lives > 0) {
						e1->cRespawn->respawnFrame = m_currentFrame + 120;
					}

					if (e1->cLives->lives == 0) {
						m_hadEnded = true;
						break;
					}

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
	Vec2 bulletSpeed = ((m_player->cProjectile->mousePos - m_player->cTransform->position) / Vec2::magnitude(m_player->cProjectile->mousePos - m_player->cTransform->position)) * 10;
	bullet->cTransform = std::make_shared<CTransform>(CTransform(m_player->cTransform->position, bulletSpeed, 0.0f));
	bullet->cShape = std::make_shared<CShape>(CShape(5, 20, bulletFill, bulletFill, 0.0f, m_player->cTransform->position));
	bullet->cCollision = std::make_shared<CCollision>(bullet->cShape->shape.getRadius(), m_player->cTransform->position);
	bullet->cLifespan = std::make_shared<CLifespan>(40); // 40 frames
	m_player->cProjectile->shoot = false;
}

void Scene_Play::sDebug() {
	// What to debug:
	// show hitbox
	// show list of entities
	ImGui::Begin("Debug", 0);
	ImGui::SetWindowPos(ImVec2(0, 0));
	ImGui::SetWindowSize(ImVec2(150, 200));
	ImGui::Checkbox("Show hitbox", &hitboxActive);
	ImGui::Separator();
	ImGui::Text("Lives: %i", m_player->cLives->lives);
	ImGui::Separator();
	ImGui::Text("Score: %i", m_player->cScore->score);
	ImGui::Separator();
	ImGui::Text("Entities:");
	for (auto entity : m_entities.getEntities()) {
		std::string eName = entity->getTag();
		ImGui::Text(eName.c_str());
	}
	ImGui::End();
}
	 
// Helper Functions

int Scene_Play::hRandom(int min, int max) {
	return min + (rand() % (1 + max - min));
}

float Scene_Play::hDistanceTwoPoints(Vec2& v1, Vec2& v2) {
	return abs(sqrt(((v1.x - v2.x) * (v1.x - v2.x)) + ((v1.y - v2.y) * (v1.y - v2.y))));
}