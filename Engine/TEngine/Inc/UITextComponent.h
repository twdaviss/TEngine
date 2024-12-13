#pragma once

#include "UIComponent.h"

namespace TEngine
{
	class UITextComponent : public UIComponent
	{
	public:
		SET_TYPE_ID(ComponentID::UIText);

		void Initialize() override;
		void Terminate() override;
		void Render() override;
		void Deserialize(const rapidjson::Value& value) override;
		void SetText(std::string text, Math::Vector2 position, float size, Color color) { mText = text; mPosition = position; mSize = size; mColor = color; }

	private:
		std::filesystem::path mText;
		Math::Vector2 mPosition = Math::Vector2::Zero;
		float mSize = 1.0f;
		Color mColor = Colors::Black;
	};
}