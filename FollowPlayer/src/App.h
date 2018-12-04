#pragma once

#include "Engine.h"
#include "Player.h"
#include "AStar.h"
#include "Enemy.h"

class Player;
class Enemy;
class PathFinding;

class App : public olc::PixelGameEngine
{

private:
	static App* _instance;
	
public:
	App();
	Player* player;
	Enemy* enemy;
	PathFinding* path;

public:
	static App* getInstance();

	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;
};