#ifndef _GAMEENGINE_H
#define _GAMEENGINE_H

#include <SFML/Graphics.hpp>
#include "EntityManager.h"
#include "Scene.h"

class GameEngine {
	sf::RenderWindow m_window;
	int m_wWidth = 1024;
	int m_wLength = 768;
	//EntityManager m_entities;
	//std::shared_ptr<Entity> m_player;
	bool m_pause = false;
	bool m_running = true;
	int m_lives = 3;
	std::map<std::string, Scene*> scenes;
	std::string m_currentScene;
	sf::Text hud;
	sf::Font font;

public:
	void run();
	void update();
	void quit();

private:
	void init();
	//void setPause();
	Scene* getCurrentScene() { return scenes[m_currentScene]; };
	//void changeScene(Scene scene);
	sf::RenderWindow* getWindow() { return &m_window; };

	// Helper Functions
	void respawnPlayer();
	void spawnBullet(std::shared_ptr<Entity>& entity, Vec2 mousePos);
};

#endif