#pragma once
#include "../Engine/Scene.h"

class Scene_Play : public Scene {
	//std::string levelPath;
	std::shared_ptr<Entity> m_player;
	//PlayerConfig playerConfig
	sf::Text m_scoreText;
	sf::Text m_livesText;
	sf::Font m_font;

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
	void sSpawnBullet();
	void sDebug();
	void sGameOver();

	// Helper Functions
	void spawnPlayer();
	int hRandom(int min, int max);
	float hDistanceTwoPoints(Vec2& v1, Vec2& v2);
};