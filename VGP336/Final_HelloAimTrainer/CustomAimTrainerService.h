#pragma once

#include "CustomTypeIds.h"

class CustomAimTrainerComponent;

class CustomAimTrainerService : public TEngine::Service
{
public:
	SET_TYPE_ID(CustomServiceId::CustomAimTrainerTracker);
	void Initialize() override;
	void Render() override;
	
private:
	Graphics::UISprite mUISprite;
	CustomAimTrainerComponent mAimTrainerComponent;
};

