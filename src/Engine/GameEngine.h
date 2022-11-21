#ifndef _GAMEENGINE_H
#define _GAMEENGINE_H

#include <SFML/Graphics.hpp>
#include "EntityManager.h"
#include "../GeometryWars/Scene_Play.h"
#include <stdlib.h>
#include <iostream>
#include "imgui.h"
#include "imgui-SFML.h"

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

public:
	void run();
	void update();
	void quit();
	sf::RenderWindow* getWindow() { return &m_window; };

private:
	void init();
	//void setPause();
	Scene* getCurrentScene() { return scenes[m_currentScene]; };
	//void changeScene(Scene scene);

	// Helper Functions
	void respawnPlayer();
	void spawnBullet(std::shared_ptr<Entity>& entity, Vec2 mousePos);
};

#endif