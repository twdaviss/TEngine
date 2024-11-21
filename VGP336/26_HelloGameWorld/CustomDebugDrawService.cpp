#include "CustomDebugDrawService.h"

#include "CustomDebugDrawComponent.h"

using namespace TEngine;
using namespace TEngine::Graphics;
using namespace TEngine::Math;

void CustomDebugDrawService::Render()
{
	for (CustomDebugDrawComponent* debugDrawCompoent : mCustomDebugDrawComponents)
	{
		debugDrawCompoent->AddDebugDraw();
	}
}

void CustomDebugDrawService::Register(CustomDebugDrawComponent* debugDrawComponent)
{
	auto iter = std::find(mCustomDebugDrawComponents.begin(), mCustomDebugDrawComponents.end(), debugDrawComponent);
	if (iter == mCustomDebugDrawComponents.end())
	{
		mCustomDebugDrawComponents.push_back(debugDrawComponent);
	}
}

void CustomDebugDrawService::Unregister(CustomDebugDrawComponent* debugDrawComponent)
{
	auto iter = std::find(mCustomDebugDrawComponents.begin(), mCustomDebugDrawComponents.end(), debugDrawComponent);
	if (iter != mCustomDebugDrawComponents.end())
	{
		mCustomDebugDrawComponents.erase(iter);
	}
}
