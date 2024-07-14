#pragma once

#include "Animation.h"

namespace TEngine::Graphics
{
	class AnimationBuilder
	{
	public:
		AnimationBuilder& AddPositionKey(const Math::Vector3& pos, float time, EaseType easetype = EaseType::Linear);
		AnimationBuilder& AddRotationKey(const Math::Quaternion& rot, float time, EaseType easetype = EaseType::Linear);
		AnimationBuilder& AddScaleKey(const Math::Vector3& scale, float time, EaseType easetype = EaseType::Linear);

		[[nodiscard]] Animation Build();
	private:
		Animation mWorkingCopy;
	};
}