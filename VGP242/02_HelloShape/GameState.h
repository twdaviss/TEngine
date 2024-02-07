#pragma once

#include <TEngine/Inc/TEngine.h>

class GameState : public TEngine::AppState
{
public:
	void Initialize();
	void Terminate();
	void Update(float deltaTime);
private:
	float mLifeTime = 0.0f;
};
