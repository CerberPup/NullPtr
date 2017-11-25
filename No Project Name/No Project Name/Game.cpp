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
			
		}
		if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W))
		{
			//Player jumps
		}
		if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))
		{
			if (posX > 0)
			{
				posX -= 10;
				map->Reposition(1);
			}
		}
		else if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))
		{
			if (posX < 480)
			{
				if (player.velocity.x<200)
					player.velocity.x += 50;
				if (player.onground)
				player.animation = Player::RIGHT;
				//Player goes Right/Player speeds up
				posX += 10;
				map->Reposition(-1);
			}
		}

		spriteBack.setTextureRect(IntRect(posX, 0, 1920, 1080));	
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

		window->draw(spriteBack);

		map->Display(posX/32);

		for (int i = 0; i < 16; i++)
		{
			window->draw(*tiles.at(i));
		}
		window->draw(player);
		window->display();

		clock.restart();

		
	}
}

void Game::Initialize()
{

}

Game::~Game()
{

}
