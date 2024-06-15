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
	TEngine::Graphics::Camera mMirrorCamera;

	//Effects
	TEngine::Graphics::StandardEffect mStandardEffect;
	TEngine::Graphics::ShadowEffect mShadowEffect;
	TEngine::Graphics::TerrainEffect mTerrainEffect;
	TEngine::Graphics::MirrorEffect mMirrorEffect;

	//Objects
	TEngine::Graphics::Terrain mTerrain;
	TEngine::Graphics::RenderGroup mCharacter;
	TEngine::Graphics::RenderGroup mCharacter2;
	TEngine::Graphics::RenderObject mGround;
	TEngine::Graphics::RenderObject mMirror;

	bool mOnTerrain = true;
};

