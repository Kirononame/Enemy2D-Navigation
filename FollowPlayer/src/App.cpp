#define OLC_PGE_APPLICATION

#include <iostream>

#include "App.h"

#include "Player.h"
#include "AStar.h"
#include "Enemy.h"

App* App::_instance = NULL;

App* App::getInstance()
{
	if (_instance == NULL)
		_instance = new App(); //Not thread-safe version
	return _instance;

	//Note that _instance is *never* deleted - 
	//it exists for the entire lifetime of the program!
}

App::App()
{
	sAppName = "Game";	
}

bool App::OnUserCreate()
{
	std::cout << "This engine isn't mine please refer to this link for the license or any other questions about the engine" << std::endl;
	std::cout << "https://github.com/OneLoneCoder/olcPixelGameEngine/blob/master/olcPixelGameEngine.h" << std::endl;
	std::cout << "App Started" << std::endl;

	path = new PathFinding();
	player = new Player();
	enemy = new Enemy();
	
	player->OnUserCreate();
	enemy->OnUserCreate();
	path->OnUserCreate();

	return true;
}

bool App::OnUserUpdate(float fElapsedTime)
{
	path->OnUserUpdate(fElapsedTime);
	player->OnUserUpdate(fElapsedTime);
	enemy->OnUserUpdate(fElapsedTime);

	return true;
}
