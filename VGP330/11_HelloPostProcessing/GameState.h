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

	//Effects
	TEngine::Graphics::StandardEffect mStandardEffect;
	TEngine::Graphics::PostProcessingEffect mPostProcessingEffect;
	
	//Objects
	TEngine::Graphics::RenderGroup mCharacter;
	TEngine::Graphics::RenderGroup mCharacter2;
	TEngine::Graphics::RenderObject mGround;
	TEngine::Graphics::RenderObject mScreenQuad;

	TEngine::Graphics::Texture mCombineTexture;

	//Render Targets
	TEngine::Graphics::RenderTarget mRenderTarget;
};

