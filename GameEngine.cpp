#include "GameEngine.h"
#include <stdlib.h>
#include "Scene.h"

void GameEngine::init() {
	std::cout << "Game Engine Init" << std::endl;
	m_window.create(sf::VideoMode(m_wWidth, m_wLength), "Game Window");
	m_window.setFramerateLimit(60);
	srand((unsigned int)time(NULL));
}

// Main Game loop
void GameEngine::run() {
	// Initialization
	init();

	// Generate Play Scene
	Scene_Play scene1(getWindow());
	m_currentScene = "scene1";
	scenes.insert(std::make_pair(m_currentScene, &scene1));

	// Gameloop
	while (m_running) {
	
		// Event Polling
		sf::Event event;
		while (m_window.pollEvent(event)) {
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed) {
				quit();
			}

			if (event.type == sf::Event::KeyPressed	|| event.type == sf::Event::KeyReleased) {
				// Key is not mapped
				if (!getCurrentScene()->m_actionMap.contains(event.key.code)) {
					continue;
				}
				std::string actionType = event.type == sf::Event::KeyPressed ? "PRESS" : "RELEASE";
				getCurrentScene()->doAction(Action(getCurrentScene()->m_actionMap.at(event.key.code), actionType));
			}

			if (event.type == sf::Event::MouseButtonPressed) {
				getCurrentScene()->mouseInput(event);
			}
		}

		// Do stuff of the current scene
		getCurrentScene()->update();

		// Scene ended -> close Window
		if (getCurrentScene()->m_hadEnded) {
			quit();
		}
	}
	std::cout << "Game Loop closing" << std::endl;
	m_window.close();
}

void GameEngine::quit() {
	m_window.close();
}