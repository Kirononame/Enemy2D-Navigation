#include <iostream>
#include <math.h>

#include "App.h"
#include "Enemy.h"

#define EEPSILON .5

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

int Enemy::GetSize()
{
	return size;
}

void Enemy::Render()
{
	app->FillRect((int)x, (int)y, size, size, olc::CYAN);;
}

void Enemy::Move(float fElapsedTime)
{

	if (!app->path->WayExist())
	{
		app->path->NextNode();
		return;
	}

	float xDest = app->path->GetXFirst();
	float yDest = app->path->GetYFirst();

	// std::cout << abs(x - xDest) << abs(y - yDest);
	
	//right <
	if ((x - xDest) < -EEPSILON)
	{
		moving = true;
		x += speed * fElapsedTime;
		if (x >= app->ScreenWidth() - size)
			x = (float)(app->ScreenWidth() - size);
	}

	// left >
	if ((x - xDest) > EEPSILON)
	{
		moving = true;
		x -= speed * fElapsedTime;
		if (x <= 0)
			x = 0;
	}

	// down <
	if ((y - yDest) < -EEPSILON)
	{
		moving = true;
		y += speed * fElapsedTime;
		if (y >= app->ScreenHeight() - size)
			y = (float)(app->ScreenHeight() - size);
	}

	// up >
	if ((y - yDest) > EEPSILON)
	{
		moving = true;
		y -= speed * fElapsedTime;
		if (y <= 0)
			y = 0;
	}

	else
	{
		app->path->NextNode();
	}
	

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

	size = 8;

	speed = 20;

	return true;
}

bool Enemy::OnUserUpdate(float fElapsedTime)
{
	moving = false;
	Move(fElapsedTime);
	Render();

	return true;
}