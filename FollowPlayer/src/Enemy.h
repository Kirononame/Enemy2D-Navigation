#pragma once

#include "App.h"

class App;


class Enemy
{
private:

	float x;
	float y;

	int size;

	int speed;

	bool moving = false;

public:
	Enemy();
	App* app;

public:
	void Render();
	void Move(float fElapsedTime);

	float GetX();
	float GetY();

	bool IsMoving();

	bool OnUserCreate();
	bool OnUserUpdate(float fElapsedTime);

};