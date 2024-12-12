#pragma once

#include "TEngine/Inc/TEngine.h"

enum class CustomComponentId
{
	CustomAimTrainer = static_cast<uint32_t>(TEngine::ComponentID::Count)
};

enum class CustomServiceId
{
	CustomAimTrainerTracker = static_cast<uint32_t>(TEngine::ServiceID::Count)
};
