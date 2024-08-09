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

	TEngine::Graphics::ModelId mModelId;
	TEngine::Graphics::RenderGroup mCharacter;
	TEngine::Graphics::Animator mCharacterAnimator;

	TEngine::Graphics::StandardEffect mStandardEffect;

	int mAnimIndex = -1;
	bool mDrawSkeleton = false;
};

