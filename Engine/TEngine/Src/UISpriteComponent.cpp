#include "Precompiled.h"
#include "UISpriteComponent.h"
#include "UIButtonComponent.h"

#include "GameWorld.h"
#include "UIRenderService.h"

using namespace TEngine;
using namespace TEngine::Graphics;

void UISpriteComponent::Initialize()
{
	ASSERT(!mTexturePath.empty(), "UISpriteComponent: texture path is not set");
	mUISprite.Initialize(mTexturePath);
	if (mRect.right - mRect.left > 0)
	{
		mUISprite.SetRect(mRect.top, mRect.left, mRect.right, mRect.bottom);
	}
	UIRenderService* renderService = GetOwner().GetWorld().GetService<UIRenderService>();
	renderService->Register(this);
}

void UISpriteComponent::Terminate()
{
	UIRenderService* renderService = GetOwner().GetWorld().GetService<UIRenderService>();
	renderService->Unregister(this);
	mUISprite.Terminate();
}

void UISpriteComponent::Render()
{
	Math::Vector2 worldPosition = GetPosition(false);
	GameObject* parent = GetOwner().GetParent();
	while (parent != nullptr)
	{
		UISpriteComponent* spriteComponent = parent->GetComponent<UISpriteComponent>();
		if (spriteComponent != nullptr)
		{
			worldPosition += spriteComponent->GetPosition();
		}
		else 
		{
			UIButtonComponent* uiButtonComponent = parent->GetComponent<UIButtonComponent>();
			if (uiButtonComponent != nullptr)
			{
				worldPosition += uiButtonComponent->GetPosition();
			}
		}
		parent = parent->GetParent();
	}
	mUISprite.SetPosition({ worldPosition.x, worldPosition.y });
	UISpriteRenderer::Get()->Render(&mUISprite);
}

void UISpriteComponent::Deserialize(const rapidjson::Value& value)
{
	if (value.HasMember("Texture"))
	{
		mTexturePath = value["Texture"].GetString();
	}
	if (value.HasMember("Position"))
	{
		auto pos = value["Position"].GetArray();
		const float x = pos[0].GetFloat();
		const float y = pos[1].GetFloat();
		mUISprite.SetPosition({ x,y });
	}
	if (value.HasMember("Scale"))
	{
		auto scale = value["Scale"].GetArray();
		const float x = scale[0].GetFloat();
		const float y = scale[1].GetFloat();
		mUISprite.SetScale({ x,y });
	}
	if (value.HasMember("Color"))
	{
		auto color = value["Color"].GetArray();
		const float r = color[0].GetFloat();
		const float g = color[1].GetFloat();
		const float b = color[2].GetFloat();
		const float a = color[3].GetFloat();

		mUISprite.SetColor({ r,g,b,a });
	}
	if (value.HasMember("Rotation"))
	{
		const float rotation = value["Rotation"].GetFloat();
		mUISprite.SetRotation(rotation);
	}
	if (value.HasMember("Pivot"))
	{
		std::string pivot = value["Pivot"].GetString();
		if (pivot == "TopLeft")
		{
			mUISprite.SetPivot(Pivot::TopLeft);
		}
		else if (pivot == "Top")
		{
			mUISprite.SetPivot(Pivot::Top);
		}
		else if (pivot == "TopRight")
		{
			mUISprite.SetPivot(Pivot::TopRight);
		}
		else if (pivot == "Left")
		{
			mUISprite.SetPivot(Pivot::Left);
		}
		else if (pivot == "Center")
		{
			mUISprite.SetPivot(Pivot::Center);
		}
		else if (pivot == "Right")
		{
			mUISprite.SetPivot(Pivot::Right);
		}
		else if (pivot == "BottomLeft")
		{
			mUISprite.SetPivot(Pivot::BottomLeft);
		}
		else if (pivot == "Bottom")
		{
			mUISprite.SetPivot(Pivot::Bottom);
		}
		else if (pivot == "BottomRight")
		{
			mUISprite.SetPivot(Pivot::BottomRight);
		}
		else {
			ASSERT(false, "UISpriteComponent: invalid pivot %s", pivot.c_str());
		}
	}
	if (value.HasMember("Flip"))
	{
		std::string flip = value["Flip"].GetString();
		if (flip == "None")
		{
			mUISprite.SetFlip(Flip::None);
		}
		else if (flip == "Vertical")
		{
			mUISprite.SetFlip(Flip::Vertical);
		}
		else if (flip == "Horizontal")
		{
			mUISprite.SetFlip(Flip::Horizontal);
		}
		else if (flip == "Both")
		{
			mUISprite.SetFlip(Flip::Both);
		}
		else {
			ASSERT(false, "UISpriteComponent: invalid flip %s", flip.c_str());
		}
	}
	if (value.HasMember("Rect"))
	{
		auto rect = value["Rect"].GetArray();
		mRect.top = rect[0].GetInt();
		mRect.left = rect[1].GetInt();
		mRect.right = rect[2].GetInt();
		mRect.bottom = rect[3].GetInt();
	}
}

Math::Vector2 TEngine::UISpriteComponent::GetPosition(bool includeOrigin)
{
	float x = 0.0f;
	float y = 0.0f;
	if (includeOrigin)
	{
		mUISprite.GetOrigin(x, y);
	}
	return { mPosition.x - x, mPosition.y - y };
}
