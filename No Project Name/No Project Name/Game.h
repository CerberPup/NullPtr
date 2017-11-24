#pragma once
#include <SFML/Graphics.hpp>
#include "Engine.h"

class Game
{
private:
	RenderWindow *window;
	int* state;
public:
	Game(RenderWindow &window, int &state);
	~Game();
};

