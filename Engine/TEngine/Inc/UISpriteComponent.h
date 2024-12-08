#pragma once

#include "UIComponent.h"

namespace TEngine
{
	class UISpriteComponent : public UIComponent
	{
	public:
		SET_TYPE_ID(ComponentID::UISprite);

		void Initialize() override;
		void Terminate() override;
		void Render() override;
		void Deserialize(const rapidjson::Value& value) override;

	private:
		std::filesystem::path mTexturePath;
		Graphics::UISprite mUISprite;
	};
}