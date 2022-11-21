#include "GameEngine.h"
#include "MainMenu.h"

void GameEngine::init() {
	std::cout << "Game Engine Init" << std::endl;
	m_window.create(sf::VideoMode(m_wWidth, m_wLength), "Game Window");
	m_window.setFramerateLimit(60);
	m_window.clear(sf::Color::Black);
	m_window.display();
	srand((unsigned int)time(NULL));
	ImGui::SFML::Init(m_window);
}

// Main Game loop
void GameEngine::run() {
	// Initialization
	init();

	// Generate Play Scene
	Scene_Play scene1(getWindow());
	m_currentScene = "scene1";
	scenes.insert(std::make_pair(m_currentScene, &scene1));

	sf::Clock deltaClock;

	// Gameloop
	while (m_running) {
	
		// Event Polling
		sf::Event event;
		while (m_window.pollEvent(event)) {

			ImGui::SFML::ProcessEvent(event);
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

		ImGui::SFML::Update(m_window, deltaClock.restart());

		// Paused
		if (getCurrentScene()->m_pause && !getCurrentScene()->m_hadEnded) {
			getCurrentScene()->sDebug();
			getCurrentScene()->sRender();
			continue;
		}

		// Game Over
		if (getCurrentScene()->m_hadEnded) {
			getCurrentScene()->sDebug();
			getCurrentScene()->sRender();
			continue;
		}

		// Do stuff of the current scene
		getCurrentScene()->update();

	}
	std::cout << "Game Loop closing" << std::endl;
	ImGui::SFML::Shutdown();
	m_window.close();
}

void GameEngine::quit() {
	m_window.close();
}