#include "Precompiled.h"
#include "UIButtonComponent.h"
#include "UISpriteComponent.h"

#include "GameWorld.h"
#include "UIRenderService.h"

using namespace TEngine;
using namespace TEngine::Graphics;
using namespace TEngine::Input;

void UIButtonComponent::Initialize()
{
	for (uint32_t i = 0; i < static_cast<uint32_t>(ButtonState::Count); ++i)
	{
		if (!mButtonStateTextures[i].empty())
		{
			mButtonStates[i].Initialize(mButtonStateTextures[i]);
		}
	}

	UIRenderService* uiRenderService = GetOwner().GetWorld().GetService<UIRenderService>();
	uiRenderService->Register(this);
}

void UIButtonComponent::Terminate()
{
	UIRenderService* uiRenderService = GetOwner().GetWorld().GetService<UIRenderService>();
	uiRenderService->Unregister(this);

	for (uint32_t i = 0; i < static_cast<uint32_t>(ButtonState::Count); ++i)
	{
		mButtonStates[i].Terminate();
	}
}

void UIButtonComponent::Update(float deltaTime)
{
	mCurrentState = ButtonState::Default;

	InputSystem* input = InputSystem::Get();
	const int mouseX = input->GetMouseScreenX();
	const int mouseY = input->GetMouseScreenY();
	if (mButtonStates[0].IsInSprite(mouseX, mouseY))
	{
		mCurrentState = ButtonState::Hover;
		if (input->IsMouseDown(MouseButton::LBUTTON))
		{
			mCurrentState = ButtonState::Click;
		}
		if (input->IsMousePressed(MouseButton::LBUTTON))
		{
			OnClick();
		}
	}
}

void UIButtonComponent::Render()
{
	uint32_t buttonState = static_cast<uint32_t>(mCurrentState);
	if (mButtonStateTextures[buttonState].empty())
	{
		buttonState = 0;
	}
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
	mButtonStates[buttonState].SetPosition(worldPosition);
	UISpriteRenderer::Get()->Render(&mButtonStates[buttonState]);
}

void UIButtonComponent::Deserialize(const rapidjson::Value& value)
{
	const uint32_t buttonCount = static_cast<uint32_t>(ButtonState::Count);
	if (value.HasMember("Position"))
	{
		auto pos = value["Position"].GetArray();
		mPosition.x = pos[0].GetFloat();
		mPosition.y = pos[1].GetFloat();
	}
	if (value.HasMember("Rotation"))
	{
		const float rotation = value["Rotation"].GetFloat();
		for (uint32_t i = 0; i < buttonCount; ++i)
		{
			mButtonStates[i].SetRotation(rotation);
		}
	}
	if (value.HasMember("Pivot"))
	{
		std::string pivot = value["Pivot"].GetString();
		Pivot buttonPivot = Pivot::TopLeft;
		if (pivot == "TopLeft")
		{
			buttonPivot = Pivot::TopLeft;
		}
		else if (pivot == "Top")
		{
			buttonPivot = Pivot::Top;
		}
		else if (pivot == "TopRight")
		{
			buttonPivot = Pivot::TopRight;
		}
		else if (pivot == "Left")
		{
			buttonPivot = Pivot::Left;
		}
		else if (pivot == "Center")
		{
			buttonPivot = Pivot::Center;
		}
		else if (pivot == "Right")
		{
			buttonPivot = Pivot::Right;
		}
		else if (pivot == "Bottom")
		{
			buttonPivot = Pivot::Bottom;
		}
		else if (pivot == "BottomRight")
		{
			buttonPivot = Pivot::BottomRight;
		}
		else
		{
			ASSERT(false, "UIButtonComponent: invalid pivot %s", pivot.c_str());
		}
		for (uint32_t i = 0; i < buttonCount; ++i)
		{
			mButtonStates[i].SetPivot(buttonPivot);
		}
	}
	for (uint32_t i = 0; i < buttonCount; ++i)
	{
		std::string buttonStateStr = "";
		ButtonState state = (ButtonState)i;
		switch (state)
		{
		case ButtonState::Default: buttonStateStr = "Default"; break;
		case ButtonState::Hover: buttonStateStr = "Hover"; break;
		case ButtonState::Click: buttonStateStr = "Click"; break;
		case ButtonState::Disabled: buttonStateStr = "Disabled"; break;
		default:
			break;
		}

		if (!value.HasMember(buttonStateStr.c_str()))
		{
			continue;
		}

		auto buttonStateObj = value[buttonStateStr.c_str()].GetObj();
		if (buttonStateObj.HasMember("Texture"))
		{
			mButtonStateTextures[i] = buttonStateObj["Texture"].GetString();
		}
		if (buttonStateObj.HasMember("Scale"))
		{
			auto scale = buttonStateObj["Scale"].GetArray();
			const float x = scale[0].GetFloat();
			const float y = scale[1].GetFloat();
			mButtonStates[i].SetScale({ x,y });
		}
		if (buttonStateObj.HasMember("Color"))
		{
			auto color = buttonStateObj["Color"].GetArray();
			const float r = color[0].GetFloat();
			const float g = color[1].GetFloat();
			const float b = color[2].GetFloat();
			const float a = color[3].GetFloat();
			mButtonStates[i].SetColor({ r,g,b,a });
		}
		if (buttonStateObj.HasMember("Flip"))
		{
			std::string flip = buttonStateObj["Flip"].GetString();
			if (flip == "None")
			{
				mButtonStates[i].SetFlip(Flip::None);
			}
			else if (flip == "Horizontal")
			{
				mButtonStates[i].SetFlip(Flip::Horizontal);
			}
			else if (flip == "Vertical")
			{
				mButtonStates[i].SetFlip(Flip::Vertical);
			}
			else if (flip == "Both")
			{
				mButtonStates[i].SetFlip(Flip::Both);
			}
			else 
			{
				ASSERT(false, "UIButtonComponent: invalid flip %s", flip.c_str());
			}
		}
	}
}

Math::Vector2 UIButtonComponent::GetPosition(bool includeOrigin)
{
	float x = 0.0f;
	float y = 0.0f;
	if (includeOrigin)
	{
		mButtonStates[0].GetOrigin(x, y);
	}
	return { mPosition.x - x, mPosition.y - y };
}

void UIButtonComponent::SetCallback(ButtonCallback cb)
{
	mCallback = cb;
}

void UIButtonComponent::OnClick()
{
	LOG("BUTTON WAS CLICKED!!!");
	if (mCallback != nullptr)
	{
		mCallback();
	}
}
