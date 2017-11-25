#include "stdafx.h"
#include "Tile.h"


Tile::Tile()
{
}

Tile::Tile(Image image)
{
	texture.loadFromImage(image, IntRect(128, 128, 128, 128));
	sprite.setTexture(texture);
}

void Tile::SetPosition(Vector2f pos)
{
	sprite.setPosition(pos);
	sprite.setScale(0.5, 0.5);
}



Tile::~Tile()
{
}
