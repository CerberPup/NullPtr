#include "stdafx.h"
#include "Menu.h"

Menu::Menu()
{
	
}

Menu::Menu(RenderWindow &window, Engine::gameState &state)
{
	state = Engine::gameState::Exit;

	if (!font.loadFromFile("Resources/Pixeled.tff"))
	{
		MessageBox(NULL, (LPCWSTR) "Font not found!", (LPCWSTR)  "ERROR", NULL);
		return;
	}

	this->window = &window;

	state = Engine::gameState::Menu;

	this->state = state;
}

Menu::~Menu()
{

}

Engine::gameState Menu::Run() 
{
	Text title("There is no title", font, 80);
	title.setStyle(Text::Bold);
	title.setPosition(1280 / 2 - title.getGlobalBounds().width / 2, 20);

	const short int options = 2;

	Text texts[options];

	string str[] = { "Play","Exit" };
	for (int i = 0; i < options; i++)
	{
		texts[i].setFont(font);
		texts[i].setCharacterSize(65);

		texts[i].setString(str[i]);
		texts[i].setPosition(1280 / 2 - texts[i].getGlobalBounds().width / 2, 250 + i * 120);
	}

	while (state == Engine::gameState::Menu)
	{
		Vector2f mouse(Mouse::getPosition(*window));
		Event event;

		while (window->pollEvent(event))
		{
			if (event.type == Event::Closed || event.type == Event::KeyPressed &&
				event.key.code == Keyboard::Escape)
				state = Engine::gameState::Exit;

			else if (texts[1].getGlobalBounds().contains(mouse) &&
				event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				state = Engine::gameState::Exit;
			}
		}
		for (int i = 0; i < options; i++)
			if (texts[i].getGlobalBounds().contains(mouse))
				texts[i].setColor(Color::Cyan);
			else texts[i].setColor(Color::White);

			window->clear();

			window->draw(title);
			for (int i = 0; i < options; i++)
				window->draw(texts[i]);

			window->display();
	}
}
