#pragma once

#include "TEngine/Inc/TEngine.h"

enum class CustomComponentId
{
	CustomDebugDraw = static_cast<uint32_t>(TEngine::ComponentID::Count)
};

enum class CustomServiceId
{
	CustomDebugDrawDisplay = static_cast<uint32_t>(TEngine::ServiceID::Count)
};
