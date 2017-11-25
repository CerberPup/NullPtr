#include "stdafx.h"
#include "Game.h"


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
				//Player jumps
			}
			else if (event.type == Event::KeyPressed && (event.key.code == Keyboard::A || event.key.code == Keyboard::Left))
			{
				//Player goes Left/Player stops/Player slows down
			}
			else if (event.type == Event::KeyPressed && (event.key.code == Keyboard::D || event.key.code == Keyboard::Right))
			{
				//Player goes Right/Player speeds up
			}
		}

		//Player rotates 15 

		

		while (clock.getElapsedTime() < milliseconds(30))
		{

		}

		window->clear();

		for (int i = 0; i < 16; i++)
		{
			window->draw(*tiles.at(i));
		}

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
