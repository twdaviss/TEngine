#include <TEngine/Inc/TEngine.h>

using namespace TEngine;

class MainState : public AppState
{
public:
	void Initialize()
	{
		LOG("MAIN STATE INITIALIZED");
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
			myApp.ChangeState("GameState");
		}
	}
private:
	float mLifeTime = 0.0f;
};

class GameState : public AppState
{
public:
	void Initialize()
	{
		LOG("GAME STATE INITIALIZED");
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
			myApp.ChangeState("MainState");
		}
	}
private:
	float mLifeTime = 0.0f;
};

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	App& myApp = TEngine::MainApp();
	myApp.AddState<MainState>("Main State");
	myApp.AddState<GameState>("Game State");

	AppConfig config;
	config.appName = L"Hello Window";
	config.winWidth = 1500;
	myApp.Run(config);

	myApp.Quit();
	return(0);
}