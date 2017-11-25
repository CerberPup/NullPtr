#include "stdafx.h"
#include "Engine.h"
#include "Game.h"
#include <iostream>

Engine::Engine()
{
	window.create(sf::VideoMode(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)), "SFML works!");
	window.setPosition(Vector2i(0, 0));
	window.setFramerateLimit(60);
	state = gameState::MENU;
}


Engine::~Engine()
{
}

void Engine::run() {
	Menu menu(window, state);
	Game game(window, state);
	while (state != gameState::EXIT) {
		switch (state)
		{
		case gameState::GAME:
			game.Initialize();
			game.Run();
			state = gameState::EXIT;
			break;
		case gameState::MENU:
			menu.Run();
			break;
		default:
			break;
		}
	}
	window.close();
	return;
}
