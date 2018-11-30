#include <iostream>

#include "App.h"
#include "Enemy.h"

Enemy::Enemy()
{
	app = App::getInstance();
}

float Enemy::GetX()
{
	return x;
}

float Enemy::GetY()
{
	return y;
}

void Enemy::Render()
{
	app->FillRect((int)x, (int)y, size, size, olc::GREEN);;
}

void Enemy::Move(float fElapsedTime)
{


}

bool Enemy::IsMoving()
{
	return moving;
}

bool Enemy::OnUserCreate()
{
	std::cout << "Player Initaited" << std::endl;

	x = (float)(app->ScreenWidth() / 4);
	y = (float)(app->ScreenHeight() / 4);

	size = 5;

	speed = 100;

	return true;
}

bool Enemy::OnUserUpdate(float fElapsedTime)
{
	moving = false;
	//Move(fElapsedTime);
	//Render();

	return true;
}