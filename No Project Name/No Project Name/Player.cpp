#include "stdafx.h"
#include "Player.h"
#include <Windows.h>

Player::Player()
{
	if (!texture.loadFromFile("Resources/characters.png"))
	{
		MessageBox(NULL, TEXT("Textures not found!"), TEXT("ERROR"), NULL);
		return;
	}
	gravity = Vector2f(0, 9.81*2);
	animation = 0;
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 32, 32, 32));
	sprite.move(263, 800);
	sprite.setOrigin(16, 0);
	sprite.setScale(2, 2);
	velocity = Vector2f(0, 0);
	onground = true;
}

Player::~Player()
{
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(sprite, states);
}

void Player::physic(float delta) {
	Vector2f tmp = sprite.getPosition();
	if (!onground)
		velocity.y += gravity.y;
	float halfScreenY = 19 * 32;
	if (tmp.y > halfScreenY) {
		sprite.setPosition(tmp.x, halfScreenY-1);
		onground = true;
		velocity.y = 0;
	}
	if (velocity.x > 1|| velocity.x < -1) {
		velocity.x += 8 * (velocity.x > 0 ? -1 : 1);
	}
	else {
		velocity.x = 0;
	}
	sprite.move(velocity.x*delta, velocity.y*delta);
}

void Player::update()
{
	IntRect tmp = sprite.getTextureRect();
	switch (animation)
	{
	case Player::move::IDDLE:
		offset = 0;
		break;
	case Player::move::RIGHT:
		{
			offset = 0;
			Vector2f tmp2 = sprite.getScale();
			if (tmp2.x < 0)
				tmp2.x = tmp2.x*-1;
			sprite.setScale(tmp2);
			if (animationcounter == 3) {
				tmp.left = 0;
				animationcounter = 0;
				animation = Player::move::IDDLE;
			}
			else {
				tmp.left += 32;
				animationcounter++;
			}
		}
		break;
	case Player::move::LEFT:
		{
			offset = 0;
			Vector2f tmp2 = sprite.getScale();
			if (tmp2.x > 0)
				tmp2.x = tmp2.x*-1;
			sprite.setScale(tmp2);
			if (animationcounter == 3) {
				tmp.left = 0;
				animationcounter = 0;
				animation = Player::move::IDDLE;
			}
			else {
				tmp.left += 32;
				animationcounter++;
			}
		}
		break;
	case Player::move::JUMP:
		if(animationcounter == 0)
			tmp.left = 4*32;
		if (animationcounter == 3) {
			tmp.left = 0;
			animationcounter = 0;
			animation = Player::move::IDDLE;
		}
		else {
			tmp.left += 32;
			animationcounter++;
		}
		break;
	default:
		break;
		
		}
	sprite.setTextureRect(tmp);
}