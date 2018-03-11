#pragma once
#include "SFML/Graphics.hpp"

using namespace sf;
using namespace std;
class Player : public sf::Transformable, public sf::Drawable
{
private:
	Vector2f gravity;
	Vector2f pos;
	int animationcounter;
	int offset;
	Texture texture;
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
public:
	void physic(float delta);
	int animation;
	bool onground;
	Vector2f velocity;
	enum move {
		LEFT, RIGHT, JUMP, IDDLE
	};
	Sprite sprite;
	void update();
	Player();
	~Player();
};

//Yup
//That's it
//There is nothing special
