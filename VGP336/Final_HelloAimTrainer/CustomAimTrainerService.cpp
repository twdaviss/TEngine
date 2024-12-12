#include "CustomAimTrainerService.h"
#include "CustomAimTrainerComponent.h"

using namespace TEngine;
using namespace TEngine::Graphics;
using namespace TEngine::Math;

void CustomAimTrainerService::Initialize()
{
	UIRenderService* renderService = GetOwner().GetWorld().GetService<UIRenderService>();
	renderService->Register(this);
}

void CustomAimTrainerService::Terminate()
{
	UIRenderService* renderService = GetOwner().GetWorld().GetService<UIRenderService>();
	renderService->Unregister(this);
}

void CustomAimTrainerService::Render()
{
	std::wstring text(L"Accuracy:");
	UIFont::Get()->DrawString(text.c_str(), {200,200}, 24, {1.0,1.0,1.0,1.0});
}

