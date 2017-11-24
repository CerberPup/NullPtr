#include "stdafx.h"
#include "Engine.h"


Engine::Engine()
{
	const HWND hDesktop = GetDesktopWindow();
	RECT ResolutionRect;
	GetWindowRect(hDesktop, &ResolutionRect);
	window.create(sf::VideoMode(ResolutionRect.right,ResolutionRect.bottom), "SFML works!", sf::Style::Fullscreen);
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
