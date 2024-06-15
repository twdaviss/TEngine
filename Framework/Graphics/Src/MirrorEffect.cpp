#include "Precompiled.h"
#include "MirrorEffect.h"

using namespace TEngine;
using namespace TEngine::Graphics;

void MirrorEffect::Initialize()
{
	constexpr uint32_t depthMapResolution = 4096;
	mMirrorRenderTarget.Initialize(depthMapResolution, depthMapResolution, Texture::Format::RGBA_U32);
}

void MirrorEffect::Terminate()
{
	mMirrorRenderTarget.Terminate();
}

void MirrorEffect::Begin()
{
	mMirrorRenderTarget.BeginRender();
}

void MirrorEffect::End()
{
	mMirrorRenderTarget.EndRender();
}

void MirrorEffect::Render(const RenderObject& renderObject)
{

}

void MirrorEffect::DebugUI()
{
	if (ImGui::CollapsingHeader("MirrorEffect", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::Text("MirrorTexture");
		ImGui::Image(
			mMirrorRenderTarget.GetRawData(),
			{ 144,144 },
			{ 0,0 },
			{ 1,1 },
			{ 1,1,1,1 },
			{ 1,1,1,1 });
		ImGui::DragFloat("Size##Mirror", &mSize, 1.0f, 1.0f, 1000.0f);
	}
}

void MirrorEffect::SetFocus(const Math::Vector3& focusPosition)
{
}

void MirrorEffect::SetSize(float size)
{
	mSize = size;
}

const Texture& MirrorEffect::GetMirrorImage() const
{
	return mMirrorRenderTarget;
}
