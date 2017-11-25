#pragma once

#include "Map.h"
#include "Engine.h"
#include "Tile.h"
#include "Player.h"

class Game
{
private:
	RenderWindow *window;
	int* state;
	Texture textBack;
	Sprite spriteBack;
	Clock clock;
	Clock clockphysic;
	Image image;
	Player player;
	vector<Tile*> tiles;
	Map* map;
public:
	Game(RenderWindow &window, int &state);
	void Initialize();
	void Run();
	~Game();
};

