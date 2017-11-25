#include "stdafx.h"
#include "Game.h"
#include <iostream>

Game::Game(RenderWindow &window, int &state)
{
	this->window = &window;
	this->state = &state;
	image.loadFromFile("Resources/Tiles.png");
	Tile *tmp;
	for (int i = 0; i < 16; i++)
	{
		tmp = new Tile(image);
		tmp->SetPosition(Vector2f(i * 64, 300));
		tiles.push_back(tmp);
	}
	clockphysic.restart();
	clock.restart();
}

void Game::Run()
{
	while (*state == Engine::gameState::GAME)
	{
		Vector2f mouse(Mouse::getPosition(*window));
		Event event;

		while (window->pollEvent(event))
		{
			if (event.type == Event::Closed || event.type == Event::KeyPressed &&
				event.key.code == Keyboard::Escape)
				*state = Engine::gameState::EXIT;
			else if (event.type == Event::KeyPressed && (event.key.code == Keyboard::W || event.key.code == Keyboard::Up))
			{
				if (player.onground) {
					player.onground = false;
					player.animation = Player::JUMP;
					player.velocity.y=-2000 ;
				}
			}
			else if (event.type == Event::KeyPressed && (event.key.code == Keyboard::A || event.key.code == Keyboard::Left))
			{
				if (player.onground)
				player.animation = Player::LEFT;
				if(player.velocity.x>-200)
				player.velocity.x -=50;
				//Player goes Left/Player stops/Player slows down
			}
			else if (event.type == Event::KeyPressed && (event.key.code == Keyboard::D || event.key.code == Keyboard::Right))
			{
				if (player.velocity.x<200)
					player.velocity.x += 50;
				if (player.onground)
				player.animation = Player::RIGHT;
				//Player goes Right/Player speeds up
			}
		}
#ifdef DEBUG
		cout << player.sprite.getGlobalBounds().contains(mouse);
#endif // DEBUG
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
		for (int i = 0; i < 16; i++)
		{
			window->draw(*tiles.at(i));
		}
		window->draw(player);
		window->display();
		
	}
}

void Game::Initialize()
{

}

Game::~Game()
{

}
