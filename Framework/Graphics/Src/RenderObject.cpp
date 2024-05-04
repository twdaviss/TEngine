#include "Precompiled.h"
#include "RenderObject.h"
#include "Model.h"

using namespace TEngine;
using namespace TEngine::Graphics;

void RenderObject::Terminate()
{
	meshBuffer.Terminate();
}
RenderGroup Graphics::CreateRenderGroup(const Model& model)
{
	RenderGroup renderGroup;
	renderGroup.reserve(model.meshData.size());
	for (const Model::MeshData& meshData : model.meshData)
	{
		RenderObject& renderObject = renderGroup.emplace_back();
		renderObject.meshBuffer.Initialize(meshData.mesh);
		if (meshData.materialIndex < model.materialData.size())
		{
			//material data
		}
	}
	return renderGroup;
}

void Graphics::CleanupRenderGroup(RenderGroup& renderGroup)
{
	for (RenderObject& renderObject : renderGroup)
	{
		renderObject.Terminate();
	}
}