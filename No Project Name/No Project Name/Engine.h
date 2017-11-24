#pragma once
#include "Menu.h"
#include <SFML/Graphics.hpp>

class Engine
{
private:
	sf::RenderWindow window;
	Menu menu;
	bool running;
public:
	enum gameState {
		Game,
		Menu,
		Exit
	};
	gameState state;
	Engine();
	~Engine();
	void run();
};

