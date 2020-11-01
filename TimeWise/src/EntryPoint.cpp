#include "Soul/Soul.h"

#include "Client.h"

int main()
{
	Soul::Application* app = new Client();
	app->Run();
	delete app;
}