#pragma once
#include "SFML/Graphics.hpp"

using namespace sf;
using namespace std;

class Tile : public sf::Drawable, public sf::Transformable
{
private:
	Texture texture;
	Sprite sprite;
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
public:

	Tile();
	Tile(Image image, IntRect rect);
	~Tile();
};
