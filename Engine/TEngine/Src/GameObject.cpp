#include "Precompiled.h"
#include "GameObject.h"

using namespace TEngine;

static uint32_t gUniqueID = 0;

void GameObject::Initialize()
{
	ASSERT(!mInitialized, "GameObject: is already initialized");

	for (auto& component : mComponents)
	{
		component->Initialize();
	}

	mUniqueID = ++gUniqueID;
	mInitialized = true;
}

void GameObject::Terminate()
{
	for (auto& component : mComponents)
	{
		component->Terminate();
		component.reset();
	}
	mComponents.clear();
}

void GameObject::Update(float deltaTime)
{
	for (auto& component : mComponents)
	{
		component->Update(deltaTime);
	}
}

void GameObject::DebugUI()
{
	ImGui::PushID(mUniqueID);
	if (ImGui::CollapsingHeader(mName.c_str()))
	{
		for (auto& component : mComponents)
		{
			component->DebugUI();
		}
	}
	ImGui::PopID();
}

void GameObject::SetName(std::string& name)
{
	mName = std::move(name);
}

const std::string& GameObject::GetName() const
{
	return mName;
}

uint32_t GameObject::GetUniqueID() const
{
	return mUniqueID;
}
