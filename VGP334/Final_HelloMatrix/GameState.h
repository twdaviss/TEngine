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

	TEngine::Graphics::RenderObject mGround;
	TEngine::Graphics::RenderObject mSkybox;

	TEngine::Graphics::ModelId mAgentModelId;
	TEngine::Graphics::ModelId mNeoModelId;
	TEngine::Graphics::ModelId mTrinityModelId;

	TEngine::Graphics::RenderGroup mAgent;
	TEngine::Graphics::RenderGroup mNeo;
	TEngine::Graphics::RenderGroup mTrinity;

	TEngine::Graphics::Animator mAgentAnimator;
	TEngine::Graphics::Animator mNeoAnimator;
	TEngine::Graphics::Animator mTrinityAnimator;

	TEngine::Graphics::StandardEffect mStandardEffect;

	TEngine::ListenerId mSpaceEventId = 0;
	TEngine::ListenerId mAnimEventId = 0;

	std::vector<TEngine::Audio::SoundId> mEventSoundIds;
	TEngine::Graphics::Animation mAgentAnimation;
	TEngine::Graphics::Animation mNeoAnimation;
	TEngine::Graphics::Animation mTrinityAnimation;

	TEngine::Graphics::Animation mCameraAnimation;

	Vector3 lookTarget;

	float mEventAnimationTime = 0.0f;

	int mAnimIndex = -1;
	bool mDrawSkeleton = false;
	bool slowMoEnabled = false;
};

