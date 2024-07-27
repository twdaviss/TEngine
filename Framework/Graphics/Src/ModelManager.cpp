#include "Precompiled.h"
#include "ModelManager.h"

#include "ModelIO.h"

using namespace TEngine;
using namespace TEngine::Graphics;


namespace
{
	std::unique_ptr<ModelManager> sModelManager;
}

void ModelManager::StaticInitialize()
{
	ASSERT(sModelManager == nullptr, "ModelManager: is already initialized");
	sModelManager = std::make_unique<ModelManager>();
}

void ModelManager::StaticTerminate()
{
	sModelManager.reset();
}

ModelManager* ModelManager::Get()
{
	ASSERT(sModelManager != nullptr, "ModelManager: is not initialized");
	return sModelManager.get();
}

ModelId ModelManager::GetModelId(const std::filesystem::path& filePath)
{
	return std::filesystem::hash_value(filePath);
}

ModelId ModelManager::LoadModelId(const std::filesystem::path& filePath)
{
	const ModelId modelId = GetModelId(filePath);
	auto [iter, success] = mInventory.insert({ modelId, nullptr });
	if (success)
	{
		auto& modelPtr = iter->second;
		modelPtr = std::make_unique<Model>();
		ModelIO::LoadModel(filePath, *modelPtr);
		ModelIO::LoadMaterial(filePath, *modelPtr);
		ModelIO::LoadSkeleton(filePath, *modelPtr);
	}
	return modelId;
}

const Model* ModelManager::GetModel(ModelId id) const
{
	auto model = mInventory.find(id);
	if (model != mInventory.end())
	{
		return model->second.get();
	}
	return nullptr;
}
