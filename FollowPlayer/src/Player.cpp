#include <iostream>

#include "App.h"
#include "Player.h"


Player::Player()
{
	app = App::getInstance();
}

float Player::GetX()
{
	return x;
}

float Player::GetY()
{
	return y;
}

void Player::SetX(float num)
{
	x = num;
}

void Player::SetY(float num)
{
	y = num;
}


int Player::GetSize()
{
	return size;
}

void Player::Render()
{
	app->FillRect((int)x, (int)y, size, size, olc::GREEN);;
}

void Player::Move(float fElapsedTime)
{

	if (app->GetKey(olc::RIGHT).bHeld)
	{
		moving = true;

		x += speed * fElapsedTime;
		if (x >= app->ScreenWidth() - size)
			x = (float)(app->ScreenWidth() - size);

	}

	else if (app->GetKey(olc::LEFT).bHeld)
	{
		moving = true;

		x -= speed * fElapsedTime;
		if (x <= 0)
			x = 0;
	}

	if (app->GetKey(olc::DOWN).bHeld)
	{
		moving = true;

		y += speed * fElapsedTime;
		if (y >= app->ScreenHeight() - size)
			y = (float)(app->ScreenHeight() - size);
	}
	else if (app->GetKey(olc::UP).bHeld)
	{
		moving = true;

		y -= speed * fElapsedTime;
		if (y <= 0)
			y = 0;
	}


}

bool Player::IsMoving()
{
	return moving;
}

bool Player::OnUserCreate()
{
	std::cout << "\n    Player Initaiting: " << std::endl;

	x = (float)(app->ScreenWidth() / 2);
	y = (float)(app->ScreenHeight() / 2);

	size = 8;

	speed = 100;

	std::cout << "        Player Initaited " << std::endl;

	return true;
}

bool Player::OnUserUpdate(float fElapsedTime)
{
	moving = false;
	Move(fElapsedTime);
	Render();

	return true;
}