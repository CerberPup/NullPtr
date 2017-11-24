#include "stdafx.h"
#include "Engine.h"


Engine::Engine()
{
	const HWND hDesktop = GetDesktopWindow();
	RECT ResolutionRect;
	GetWindowRect(hDesktop, &ResolutionRect);
	window.setPosition(Vector2i(0, 0));
	window.create(sf::VideoMode(ResolutionRect.right,ResolutionRect.bottom), "SFML works!");
	//MessageBox(NULL, TEXT("" + ResolutionRect.right + ResolutionRect.bottom), TEXT("k"), NULL);
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
