#include "stdafx.h"
#include "Engine.h"


Engine::Engine()
{
	window.create(sf::VideoMode(200, 200), "SFML works!");
	state = gameState::Menu;
}


Engine::~Engine()
{
}

void Engine::run() {

	while (state != gameState::Exit) {
		switch (state)
		{
		case gameState::Game:
				
			break;
		case gameState::Menu:
			//state = menu.Run(window);
			break;
		default:
			break;
		}
	}
	return;
}
