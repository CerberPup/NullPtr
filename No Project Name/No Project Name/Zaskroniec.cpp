#include "stdafx.h"
#include "Zaskroniec.h"
#include <Windows.h>


Zaskroniec::Zaskroniec()
{
	if (!texture.loadFromFile("Resources/characters.png"))
	{
		MessageBox(NULL, TEXT("Textures not found!"), TEXT("ERROR"), NULL);
		return;
	}
	animation = 0;
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 96, 32, 32));
	sprite.setOrigin(64, 0);
	sprite.setScale(8, 8);
	direction = false;
}

Zaskroniec::Zaskroniec(bool kierunek, Vector2f pos)
{
	if (!texture.loadFromFile("Resources/characters.png"))
	{
		MessageBox(NULL, TEXT("Textures not found!"), TEXT("ERROR"), NULL);
		return;
	}
	animation = 0;
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 96, 32, 32));
	sprite.setPosition(0,0);
	sprite.move(pos);
	sprite.setOrigin(8, 0);
	sprite.setScale(2, 2);
	direction = kierunek;
}

void Zaskroniec::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(sprite, states);
}

Zaskroniec::~Zaskroniec()
{
}

void Zaskroniec::update()
{
	IntRect tmp = sprite.getTextureRect();
	if (animation<=3) {
		Vector2f tmp2 = sprite.getScale();
		if (tmp2.x > 0)
			tmp2.x = tmp2.x*-1;
		sprite.setScale(tmp2);
		if (animation == 3) {
			tmp.left = 0;
			animation = 0;
		}
		else {
			tmp.left += 32;
			animation++;
		}
	}
	sprite.setTextureRect(tmp);
}
