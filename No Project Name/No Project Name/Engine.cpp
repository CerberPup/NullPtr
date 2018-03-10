#include "stdafx.h"
#include "Engine.h"
#include "Game.h"
#include <iostream>

Engine::Engine()
{
	window.create(sf::VideoMode(1300, 732), "Zaskroniec");
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