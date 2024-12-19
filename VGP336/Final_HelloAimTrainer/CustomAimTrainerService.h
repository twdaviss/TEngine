#pragma once

#include "CustomTypeIds.h"
#include "CustomAimTrainerComponent.h"

class CustomAimTrainerComponent;

class CustomAimTrainerService : public TEngine::Service
{
public:
	SET_TYPE_ID(CustomServiceId::CustomAimTrainerTracker);

	void CustomInitialize();
	void Terminate() override;
	void Update(float deltaTime) override;
	void SpawnTarget();
	void Shoot();
private:
	Graphics::UISprite mUISprite;
	CustomAimTrainerComponent mAimTrainerComponent;
	UITextComponent mTextComponent;
	
	GameObject* mTarget;
	bool initialized = false;
	TEngine::Color mColor = TEngine::Colors::White;
	uint32_t mSlices = 10.0;
	uint32_t mRings = 10.0;
	float mRadius = 1.0f;
	int mHits = 0;
	int mMisses = 0;
	int mTotalShots = 0;
	float mLifeTime = 2.0f;
	float mCurrentLife = 0.0f;
	float mTotalTime = 0;
	float mAvgTime = 0;
	int mTotalTargets = 0;
};

