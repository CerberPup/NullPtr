#pragma once
#include "SFML/Graphics.hpp"

using namespace sf;

class Tile: public sf::Drawable, public sf::Transformable
{
private:
	Sprite sprite;
	Texture texture;
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		target.draw(sprite);
	}
public:
	Tile();
	Tile(Image image);
	void SetPosition(Vector2f pos);
	~Tile();
};

