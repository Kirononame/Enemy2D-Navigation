#include "App.h"


// The entry point for the app

int main()
{
	App *app = App::getInstance();

	if (app->Construct(122, 122, 5, 5))
		app->Start();

	return 0;
}