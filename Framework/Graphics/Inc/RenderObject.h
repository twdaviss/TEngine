#pragma once

#include "Material.h"
#include "MeshBuffer.h"
#include "TextureManager.h"
#include "Transform.h"

namespace TEngine::Graphics
{
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
}
