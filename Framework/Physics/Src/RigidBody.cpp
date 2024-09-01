#include "Precompiled.h"
#include "RigidBody.h"
#include "CollisionShape.h"
#include "PhysicsWorld.h"

using namespace TEngine;
using namespace TEngine::Physics;
using namespace TEngine::Math;
using namespace TEngine::Graphics;

RigidBody::~RigidBody()
{
	ASSERT(mRigidBody == nullptr && mMotionState == nullptr, "RigidBody: termiante must be called");
}

void RigidBody::Initialize(TEngine::Graphics::Transform& graphicsTransform, const CollisionShape& shape, float mass)
{
	mGraphicsTransform = &graphicsTransform;
	mMass = mass;

	mMotionState = new btDefaultMotionState(ConvertTobtTransform(graphicsTransform));
	mRigidBody = new btRigidBody(mMass, mMotionState, shape.GetCollisionShape());
	PhysicsWorld::Get()->Register(this);
}

void RigidBody::Terminate()
{
	PhysicsWorld::Get()->Unregister(this);
	SafeDelete(mRigidBody);
	SafeDelete(mMotionState);
	mGraphicsTransform == nullptr;
}

void RigidBody::SetPosition(const TEngine::Math::Vector3& position)
{
	if (isDynamic())
	{
		mRigidBody->activate();
	}
	mGraphicsTransform->position = position;
	mRigidBody->setWorldTransform(ConvertTobtTransform(*mGraphicsTransform));
}

void RigidBody::SetVelocity(const TEngine::Math::Vector3& velocity)
{
	mRigidBody->activate();
	mRigidBody->setLinearVelocity(ConvertTobtVector3(velocity));
}

bool RigidBody::isDynamic() const
{
	return mMass > 0.0f;
}

void RigidBody::SyncGraphics()
{
	ApplybtTransform(*mGraphicsTransform, mRigidBody->getWorldTransform());
}