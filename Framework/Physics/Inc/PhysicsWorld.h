#pragma once

#include "PhysicsDebugDrawer.h"

namespace TEngine::Physics
{
	class PhysicsObject;

	class PhysicsWorld final
	{
	public:
		struct Settings
		{
			TEngine::Math::Vector3 gravity{ 0.0f, -9.81f, 0.0f };
			uint32_t simulationSteps = 10;
			float fixedTimeStep = 1.0f / 60.0f;
		};

		static void StaticInitialize(const Settings& settings);
		static void StaticTerminate();
		static PhysicsWorld* Get();

		PhysicsWorld() = default;
		~PhysicsWorld();

		void Initialize(const Settings& settings);
		void Terminate();

		void Update(float deltaTime);
		void DebugUI();

		void Register(PhysicsObject* physicsObject);
		void Unregister(PhysicsObject* physicsObject);

		Settings GetSettings() { return mSettings; }
		void UpdateSettings(Settings settings) { mSettings = settings; }

		const btCollisionObject* PerformRayCast(btVector3 start, btVector3 end)
		{
			btCollisionWorld::ClosestRayResultCallback rayCallback(start, end);
			mDynamicWorld->rayTest(start, end, rayCallback);
			return rayCallback.m_collisionObject;
		}

	private:
		using PhysicsObjects = std::vector<PhysicsObject*>;
		PhysicsObjects mPhysicsObjects;

		Settings mSettings;
		PhysicsDebugDrawer mDebugDrawer;

		//bullet objects
		btBroadphaseInterface* mInterface = nullptr;
		btCollisionDispatcher* mDispatcher = nullptr;
		btDefaultCollisionConfiguration* mCollisionConfiguraton = nullptr;
		btSequentialImpulseConstraintSolver* mSolver = nullptr;

		friend class SoftBody;
#ifdef USE_SOFT_BODY
		btSoftRigidDynamicsWorld* mDynamicWorld = nullptr;
		btSoftBodyWorldInfo& GetSoftBodyWorldInfo() { return mDynamicWorld->getWorldInfo(); }
#else
		btDiscreteDynamicsWorld* mDynamicWorld = nullptr;
		//btSoftBodyWorldInfo& GetSoftBodyWorldInfo() { return btSoftBodyWorldInfo(); }
#endif
	};
}