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
	RenderWindow *window;
	int* state;
	Vector2u size;
public:
	Menu();
	Menu(RenderWindow &window, int &state);
	~Menu();
	void Run();
};
