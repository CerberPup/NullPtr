#include "stdafx.h"
#include "Engine.h"


Engine::Engine()
{
	window.create(sf::VideoMode(200, 200), "SFML works!");
	window.setFramerateLimit(60);
	state = gameState::MENU;
}


Engine::~Engine()
{
}

void Engine::run() {
	Menu menu(window, state);
	while (state != gameState::EXIT) {
		switch (state)
		{
		case gameState::GAME:
			
			break;
		case gameState::MENU:
			menu.Run();

			break;
		default:
			break;
		}
	}
	return;
}
