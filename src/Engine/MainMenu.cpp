#include "MainMenu.h"
#include <Windows.h>
#include <iostream>

void MainMenu::init() {
	m_menuFont.loadFromFile("./arial.ttf");
	m_game1.setString("Geometry Wars");
	m_game1.setFont(m_menuFont);
	m_game1.setPosition(200, 100);
	m_game1.setStyle(sf::Text::Underlined);
	m_game2.setString("Still in Development");
	m_game2.setFont(m_menuFont);
	m_game2.setPosition(200, 200);
	m_game3.setString("Engine SandBox Mode");
	m_game3.setFont(m_menuFont);
	m_game3.setPosition(200, 300);
}

void MainMenu::run() {
	init();

	while (m_running) {
		sf::Event event;
		while (m_window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				m_window->close();
			}
		}
		sRender();
	}
}

void MainMenu::sRender() {
	m_window->draw(m_game1);
	m_window->draw(m_game2);
	m_window->draw(m_game3);
	m_window->display();
}

