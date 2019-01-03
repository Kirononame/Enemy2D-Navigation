#pragma once

#include "App.h"

class App;

class Player
{
private:

	float x;
	float y;

	int size;

	int speed;

	bool moving = false;

public:
	Player();
	App* app;

public:
	void Render();
	void Move(float fElapsedTime);

	float GetX();
	float GetY();

	void SetX(float num);
	void SetY(float num);

	int GetSize();

	bool IsMoving();

	bool OnUserCreate();
	bool OnUserUpdate(float fElapsedTime);

};
