#include <TEngine/Inc/TEngine.h>

using namespace TEngine;
using namespace TEngine::Graphics;

class MainState : public AppState
{
public:
	void Initialize()
	{
		LOG("MAIN STATE INITIALIZED");
		GraphicsSystem::Get()->SetClearColor(Colors::Red);
		mLifeTime = 2.0f;
	}
	void Terminate()
	{
		LOG("MAIN STATE TERMINATED");
	}
	void Update(float deltaTime)
	{
		mLifeTime -= deltaTime;
		if (mLifeTime <= 0.0f)
		{
			App& myApp = TEngine::MainApp();
			myApp.ChangeState("Game State");
		}
	}
private:
	float mLifeTime = 0.0f;
};

class SolarSystem : public AppState
{
public:
	void Initialize()
	{
		LOG("GAME STATE INITIALIZED");
		GraphicsSystem::Get()->SetClearColor(Colors::Blue);
		mLifeTime = 2.0f;
	}
	void Terminate()
	{
		LOG("GAME STATE TERMINATED");
	}
	void Update(float deltaTime)
	{
		mLifeTime -= deltaTime;
		if (mLifeTime <= 0.0f)
		{
			App& myApp = TEngine::MainApp();
			myApp.ChangeState("Main State");
		}
	}
private:
	float mLifeTime = 0.0f;
};

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	App& myApp = TEngine::MainApp();
	myApp.AddState<MainState>("Main State");
	myApp.AddState<SolarSystem>("Game State");


	AppConfig config;
	config.appName = L"Hello Window";
	config.winWidth = 1500;
	myApp.Run(config);

	myApp.Quit();
	return(0);
}