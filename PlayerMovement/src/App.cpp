#define OLC_PGE_APPLICATION
#include "Engine.h"
#include <iostream>

using namespace std;

namespace game
{
	class Player : public olc::PixelGameEngine
	{
	public:
		Player()
		{
			sAppName = "PLayer Movement";
		}

	public:
		bool OnUserCreate() override
		{
			x = (float) (ScreenWidth() / 2);
			y = (float) (ScreenHeight() / 2);

			size = 5;

			speed = 100;

			xx = 10;


			return true;
		}

		bool OnUserUpdate(float fElapsedTime) override
		{
			Move(fElapsedTime);
			
			Render();

			/*FillRect(0, 0, ScreenWidth(), ScreenHeight(), olc::BLACK);

			xx += 10 * fElapsedTime;
			FillRect(xx, 10, 2, 2, olc::GREEN);*/
					
			return true;
		}

	private:

		float x;
		float y;

		int xx;

		int size;

		int speed;
	
	private:

		void Render()
		{
			FillRect(0, 0, ScreenWidth(), ScreenHeight(), olc::BLACK);

			FillRect((int)x, (int)y, size, size, olc::GREEN);;
		}

		void Move(float fElapsedTime)
		{
			
			if (GetKey(olc::RIGHT).bHeld)
			{
				
				x += speed * fElapsedTime;
				if (x >= ScreenWidth() - size)
					x = (float) (ScreenWidth() - size);
				
			} 

			else if (GetKey(olc::LEFT).bHeld)
			{
				x -= speed * fElapsedTime;
				if (x <= 0)			
					x = 0;
			}

			if (GetKey(olc::DOWN).bHeld)
			{
				y += speed * fElapsedTime;
				if (y >= ScreenHeight() - size)
					y = (float) (ScreenHeight() - size);
			}
			else if (GetKey(olc::UP).bHeld)
			{
				y -= speed * fElapsedTime;
				if (y <= 0)
					y = 0;
			}

			cout << "x: " << x << " " << endl;
			cout << "y: " << y << " " << endl;

		}

	};

}



int main()
{
	game::Player player;
	if (player.Construct(150, 150, 4, 4))
		player.Start();

	return 0;
}