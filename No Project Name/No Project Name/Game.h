#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Engine.h"
#include "Tile.h"

class Game
{
private:
	RenderWindow *window;
	int* state;
	Clock clock;
	Image image;
	vector<Tile*> tiles;
public:
	Game(RenderWindow &window, int &state);
	void Initialize();
	void Run();
	~Game();
};

