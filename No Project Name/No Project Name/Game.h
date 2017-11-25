#pragma once

#include "Map.h"
#include "Engine.h"

class Game
{
private:
	RenderWindow *window;
	int* state;
	Texture textBack;
	Sprite spriteBack;
	Clock clock;
	Map* map;
public:
	Game(RenderWindow &window, int &state);
	void Initialize();
	void Run();
	~Game();
};

