#pragma once

#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <String>
#include "Engine.h"

using namespace sf;
using namespace std;

class Menu
{
private:
	Font font;
public:
	Menu();
	Menu(RenderWindow &window, Engine::gameState state);
	~Menu();
	Engine::gameState Run();
};
