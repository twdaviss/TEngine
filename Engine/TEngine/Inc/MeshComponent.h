#pragma once

#include "RenderObjectComponent.h"

namespace TEngine
{
	class MeshComponent final : public RenderObjectComponent
	{
	public:
		SET_TYPE_ID(ComponentID::Mesh);

		void Deserialize(const rapidjson::Value& value) override;
		const Graphics::Model& GetModel() const override;
		void SetModelMesh(Graphics::Model::MeshData meshData, Graphics::Model::MaterialData matData);


	private:
		Graphics::Model mModel;
	};
}
