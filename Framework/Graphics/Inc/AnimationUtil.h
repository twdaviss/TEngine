#pragma once

#include "ModelManager.h"

namespace TEngine::Graphics
{
	class Animator;
	namespace AnimationUtil
	{
		using BoneTransforms = std::vector<Math::Matrix4>;

		void ComputeBoneTransforms(ModelId id, BoneTransforms& boneTransforms, const Animator* animator = nullptr);
		void ApplyBoneOffsets(ModelId id, BoneTransforms& boneTransforms);
		void DrawSkeleton(ModelId id, const BoneTransforms& boneTransforms);
	}
}