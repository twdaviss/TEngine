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
	void Render() override;
	void Update(float deltaTime) override;
	void SpawnTarget();
	void Shoot();
private:
	Graphics::UISprite mUISprite;
	CustomAimTrainerComponent mAimTrainerComponent;
	UITextComponent mTextComponent;

	TEngine::Color mColor = TEngine::Colors::White;
	uint32_t mSlices = 10.0;
	uint32_t mRings = 10.0;
	float mRadius = 1.0f;
	using Targets = GameObject*[10];
	Targets mTargets;
	bool initialized = false;
};

