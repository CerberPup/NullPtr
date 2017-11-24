#pragma once
#include "Menu.h"

class Engine
{
private:
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

