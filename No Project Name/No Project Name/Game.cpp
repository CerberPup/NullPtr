#include "stdafx.h"
#include "Game.h"
#include <iostream>
#include <python.h>


Game::Game(RenderWindow &window, int &state)
{
	this->window = &window;
	this->state = &state;
	wonsz.setPosition(Vector2f(200,408));
	wonsz.direction = false;
	textBack.loadFromFile("Resources/City.png");
	textBack.setRepeated(true);
	spriteBack.setTexture(textBack);
	spriteBack.scale(1.2, 1.3);
	clockphysic.restart();
	clock.restart();
}

int Game::Pyth(char* file, char* function, char* arg1, char* arg2, char* arg3=NULL)
{
	char *argv[] = { "", file,function,arg1,arg2,arg3, NULL };
	int argc = sizeof(argv) / sizeof(char*) - 1;

	PyObject *pName, *pModule, *pDict, *pFunc;
	PyObject *pArgs, *pValue;
	int i;

	if (argc < 3) {
		fprintf(stderr, "Usage: call pythonfile funcname [args]\n");
		return 1;
	}

	Py_Initialize();
	pName = PyUnicode_DecodeFSDefault(argv[1]);
	/* Error checking of pName left out */

	pModule = PyImport_Import(pName);
	Py_DECREF(pName);

	if (pModule != NULL) {
		pFunc = PyObject_GetAttrString(pModule, argv[2]);
		/* pFunc is a new reference */

		if (pFunc && PyCallable_Check(pFunc)) {
			pArgs = PyTuple_New(argc - 3);
			for (i = 0; i < argc - 3; ++i) {
				pValue = PyLong_FromLong(atoi(argv[i + 3]));
				if (!pValue) {
					Py_DECREF(pArgs);
					Py_DECREF(pModule);
					fprintf(stderr, "Cannot convert argument\n");
					return 1;
				}
				/* pValue reference stolen here: */
				PyTuple_SetItem(pArgs, i, pValue);
			}
			pValue = PyObject_CallObject(pFunc, pArgs);
			Py_DECREF(pArgs);
			if (pValue != NULL) {
				printf("Result of call: %ld\n", PyLong_AsLong(pValue));
				Py_DECREF(pValue);
			}
			else {
				Py_DECREF(pFunc);
				Py_DECREF(pModule);
				PyErr_Print();
				fprintf(stderr, "Call failed\n");
				return 1;
			}
		}
		else {
			if (PyErr_Occurred())
				PyErr_Print();
			fprintf(stderr, "Cannot find function \"%s\"\n", argv[2]);
		}
		Py_XDECREF(pFunc);
		Py_DECREF(pModule);
	}
	else {
		PyErr_Print();
		fprintf(stderr, "Failed to load \"%s\"\n", argv[1]);
		return 1;
	}
	if (Py_FinalizeEx() < 0) {
		return 120;
	}
	return 0;
}

void Game::Run(int argc, char* argv[])
{
	//Pyth(argc, argv);
	
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
			if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W))
			{
				if (player.onground) {
					player.onground = false;
					player.animation = Player::JUMP;
					player.velocity.y = -1000;
				}
			}
			if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))
			{
				if (player.sprite.getPosition().x > 0) {
					if (player.onground)
						player.animation = Player::LEFT;
					if (player.velocity.x > -200)
						player.velocity.x -= 50;
					if (posX > 0)
					{
						posX -= 10;
						map->Reposition(1);
					}
				}
				else {
					player.sprite.setPosition(0, player.sprite.getPosition().y);
				}
				//Player goes Left/Player stops/Player slows down
			}
			if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))
			{
				if (player.sprite.getPosition().x < 1080) {
					if (player.velocity.x < 200)
						player.velocity.x += 50;
					if (player.onground)
						player.animation = Player::RIGHT;
				}
				else {
					player.sprite.setPosition(0, player.sprite.getPosition().y);
				}
				//Player goes Right/Player speeds up
				if (posX < 480)
				{
					posX += 10;
					map->Reposition(-1);
				}
			}
		}
		spriteBack.setTextureRect(IntRect(posX, 0, 1920, 1080));

		if (player.sprite.getPosition().x > 520) {
			*state = Engine::MENU;
		}
		//cout << player.sprite.getPosition().x<<endl;

		//Player rotates 15
		Time elapsed = clockphysic.getElapsedTime();
		clockphysic.restart();
		player.physic(elapsed.asSeconds());

		if (clock.getElapsedTime() > milliseconds(100))
		{
			wonsz.update();
			player.update();
			clock.restart();
		}
		window->clear();

		window->draw(spriteBack);

		map->Display(posX / 32);
		
		window->draw(player);
		window->draw(wonsz);
		window->display();
	}
}

Game::~Game()
{
}