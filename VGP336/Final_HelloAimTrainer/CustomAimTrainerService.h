#pragma once

#include "CustomTypeIds.h"
#include "CustomAimTrainerComponent.h"

class CustomAimTrainerComponent;

class CustomAimTrainerService : public TEngine::Service
{
public:
	SET_TYPE_ID(CustomServiceId::CustomAimTrainerTracker);
	void Initialize() override;
	void Terminate() override;
	void Render() override;
	void Update(float deltaTime) override;
	void Shoot();
private:
	Graphics::UISprite mUISprite;
	CustomAimTrainerComponent mAimTrainerComponent;
	UITextComponent mTextComponent;

};

