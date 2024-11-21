#include "Precompiled.h"
#include "PhysicsObject.h"
#include "PhysicsWorld.h"

using namespace TEngine;
using namespace TEngine::Physics;

namespace
{
	std::unique_ptr<PhysicsWorld> sPhysicsWorld;
}

void PhysicsWorld::StaticInitialize(const Settings& settings)
{
	ASSERT(sPhysicsWorld == nullptr, "PhysicsWorld: is already initialized");
	sPhysicsWorld = std::make_unique<PhysicsWorld>();
	sPhysicsWorld->Initialize(settings);
}

void PhysicsWorld::StaticTerminate()
{
	if (sPhysicsWorld != nullptr)
	{
		sPhysicsWorld->Terminate();
		sPhysicsWorld.reset();
	}
}

PhysicsWorld* PhysicsWorld::Get()
{
	ASSERT(sPhysicsWorld != nullptr, "PhysicsWorld: is not initialized");
	return sPhysicsWorld.get();
}

PhysicsWorld::~PhysicsWorld()
{
	ASSERT(mDynamicWorld == nullptr, "PhysicsWorld: terminate must be called");
}

void PhysicsWorld::Initialize(const Settings& settings)
{
	mSettings = settings;
	mInterface = new btDbvtBroadphase();
	mSolver = new btSequentialImpulseConstraintSolver();
#ifdef USE_SOFT_BODY
	mCollisionConfiguraton = new btSoftBodyRigidBodyCollisionConfiguration();
	mDispatcher = new btCollisionDispatcher(mCollisionConfiguraton);
	mDynamicWorld = new btSoftRigidDynamicsWorld(mDispatcher, mInterface, mSolver, mCollisionConfiguraton);
#else
	mCollisionConfiguraton = new btDefaultCollisionConfiguration();
	mDispatcher = new btCollisionDispatcher(mCollisionConfiguraton);
	mDynamicWorld = new btDiscreteDynamicsWorld(mDispatcher, mInterface, mSolver, mCollisionConfiguraton);
#endif
	mDynamicWorld->setGravity(ConvertTobtVector3(settings.gravity));
	mDynamicWorld->setDebugDrawer(&mDebugDrawer);
}



void PhysicsWorld::Terminate()
{
	SafeDelete(mDynamicWorld);
	SafeDelete(mSolver);
	SafeDelete(mInterface);
	SafeDelete(mDispatcher);
	SafeDelete(mCollisionConfiguraton);
}

void PhysicsWorld::Update(float deltaTime)
{
	//update the physics world
	mDynamicWorld->stepSimulation(deltaTime, mSettings.simulationSteps, mSettings.fixedTimeStep);

	//sync up the graphics
	for (PhysicsObject* po : mPhysicsObjects)
	{
		po->SyncGraphics();
	}
}

void PhysicsWorld::DebugUI()
{
	if (ImGui::CollapsingHeader("Physics", ImGuiTreeNodeFlags_DefaultOpen))
	{
		int debugMode = mDebugDrawer.getDebugMode();
		
		bool isEnabled = (debugMode & btIDebugDraw::DBG_DrawWireframe) > 0;
		if (ImGui::Checkbox("DrawWireFrame", &isEnabled))
		{
			debugMode = (isEnabled) ? debugMode | btIDebugDraw::DBG_DrawWireframe : debugMode & ~btIDebugDraw::DBG_DrawWireframe;
		}

		isEnabled = (debugMode & btIDebugDraw::DBG_DrawAabb) > 0;
		if (ImGui::Checkbox("DrawAABB", &isEnabled))
		{
			debugMode = (isEnabled) ? debugMode | btIDebugDraw::DBG_DrawAabb : debugMode & ~btIDebugDraw::DBG_DrawAabb;
		}

		isEnabled = (debugMode & btIDebugDraw::DBG_DrawContactPoints) > 0;
		if (ImGui::Checkbox("DrawContactPoints", &isEnabled))
		{
			debugMode = (isEnabled) ? debugMode | btIDebugDraw::DBG_DrawContactPoints : debugMode & ~btIDebugDraw::DBG_DrawContactPoints;
		}
		mDebugDrawer.setDebugMode(debugMode);
		mDynamicWorld->debugDrawWorld();
	}
}

void PhysicsWorld::Register(PhysicsObject* physicsObject)
{
	auto iter = std::find(mPhysicsObjects.begin(), mPhysicsObjects.end(), physicsObject);
	if (iter == mPhysicsObjects.end())
	{
		mPhysicsObjects.push_back(physicsObject);
#ifdef USE_SOFT_BODY
		if (physicsObject->GetSoftBody() != nullptr)
		{
			mDynamicWorld->addSoftBody(physicsObject->GetSoftBody());
		}
#endif
		if (physicsObject->GetRigidBody() != nullptr)
		{
			mDynamicWorld->addRigidBody(physicsObject->GetRigidBody());
		}
	}
}

void PhysicsWorld::Unregister(PhysicsObject* physicsObject)
{
	auto iter = std::find(mPhysicsObjects.begin(), mPhysicsObjects.end(), physicsObject);
	if (iter != mPhysicsObjects.end())
	{
#ifdef USE_SOFT_BODY
		if (physicsObject->GetSoftBody() != nullptr)
		{
			mDynamicWorld->removeSoftBody(physicsObject->GetSoftBody());
		}
#endif
		if (physicsObject->GetRigidBody() != nullptr)
		{
			mDynamicWorld->removeRigidBody(physicsObject->GetRigidBody());
		}
		mPhysicsObjects.erase(iter);
	}
}
