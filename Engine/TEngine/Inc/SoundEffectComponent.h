#pragma once

#include "Component.h"

namespace TEngine
{
	class SoundEffectComponent final : public Component
	{
	public:
		SET_TYPE_ID(ComponentID::SoundEffect);

		void Initialize() override;
		void Terminate() override;
		void DebugUI() override;

		void Serialize(rapidjson::Document& doc, rapidjson::Value& value) override;
		void Deserialize(const rapidjson::Value& value) override;

		void Play();
		void Stop();
	private:
		std::string mFileName;
		bool mLooping = false;
		Audio::SoundId mSoundId;
	};
}
