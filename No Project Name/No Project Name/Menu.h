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
public:
	Menu();
	Menu(RenderWindow &window, int &state);
	~Menu();
	void Run();
};
