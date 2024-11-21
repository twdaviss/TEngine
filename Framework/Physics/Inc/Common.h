#pragma once

//framework headers
#include <Math/Inc/TMath.h>
#include <Core/Inc/Core.h>
#include <Graphics/Inc/Graphics.h>

//bullet files
#include <Bullet/btBulletCollisionCommon.h>
#include <Bullet/btBulletDynamicsCommon.h>
#include <Bullet/BulletSoftBody/btSoftRigidDynamicsWorld.h>
#include <Bullet/BulletSoftBody/btSoftBodyHelpers.h>
#include <Bullet/BulletSoftBody/btSoftBodyRigidBodyCollisionConfiguration.h>
#include <Bullet/BulletSoftBody/btSoftBodySolvers.h>

//#define USE_SOFT_BODY

//helper functions
template<class T>
inline void SafeDelete(T*& ptr)
{
	if (ptr != nullptr)
	{
		delete ptr;
		ptr = nullptr;
	}
}

//math helper functions
inline btVector3 ConvertTobtVector3(const TEngine::Math::Vector3& v)
{
	return btVector3(v.x, v.y, v.z);
}
inline btQuaternion ConvertTobtQuaternion(const TEngine::Math::Quaternion& q)
{
	return btQuaternion(q.x, q.y, q.z, q.w);
}
inline btTransform ConvertTobtTransform(const TEngine::Graphics::Transform& transform)
{
	return btTransform(ConvertTobtQuaternion(transform.rotation),ConvertTobtVector3(transform.position));
}

inline TEngine::Math::Vector3 ConvertToVector3(const btVector3& v)
{
	return TEngine::Math::Vector3(v.getX(), v.getY(), v.getZ());
}
inline TEngine::Math::Quaternion ConvertToQuaternion(const btQuaternion& q)
{
	return TEngine::Math::Quaternion(q.getX(), q.getY(), q.getZ(), q.getW());
}
inline void ApplybtTransform(TEngine::Graphics::Transform& transform, const btTransform& t)
{
	transform.position = ConvertToVector3(t.getOrigin());
	transform.rotation = ConvertToQuaternion(t.getRotation());
}