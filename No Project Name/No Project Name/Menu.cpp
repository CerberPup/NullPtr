#include "stdafx.h"
#include "Menu.h"

Menu::Menu()
{
}

Menu::Menu(RenderWindow &window, int &state)
{
	state = Engine::gameState::EXIT;

	if (!font.loadFromFile("Resources/Pixeled.ttf"))
	{
		MessageBox(NULL, TEXT("Font not found!"), TEXT("ERROR"), NULL);
		return;
	}

	this->window = &window;

	state = Engine::gameState::MENU;

	this->state = &state;

	size = window.getSize();
}

Menu::~Menu()
{
}

void Menu::Run()
{
	Text title("Zaskroniec", font, 80);
	title.setStyle(Text::Bold);
	title.setPosition(size.x / 2 - title.getGlobalBounds().width / 2, 20);

	const short int options = 2;

	Text texts[options];

	string str[] = { "Play","Exit" };
	for (int i = 0; i < options; i++)
	{
		texts[i].setFont(font);
		texts[i].setCharacterSize(65);

		texts[i].setString(str[i]);
		texts[i].setPosition(size.x / 2 - texts[i].getGlobalBounds().width / 2, 350 + i * 120);
	}

	while (*state == Engine::gameState::MENU)
	{
		Vector2f mouse(Mouse::getPosition(*window));
		Event event;

		while (window->pollEvent(event))
		{
			if (event.type == Event::Closed || event.type == Event::KeyPressed &&
				event.key.code == Keyboard::Escape)
				*state = Engine::gameState::EXIT;

			else if (texts[1].getGlobalBounds().contains(mouse) &&
				event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				*state = Engine::gameState::EXIT;
			}
			else if (texts[0].getGlobalBounds().contains(mouse) &&
				event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				*state = Engine::gameState::GAME;
			}
		}
		for (int i = 0; i < options; i++)
			if (texts[i].getGlobalBounds().contains(mouse))
				texts[i].setFillColor(Color::Cyan);
			else texts[i].setFillColor(Color::White);

			window->clear();

			window->draw(title);
			for (int i = 0; i < options; i++)
				window->draw(texts[i]);

			window->display();
	}
}