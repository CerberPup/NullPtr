#include "stdafx.h"
#include "Menu.h"

Menu::Menu()
{
	
}

Menu::Menu(RenderWindow &window, Engine::gameState state)
{
	state = Engine::gameState::Exit;

	if (!font.loadFromFile("Resources/Pixeled.tff"))
	{
		MessageBox(NULL, (LPCWSTR) "Font not found!", (LPCWSTR)  "ERROR", NULL);
		return;
	}

	state = Engine::gameState::Menu;
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
}
