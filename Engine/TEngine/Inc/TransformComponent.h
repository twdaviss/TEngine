#pragma once

#include "Component.h"

namespace TEngine
{
	class TransformComponent final : public Component, public Graphics::Transform
	{
	public:
		SET_TYPE_ID(ComponentID::Transform);

		void DebugUI() override;
		void Seriliaze(rapidjson::Document& doc, rapidjson::Value& value) override;
		void Deseriliaze(const rapidjson::Value& value) override;
	};
}
