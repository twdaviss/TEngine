#pragma once

namespace TEngine
{
	class GameObject;
	class Component;

	using CustomMake = std::function<Component* (const std::string&, GameObject&)>;
	using CustomGet = std::function<Component* (const std::string&, GameObject&)>;

	namespace GameObjectFactory
	{
		void SetCustomMake(CustomMake customMake);
		void SetCustomGet(CustomGet customMake);

		void Make(const std::filesystem::path& templatePath, GameObject& gameObject);
		void OverrideDeserialize(const rapidjson::Value& value, GameObject& gameObject);
	}
}