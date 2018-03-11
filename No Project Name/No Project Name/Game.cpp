#include "stdafx.h"
#include "Game.h"
#include <string>
#include <iostream>
#include <python.h>
#include <thread>


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
	phys = new thread((&Game::async),this);
	animate = new thread((&Game::animation), this);
}

long int Game::Pyth(char* file, char* function, char* arg1, char* arg2)
{
	char *argv[] = { "", file,function,arg1,arg2, NULL };
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
				return (long int) PyLong_AsLong(pValue);
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

void Game::async() 
{
	while (true) {
		Time elapsed = clockphysic.getElapsedTime();
		clockphysic.restart();
		player.physic(elapsed.asSeconds());
		Sleep(10);
	}
}
void Game::animation()
{
	while (true) {
		wonsz.update();
		player.update();
		Sleep(100);
		cout << "anim" << endl;
	}
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
			if (player.onground) {
				player.onground = false;
				player.animation = Player::JUMP;
				player.velocity.y = -600;
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))
		{
			if (player.sprite.getPosition().x > 0) {
			//if (player.onground)
			player.animation = Player::LEFT;
			/*if (player.velocity.x > -200)
			player.velocity.x -= 50;*/
			if (posX > 0)
			{
				posX -= 5;
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
			if (player.sprite.getPosition().x < 1300) {
			/*if (player.velocity.x < 200)
			player.velocity.x += 50;*/
			//if (player.onground)
			player.animation = Player::RIGHT;
			}
			else {
			player.sprite.setPosition(1300, player.sprite.getPosition().y);
			}
			if (posX < 5000)
			{
				posX += 5;
				map->Reposition(-1);
			}
		}
		spriteBack.setTextureRect(IntRect(posX, 0, 1920, 1080));
		/*if (player.sprite.getPosition().x > 520) {
			Sleep(100);
			GiveScript();
			if (Pyth("py", "multiply", "5", "4") == Pyth("script", "multiply", "5", "4")) {
				MessageBox(NULL, TEXT("Rozwi¹za³eœ poprawnie zadanie."), TEXT("Gratulacje"), NULL);
			}
			else {
				MessageBox(NULL, TEXT("Tym razem nie uda³o Ci siê rozwi¹zaæ zadania. Próbuj dalej."), TEXT("Ups..."), NULL);
			}
			*state = Engine::EXIT;

		}*/
		//cout << player.sprite.getPosition().x<<endl;

		//Player rotates 15
		
		window->clear();

		window->draw(spriteBack);

		map->Display(posX / 32);
		
		window->draw(player);
		window->draw(wonsz);
		window->display();
	}
}

void Game::GiveScript()
{
	fstream script;
	script.open("script.py", ios::out);

	RenderWindow newWindow;
	newWindow.create(sf::VideoMode(800, 500), "Type your script here!");
	newWindow.setPosition(Vector2i(100, 50));
	newWindow.setFramerateLimit(60);

	Font scriptFont;
	scriptFont.loadFromFile("Resources/Arial.ttf");
	std::string output = "#Write script in Python\n#with \"multiply\" function\n#that will multiply 2 given numbers\n#Press End to finish\n\n";
	Text text(output, scriptFont, 20);
	text.setPosition(10, 10);
	text.setStyle(sf::Text::Bold);
	text.setFillColor(sf::Color::White);
	Event event;
	while (!Keyboard::isKeyPressed(Keyboard::End))
	{
		while (newWindow.pollEvent(event))
		{
			if (event.type == sf::Event::TextEntered)
			{
				if (event.text.unicode != 8)
					output += (char)event.text.unicode;
				if (event.text.unicode == 8)
					output = output.substr(0, output.length() - 1);
				if (event.text.unicode == 13)
				{
					output = output.substr(0, output.length() - 1);
					output += "\n";
				}
			}
		}
		text.setString(output);
		newWindow.clear();
		newWindow.draw(text);
		newWindow.display();
	}
	newWindow.close();
	script << output;
	script.flush();
	script.close();
}

Game::~Game()
{
}