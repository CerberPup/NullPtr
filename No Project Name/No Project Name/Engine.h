#pragma once
#include "Menu.h"
#include <SFML/Graphics.hpp>

class Engine
{
private:
	char** arrr;
	int arg;
	sf::RenderWindow window;
	bool running;
public:
	enum gameState {
		GAME,
		MENU,
		EXIT
	};
	int state;
	Engine();
	
	~Engine();
	void run();
};
