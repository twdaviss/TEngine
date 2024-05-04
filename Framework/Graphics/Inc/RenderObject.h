#pragma once

#include "Material.h"
#include "MeshBuffer.h"
#include "TextureManager.h"
#include "Transform.h"

namespace TEngine::Graphics
{
	struct Model;
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
	};

	using RenderGroup = std::vector<RenderObject>;
	[[nodiscard]] RenderGroup CreateRenderGroup(const Model& model);
	void CleanupRenderGroup(RenderGroup& renderGroup);

	template<class Effect>
	void DrawRenderGroup(Effect& effect, const RenderGroup& renderGroup)
	{
		for (const RenderObject& renderObject : renderGroup)
		{
			effect.Render(renderObject);
		}
	}
}
