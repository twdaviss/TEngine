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
	void OnEvent2();
	void OnEvent3();

	void OnSpaceEvent(const TEngine::Event* event);
	void OnAnimEvent(const TEngine::Event* event);

	TEngine::Graphics::DirectionalLight mDirectionalLight;
	TEngine::Graphics::Camera mCamera;

	TEngine::Graphics::ModelId mModelId;
	TEngine::Graphics::RenderGroup mCharacter;
	TEngine::Graphics::Animator mCharacterAnimator;
	TEngine::Graphics::StandardEffect mStandardEffect;

	TEngine::ListenerId mSpaceEventId = 0;
	TEngine::ListenerId mAnimEventId = 0;

	std::vector<TEngine::Audio::SoundId> mEventSoundIds;
	TEngine::Graphics::Animation mEventAnimation;
	float mEventAnimationTime = 0.0f;

	int mAnimIndex = -1;
	bool mDrawSkeleton = false;
};

