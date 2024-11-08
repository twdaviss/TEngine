#pragma once

#include "Component.h"

namespace TEngine
{
	class CameraComponent;
	
	class FPSCameraComponent final : public Component
	{
	public:
		SET_TYPE_ID(ComponentID::FPSCamera);

		void Initialize() override;
		void Terminate() override;
		void Update(float deltaTime) override;
		void Seriliaze(rapidjson::Document& doc, rapidjson::Value& value) override;
		void Deseriliaze(const rapidjson::Value& value) override;

	private:
		CameraComponent* mCameraComponent = nullptr;
		float mShiftSpeed = 10.0f;
		float mMoveSpeed = 1.0f;
		float mTurnSpeed = 0.1f;
	};
}