#pragma once
#include "SFML/Graphics.hpp"
class Player: public sf::Transformable, public sf::Drawable
{
private:
	sf::Sprite sprite;
	sf::Texture texture;
	//virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
public:
	Player();
	~Player();
};

//Yup
//That's it
//There is nothing special
