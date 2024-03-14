#pragma once

#include <TEngine/Inc/TEngine.h>

enum class Shape
{
	Transform, 
	Sphere, 
	Aabb, 
	Aabbfilled,
	Lines
};

class GameState : public TEngine::AppState
{
public:
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render() override;

protected:
	TEngine::Graphics::Camera mCamera;
	Shape currentShape;
};
