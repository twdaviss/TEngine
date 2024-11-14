#pragma once

namespace TEngine
{
	class GameObject;
	namespace GameObjectFactory
	{
		void Make(const std::filesystem::path& templatePath, GameObject& gameObject);
		void OverrideDeserialize(const rapidjson::Value& value, GameObject& gameObject);
	}
}