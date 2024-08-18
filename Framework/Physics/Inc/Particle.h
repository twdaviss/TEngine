#pragma once

#include "RigidBody.h"
#include "CollisionShape.h"
namespace TEngine::Physics
{
	struct ParticleActivationData
	{
		float lifeTime = 0.0f;
		Color startColor = Colors::White;
		Color endColor = Colors::White;
		Math::Vector3 startScale = Math::Vector3::One;
		Math::Vector3 endScale = Math::Vector3::One;
		Math::Vector3 position = Math::Vector3::One;
		Math::Vector3 velocity = Math::Vector3::One;
	};

	struct CurrentParticleInfo
	{
		Color color = Colors::White;
		Graphics::Transform transform;
	};

	class Particle
	{
	public:
		virtual void Initialize();
		void Terminate();
		void Activate(const ParticleActivationData& data);
		void Update(float deltaTime);

		bool isActive() const;
		void ObtainCurrentInfo(CurrentParticleInfo& info) const;

		const Vector3 GetPosition() const;

	private:
		Graphics::Transform mTransform;
		RigidBody mRigidBody;
		CollisionShape mCollisionShape;

		ParticleActivationData mData;
		float mLifeTime = 0.0f;
	};
}