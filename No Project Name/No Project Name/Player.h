#pragma once
#include "SFML/Graphics.hpp"

using namespace sf;
using namespace std;
class Player: public sf::Transformable, public sf::Drawable
{
private:
	vector<RectangleShape> vec;
	Sprite sprite;
	Texture texture;
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
public:
	void update(float angle);
	Player();
	~Player();
};

//Yup
//That's it
//There is nothing special
