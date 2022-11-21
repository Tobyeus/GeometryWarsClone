#pragma once
#include "Scene.h"

class MainMenu : Scene {
	std::vector<std::string> menuStrings;
	sf::Text menuText;
	std::vector<std::string> levelPaths;
	sf::Font m_menuFont;
	bool m_running = true;
	sf::Text m_game1;
	sf::Text m_game2;
	sf::Text m_game3;

	void init();
	//void sRender();
	//void sDoAction(Action action);

	void update() {};
	void sDoAction(Action& action) {};
	void sMouseInput(sf::Event& event) {};
	void sRender();
	void sDebug() {};

public:
	void run();
	MainMenu();
	MainMenu(sf::RenderWindow* window) : Scene(window) {};
};