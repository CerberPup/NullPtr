#pragma once

#include <conio.h>
#include <fstream>
#include "Map.h"
#include "Engine.h"
#include "Tile.h"
#include "Player.h"
#include "Zaskroniec.h"

class Game
{
private:
	RenderWindow *window;
	Zaskroniec wonsz;
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
	void Run(int argc, char* argv[]);
	long int Pyth(char* file, char* function, char* arg1, char* arg2);
	void GiveScript();
	~Game();
};
