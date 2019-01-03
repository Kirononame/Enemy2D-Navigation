#include <iostream>
#include <math.h>
#include <string.h>

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

void Enemy::SetX(float num)
{
	x = num;
}

void Enemy::SetY(float num)
{
	y = num;
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
	if (ssMoving)
	{
		bool next = true;

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
			//if (x >= app->ScreenWidth() - size)
				//x = (float)(app->ScreenWidth() - size);

			next = false;
		}

		// left >
		if ((x - xDest) > EEPSILON)
		{
			moving = true;
			x -= speed * fElapsedTime;
			//if (x <= 0)
				//x = 0;

			next = false;
		}

		// down <
		if ((y - yDest) < -EEPSILON)
		{
			moving = true;
			y += speed * fElapsedTime;
			//if (y >= app->ScreenHeight() - size)
				//y = (float)(app->ScreenHeight() - size);

			next = false;
		}

		// up >
		if ((y - yDest) > EEPSILON)
		{
			moving = true;
			y -= speed * fElapsedTime;
			//if (y <= 0)
				//y = 0;

			next = false;
		}

		if(next)
		{
			app->path->NextNode();
		}

	}

}

bool Enemy::IsMoving()
{
	return moving;
}

bool Enemy::OnUserCreate()
{
	std::cout << "\n    Enemy Initaiting: " << std::endl;

	x = (float)(app->ScreenWidth() / 4);
	y = (float)(app->ScreenHeight() / 4);

	size = 8;

	speed = 20;

	std::cout << "        Enemy Initaited" << std::endl;

	return true;
}

bool Enemy::OnUserUpdate(float fElapsedTime)
{
	if (app->GetKey(olc::M).bPressed)
		ssMoving = !ssMoving;
	else if (app->GetKey(olc::Q).bPressed)
	{
		speed -= 5;
		if (speed <= 0)
			speed = 0;
	}
	else if (app->GetKey(olc::W).bPressed)
	{
		speed += 5;
		if (speed >= 100)
			speed = 100;
	}

	if (ssMoving)
	{
		//void DrawString(int32_t x, int32_t y, std::string sText,
		//Pixel col = olc::WHITE, uint32_t scale = 1);

		app->DrawString(5, 3, "Moving",
			olc::WHITE, 1);
	}

	else
	{
		//void DrawString(int32_t x, int32_t y, std::string sText,
		//Pixel col = olc::WHITE, uint32_t scale = 1);

		app->DrawString(5, 3, "Standing",
			olc::WHITE, 1);
	}

	std::string s = std::to_string(speed);
	app->DrawString(100, 3, s,
		olc::WHITE, 1);
		

	moving = false;
	Move(fElapsedTime);
	Render();

	return true;
}