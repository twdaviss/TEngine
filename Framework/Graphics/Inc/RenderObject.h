#pragma once

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

		TextureId diffuseTextureId;
	};
}
