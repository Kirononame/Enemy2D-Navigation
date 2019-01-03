#pragma once

#include "Engine.h"
#include "Player.h"
#include "PathFinding.h"
#include "Enemy.h"

class Player;
class Enemy;
class PathFinding;


// Used as singelton pattern works as the main application and have a reference to all game objects in the game

class App : public olc::PixelGameEngine
{

private:
	static App* _instance;
	
public:

	App();

	// GameObjects
	Player* player;
	Enemy* enemy;
	PathFinding* path;

public:
	static App* getInstance();

	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;
};