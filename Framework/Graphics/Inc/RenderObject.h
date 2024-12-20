#pragma once

#include "Material.h"
#include "MeshBuffer.h"
#include "ModelManager.h"
#include "TextureManager.h"
#include "Transform.h"

namespace TEngine::Graphics
{
	struct Model;
	class Animator;

	struct RenderObject
	{
		void Terminate();

		Transform transform;
		MeshBuffer meshBuffer;

		Material material;

		TextureId diffuseMapId;
		TextureId normalMapId;
		TextureId specMapId;
		TextureId bumpMapId;

		ModelId modelId;
		const Skeleton* skeleton = nullptr;
		const Animator* animator = nullptr;
	};

	using RenderGroup = std::vector<RenderObject>;
	[[nodiscard]] RenderGroup CreateRenderGroup(ModelId modelId, const Animator* animator = nullptr);
	[[nodiscard]] RenderGroup CreateRenderGroup(const Model& model, ModelId modelId = 0, const Animator* animator = nullptr);

	void CleanupRenderGroup(RenderGroup& renderGroup);

	void SetRenderGroupPosition(RenderGroup& renderGroup, const Math::Vector3& pos);

	void SetRenderGroupRotation(RenderGroup& renderGroup, const Math::Quaternion& rot);

	void SetRenderGroupScale(RenderGroup& renderGroup, const Math::Vector3 v);

	template<class Effect>
	void DrawRenderGroup(Effect& effect, const RenderGroup& renderGroup)
	{
		for (const RenderObject& renderObject : renderGroup)
		{
			effect.Render(renderObject);
		}
	}
}
