#include "stdafx.h"
#include "Game.h"
#include <iostream>

Game::Game(RenderWindow &window, int &state)
{
	this->window = &window;
	this->state = &state;

	textBack.loadFromFile("Resources/City.png");
	textBack.setRepeated(true);
	spriteBack.setTexture(textBack);
	spriteBack.scale(1.2, 1.3);
	clockphysic.restart();
	clock.restart();
}

void Game::Run()
{
	int posX = 0;
	map = new Map(*window);
	while (*state == Engine::gameState::GAME)
	{
		Vector2f mouse(Mouse::getPosition(*window));
		Event event;

		while (window->pollEvent(event))
		{
			if (event.type == Event::Closed || event.type == Event::KeyPressed &&
				event.key.code == Keyboard::Escape)
				*state = Engine::gameState::EXIT;
			if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W))
			{
				if (player.onground) {
					player.onground = false;
					player.animation = Player::JUMP;
					player.velocity.y = -1000;
				}
			}
			if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))
			{
				if (player.sprite.getPosition().x > 0) {
					if (player.onground)
						player.animation = Player::LEFT;
					if (player.velocity.x > -200)
						player.velocity.x -= 50;
					if (posX > 0)
					{
						posX -= 10;
						map->Reposition(1);
					}
				}
				else {
					player.sprite.setPosition(0, player.sprite.getPosition().y);
				}
				//Player goes Left/Player stops/Player slows down
			}
			if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))
			{
				if (player.sprite.getPosition().x < 1080) {
					if (player.velocity.x < 200)
						player.velocity.x += 50;
					if (player.onground)
						player.animation = Player::RIGHT;
				}
				else {
					player.sprite.setPosition(0, player.sprite.getPosition().y);
				}
				//Player goes Right/Player speeds up
				if (posX < 480)
				{
					posX += 10;
					map->Reposition(-1);
				}
			}
		}
		spriteBack.setTextureRect(IntRect(posX, 0, 1920, 1080));

		//Player rotates 15
		Time elapsed = clockphysic.getElapsedTime();
		clockphysic.restart();
		player.physic(elapsed.asSeconds());

		if (clock.getElapsedTime() > milliseconds(100))
		{
			player.update();
			clock.restart();
		}
		window->clear();

		window->draw(spriteBack);

		map->Display(posX / 32);

		window->draw(player);
		window->display();

		clock.restart();
	}
}

Game::~Game()
{
}