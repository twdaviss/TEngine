#pragma once

namespace TEngine::Physics
{
	class CollisionShape final
	{
	public:
		CollisionShape() = default;
		~CollisionShape();

		void InitializeSphere(float radius);
		void InitializeBox(const TEngine::Math::Vector3 halfExtents);
		void InitializeHull(const TEngine::Math::Vector3 halfExtents, const TEngine::Math::Vector3& origin);
		void InitializeEmpty();
		void Terminate();
	private:
		btCollisionShape* mCollisionShape = nullptr;

		friend class RigidBody;
		btCollisionShape* GetCollisionShape() const { return mCollisionShape; }
	};
}