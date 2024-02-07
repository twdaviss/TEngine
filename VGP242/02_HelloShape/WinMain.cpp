#include <TEngine/Inc/TEngine.h>

#include "GameState.h"

using namespace TEngine;
using namespace TEngine::Graphics;

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	App& myApp = TEngine::MainApp();
	myApp.AddState<TriforceState>("TriforceState");
	myApp.AddState<PyramidState>("PyramidState");
	myApp.AddState<DiamondState>("DiamondState");


	AppConfig config;
	config.appName = L"Hello Shape";
	myApp.Run(config);

	myApp.Quit();
	return(0);
}