// No Project Name.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Engine.h"
#include <Windows.h>

#include <SFML/Graphics.hpp>

int main()
{
	//MessageBox(NULL, (LPCWSTR) "a", (LPCWSTR) "t", NULL);
	Engine engine;
	engine.run();
	return 0;
}