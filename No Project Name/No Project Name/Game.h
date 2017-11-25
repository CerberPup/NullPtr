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
	Vector2f velocity;
	float delta;
public:
	Game(RenderWindow &window, int &state);
	void Run();
	~Game();
};
