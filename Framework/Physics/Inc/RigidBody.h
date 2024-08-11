#pragma once

#include "PhysicsObject.h"

namespace TEngine::Physics
{
	class CollisionShape;

	class RigidBody final : public PhysicsObject
	{
	public:
		RigidBody() = default;
		~RigidBody();

		void Initialize(TEngine::Graphics::Transform& graphicsTransform, const CollisionShape& shape, float mass = 0.0f);
		void Terminate();

		void SetPosition(const TEngine::Math::Vector3& position);
		void SetVelocity(const TEngine::Math::Vector3& velocity);

		bool isDynamic() const;

	private:
		void SyncGraphics() override;
		btRigidBody* GetRigidBody() override { return mRigidBody; }

		btRigidBody* mRigidBody = nullptr;
		btDefaultMotionState* mMotionState = nullptr;
		float mMass = 0.0f;

		TEngine::Graphics::Transform* mGraphicsTransform = nullptr;
	};
}
