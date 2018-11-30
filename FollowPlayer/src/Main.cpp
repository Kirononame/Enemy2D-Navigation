#include "App.h"

int main()
{
	App *app = App::getInstance();

	if (app->Construct(130, 130, 5, 5))
		app->Start();

	return 0;
}