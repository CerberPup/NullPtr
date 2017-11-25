#include "stdafx.h"
#include "Map.h"

Map::Map()
{
}

Map::Map(RenderWindow &window)
{
	srand(time(NULL));
	mapFile.open("Resources/Map.txt", ios::in);
	IntRect rect;
	int numb;
	for (int i = 0; i < 24; i++)
	{
		do
		{
			mapFile >> numb;
			map[i].push_back(numb);
		} while (numb != -1);
		map[i].pop_back();
	}
	int level = floorLevel;
	this->window = &window;
	image.loadFromFile("Resources/Tiles.png");
	Tile *tmp;
	int j;
	for (int i = 0; i < 24; i++)
	{
		j = 0;
		for each (int number in map[i])
		{
			if (number == 1)
				rect = IntRect(128, 32, 16, 16);

			if (number == 9)
				rect = IntRect(176, 16, 16, 16);

			if (number == 4)
				rect = IntRect(128, 80, 16, 16);

			if (number == 2)
				rect = IntRect(112, 32, 16, 16);

			if (number == 3)
				rect = IntRect(144, 32, 16, 16);

			if (number == 5)
				rect = IntRect(176, 32, 16, 16);

			if (number == 6)
				rect = IntRect(160, 48, 16, 16);

			if (number == 7)
				rect = IntRect(192, 48, 16, 16);

			if (number == 8)
				rect = IntRect(128, 96, 16, 16);

			if (number == 0)
				mapTiles[i].push_back(NULL);
			else
			{
				tmp = new Tile(image, rect);
				tmp->setPosition(Vector2f(j * 32, i * 32));
				tmp->setScale(2, 2);
				mapTiles[i].push_back(tmp);
			}
			j++;
		}
	}

	mapFile.close();
}

void Map::Display(int start)
{

	for (int i = 0; i < 24; i++)
	{
		for (int j = start; j < start + 64; j++)
		{
			if(mapTiles[i].at(j) != NULL)
				window->draw(*mapTiles[i].at(j));
		}
	}
}

void Map::Reposition(int side)
{
	Vector2f position;
	for (int i = 0; i < 24; i++)
	{
		for each (Tile* tile in mapTiles[i])
		{
			if (tile != NULL)
			{
				position = tile->getPosition();
				position.x += 20*side;
				tile->setPosition(position);
			}
		}
	}
}

Map::~Map()
{
}
