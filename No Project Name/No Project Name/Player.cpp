#include "stdafx.h"
#include "Player.h"


Player::Player()
{
	vec.push_back(RectangleShape(Vector2f(50, 50)));
}


Player::~Player()
{
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply the transform
	states.transform *= getTransform();

	// our particles don't use a texture
	states.texture = NULL;

	// draw the vertex array
	//target.draw(m_vertices, states);
	for each (RectangleShape var in vec)
	{
		target.draw(var, states);
	}
}

void Player::update(float angle)
{
	for each (RectangleShape var in vec)
	{

	}
}

/*
POINT rotate_point(float cx, float cy, float angle, POINT p)
{
	float s = sin(angle);
	float c = cos(angle);

	// translate point back to origin:
	p.x -= cx;
	p.y -= cy;

	// rotate point
	float xnew = p.x * c - p.y * s;
	float ynew = p.x * s + p.y * c;

	// translate point back:
	p.x = xnew + cx;
	p.y = ynew + cy;
	return p;
}*/