#include "Precompiled.h"
#include "AnimationBuilder.h"

using namespace TEngine;
using namespace TEngine::Graphics;

namespace
{
	template<class T>
	inline void PushKey(Keyframes<T>& keyFrames, const T& value, float t, EaseType e)
	{
		ASSERT(keyFrames.empty() || keyFrames.back().time <= t, "AnimationBuilder: cannot add keyframe back in time");
		keyFrames.emplace_back(value, t, e);
	}
}

AnimationBuilder& AnimationBuilder::AddPositionKey(const Math::Vector3& pos, float time, EaseType easetype)
{
	PushKey(mWorkingCopy.mPositionKeys, pos, time, easetype);
	mWorkingCopy.mDuration = Math::Max(mWorkingCopy.mDuration, time);
	return *this;
}

AnimationBuilder& AnimationBuilder::AddRotationKey(const Math::Quaternion& rot, float time, EaseType easetype)
{
	PushKey(mWorkingCopy.mRotationKeys, rot, time, easetype);
	mWorkingCopy.mDuration = Math::Max(mWorkingCopy.mDuration, time);
	return *this;
}

AnimationBuilder& AnimationBuilder::AddScaleKey(const Math::Vector3& scale, float time, EaseType easetype)
{
	PushKey(mWorkingCopy.mScaleKeys, scale, time, easetype);
	mWorkingCopy.mDuration = Math::Max(mWorkingCopy.mDuration, time);
	return *this;
}

AnimationBuilder& AnimationBuilder::AddEventKey(AnimationCallback cb, float time)
{
	PushKey(mWorkingCopy.mEventKeys, cb, time, EaseType::Linear);
	mWorkingCopy.mDuration = Math::Max(mWorkingCopy.mDuration, time);
	return *this;
}

Animation AnimationBuilder::Build()
{
	ASSERT(!mWorkingCopy.mPositionKeys.empty()
		|| !mWorkingCopy.mRotationKeys.empty()
		|| !mWorkingCopy.mScaleKeys.empty()
		|| !mWorkingCopy.mEventKeys.empty(),
		"AnimationBuilder: no animation keys were added");
	return std::move(mWorkingCopy);
}
