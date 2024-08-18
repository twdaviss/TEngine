#include "Precompiled.h"
#include "ParticleSystem.h"

using namespace TEngine;
using namespace TEngine::Physics;
using namespace TEngine::Math;
using namespace TEngine::Graphics;

void ParticleSystem::Initialize(const ParticleSystemInfo& info)
{
	mInfo = info;
	mNextAvailableParticleIndex = 0;
	mNextSpawnTime = info.spawnDelay;
	mLifeTime = info.spawnLifeTime;

	Mesh particleMesh = MeshBuilder::CreateSpriteQuad(0.5f, 0.5f);
	mParticleObject.meshBuffer.Initialize(particleMesh);
	mParticleObject.diffuseMapId = info.particleTextureId;
	InitializeParticles(info.maxParticles);
}

void ParticleSystem::InitializeParticles(uint32_t count)
{
	mParticleIndices.resize(count);
	mParticles.resize(count);
	for (uint32_t i = 0; i < count; ++i)
	{
		mParticleIndices[i] = i;
		mParticles[i] = std::make_unique<Particle>();
		mParticles[i]->Initialize();
	}
}

void ParticleSystem::Terminate()
{
	mParticleObject.Terminate();
	for (auto& p : mParticles)
	{
		p->Terminate();
		p.reset();
	}
}

void ParticleSystem::Update(float deltaTime)
{
	if (IsActive())
	{
		mLifeTime -= deltaTime;
		mNextSpawnTime -= deltaTime;
		if (mNextSpawnTime <= 0.0f && mLifeTime > 0.0f)
		{
			SpawnParticles();
		}
		for (auto& p : mParticles)
		{
			p->Update(deltaTime);
		}
		std::sort(mParticleIndices.begin(), mParticleIndices.end(), [&](const int& a, const int& b)
		{
			float distSqrA = MagnitudeSqr(mParticles[a]->GetPosition() - mCamera->GetPosition());
			float distSqrB = MagnitudeSqr(mParticles[b]->GetPosition() - mCamera->GetPosition());
			return distSqrB < distSqrA;
		});
	}
}

bool ParticleSystem::IsActive()
{
	return false;
}

void ParticleSystem::DebugUI()
{
}

void ParticleSystem::SetPosition(const Math::Vector3& position)
{
	mInfo.spawnPosition = position;
}

void ParticleSystem::SetCamera(const Camera& camera)
{
	mCamera = &camera;
}

void ParticleSystem::SpawnParticles()
{
}

void ParticleSystem::SpawnSingleParticle()
{
}
