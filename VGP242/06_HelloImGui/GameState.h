#pragma once

#include <TEngine/Inc/TEngine.h>

class GameState : public TEngine::AppState
{
public:
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render() override;
	void DebugUI() override;

protected:
	TEngine::Graphics::Camera mCamera;
	float mSphereAlpha = 1.0f;
	Math::Vector3 mPosition = Math::Vector3::Zero;
};
