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
	TEngine::Graphics::DirectionalLight mDirectionalLight;
	TEngine::Graphics::Camera mCamera;
	TEngine::Graphics::StandardEffect mStandardEffect;

	TEngine::Graphics::RenderObject mGround;
	TEngine::Graphics::RenderObject mBall;

	TEngine::Graphics::Animation mAnimation;
	float mAnimationTime = 0.0f;

};

