#include "stdafx.h"
#include "Tile.h"

Tile::Tile()
{
}

void Tile::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(sprite, states);
}

Tile::Tile(Image image, IntRect rect)
{
	texture.loadFromImage(image, rect);
	sprite.setTexture(texture);
}

Tile::~Tile()
{
}