#pragma once

#include <conio.h>
#include <fstream>
#include "Map.h"
#include "Engine.h"
#include "Tile.h"
#include "Player.h"
#include "Zaskroniec.h"
#include <thread>

class Game
{
private:
	RenderWindow *window;
	Zaskroniec wonsz;
	int* state;
	Texture textBack;
	Sprite spriteBack;
	Clock clock;
	
	Image image;
	
	vector<Tile*> tiles;
	Map* map;
	Vector2f velocity;
	float delta;
	thread* phys;
public:
	Clock clockphysic;
	Player player;
	Game(RenderWindow &window, int &state);
	void Run();
	long int Pyth(char* file, char* function, char* arg1, char* arg2);
	void async();
	void GiveScript();
	~Game();
};
