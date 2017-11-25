#pragma once

#include <vector>
#include <Windows.h>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include "Tile.h"


class Map
{
private:
	int floorLevel = (GetSystemMetrics(SM_CYSCREEN) / 2 + 192);
	RenderWindow *window;
	Image image;
	vector<Tile*> mapTiles[24];
	vector<int> map[24];
	fstream mapFile;

public:
	Map();
	Map(RenderWindow &window);
	void Display(int start);
	void Reposition(int side);
	~Map();
};

