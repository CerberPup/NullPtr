#include "stdafx.h"
#include "Game.h"


Game::Game(RenderWindow &window, int &state)
{
	this->window = &window;
	this->state = &state;

	textBack.loadFromFile("Resources/City.png");
	textBack.setRepeated(true);
	spriteBack.setTexture(textBack);
	spriteBack.scale(1.2, 1.3);
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
				posX += 10;
				map->Reposition(-1);
			}
		}

		spriteBack.setTextureRect(IntRect(posX, 0, 1920, 1080));	

		while (clock.getElapsedTime() < milliseconds(30))
		{

		}

		window->clear();

		window->draw(spriteBack);

		map->Display(posX/32);

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
