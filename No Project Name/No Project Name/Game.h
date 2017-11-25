#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Engine.h"
#include "Tile.h"
#include "Player.h"

class Game
{
private:
	RenderWindow *window;
	int* state;
	Clock clock;
	Clock clockphysic;
	Image image;
	Player player;
	vector<Tile*> tiles;
public:
	Game(RenderWindow &window, int &state);
	void Initialize();
	void Run();
	~Game();
};

