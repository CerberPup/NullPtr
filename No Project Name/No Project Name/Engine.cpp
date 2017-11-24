#include "stdafx.h"
#include "Engine.h"


Engine::Engine()
{
	running = true;
}


Engine::~Engine()
{
}

void Engine::run() {

	while (running) {
		switch (state)
		{
		case gameState::Game:
				
			break;
		case gameState::Menu:
			menu.Run();
			break;
		case gameState::Exit:
			running = false;
			break;
		default:
			break;
		}
	}
	return;
}
