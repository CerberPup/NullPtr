#include "stdafx.h"
#include "Player.h"
#include <Windows.h>


Player::Player()
{
	if (!texture.loadFromFile("Resources/characters.png"))
	{
		MessageBox(NULL, TEXT("Textures not found!"),TEXT( "ERROR"), NULL);
		return;
	}
	gravity = Vector2f(0,98.1);
	animation = 0;
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 32, 32, 32));
	sprite.move(32, 800);
	sprite.setOrigin(16,0);
	sprite.setScale(4, 4);
	velocity = Vector2f(0,0);
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
	float halfScreenY = GetSystemMetrics(SM_CYSCREEN) / 2;
	if (tmp.y >= halfScreenY + 192) {
		sprite.setPosition(tmp.x, halfScreenY + 190);
		onground = true;
		velocity.y = 0;
	}
	velocity.x += 8*(velocity.x>0?-1:1);
	sprite.move(velocity.x*delta,velocity.y*delta);
}

void Player::update()
{

	IntRect tmp = sprite.getTextureRect();
	if (animation == Player::move::RIGHT) {
		
		Vector2f tmp2 = sprite.getScale();
		if (tmp2.x<0)
			tmp2.x = tmp2.x*-1;
		sprite.setScale(tmp2);
		if (animationcounter == 3) {
			tmp.left = 0;
			animationcounter = 0;
		}
		else {
			tmp.left += 32;
			animationcounter++;
		}
	}else if(animation == Player::move::LEFT) {
		Vector2f tmp2 = sprite.getScale();
		if (tmp2.x>0)
			tmp2.x = tmp2.x*-1;
		sprite.setScale(tmp2);
		if (animationcounter == 3) {
			tmp.left = 0;
			animationcounter = 0;
		}
		else {
			tmp.left += 32;
			animationcounter++;
		}
	}
	else if (animation == Player::move::JUMP) {
		
		/*if (animationcounter == 3) {
			tmp.left = 0;
			animationcounter = 0;
		}
		else {
			tmp.left += 32;
			animationcounter++;
		}*/
	}
	sprite.setTextureRect(tmp);
}
