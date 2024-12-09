#pragma once

#include "Component.h"

namespace TEngine
{
	class CameraComponent;
	
	class StationaryCameraComponent final : public Component
	{
	public:
		SET_TYPE_ID(ComponentID::StationaryCamera);

		void Initialize() override;
		void Terminate() override;
		void Update(float deltaTime) override;
		void Serialize(rapidjson::Document& doc, rapidjson::Value& value) override;
		void Deserialize(const rapidjson::Value& value) override;

	private:
		CameraComponent* mCameraComponent = nullptr;
		float mTurnSpeed = 0.1f;
	};
}