#include "Precompiled.h"
#include "Camera.h"

#include "GraphicsSystem.h"

using namespace TEngine;
using namespace TEngine::Graphics;

void Camera::SetMode(ProjectionMode mode)
{
	mProjectionMode = mode;
}

void Camera::SetPosition(const TMath::Vector3& position)
{
	mPosition = position;
}

void Camera::SetDirection(const TMath::Vector3& direction)
{
	// Prevent setting direction straight up or down
	auto dir = TMath::Normalize(direction);
	if (TMath::Abs(TMath::Dot(dir, TMath::Vector3::YAxis)) < 0.995f)
		mDirection = dir;
}

void Camera::SetLookAt(const TMath::Vector3& target)
{
	SetDirection(target - mPosition);
}

void Camera::SetFov(float fov)
{
	constexpr float kMinFov = 10.0f * TMath::Constants::DegToRad;
	constexpr float kMaxFov = 170.0f * TMath::Constants::DegToRad;
	mFov = TMath::Clamp(fov, kMinFov, kMaxFov);
}

void Camera::SetAspectRatio(float ratio)
{
	mAspectRatio = ratio;
}

void Camera::SetSize(float width, float height)
{
	mWidth = width;
	mHeight = height;
}

void Camera::SetNearPlane(float nearPlane)
{
	mNearPlane = nearPlane;
}

void Camera::SetFarPlane(float farPlane)
{
	mFarPlane = farPlane;
}

void Camera::Walk(float distance)
{
	mPosition += mDirection * distance;
}

void Camera::Strafe(float distance)
{
	const TMath::Vector3 right = TMath::Normalize(Cross(TMath::Vector3::YAxis, mDirection));
	mPosition += right * distance;
}

void Camera::Rise(float distance)
{
	mPosition += TMath::Vector3::YAxis * distance;
}

void Camera::Yaw(float radian)
{
	TMath::Matrix4 matRotate = TMath::Matrix4::RotationY(radian);
	mDirection = TMath::TransformNormal(mDirection, matRotate);
}

void Camera::Pitch(float radian)
{
	const TMath::Vector3 right = TMath::Normalize(Cross(TMath::Vector3::YAxis, mDirection));
	const TMath::Matrix4 matRot = TMath::Matrix4::RotationAxis(right, radian);
	const TMath::Vector3 newLook = TMath::TransformNormal(mDirection, matRot);
	SetDirection(newLook);
}

void Camera::Zoom(float amount)
{
	constexpr float minZoom = 170.0f * TMath::Constants::DegToRad;
	constexpr float maxZoom = 10.0f * TMath::Constants::DegToRad;
	mFov = TMath::Clamp(mFov - amount, maxZoom, minZoom);
}

const TMath::Vector3& Camera::GetPosition() const
{
	return mPosition;
}

const TMath::Vector3& Camera::GetDirection() const
{
	return mDirection;
}

TMath::Matrix4 Camera::GetViewMatrix() const
{
	const TMath::Vector3 l = mDirection;
	const TMath::Vector3 r = TMath::Normalize(TMath::Cross(TMath::Vector3::YAxis, l));
	const TMath::Vector3 u = TMath::Normalize(TMath::Cross(l, r));
	const float x = -TMath::Dot(r, mPosition);
	const float y = -TMath::Dot(u, mPosition);
	const float z = -TMath::Dot(l, mPosition);

	return
	{
		r.x, u.x, l.x, 0.0f,
		r.y, u.y, l.y, 0.0f,
		r.z, u.z, l.z, 0.0f,
		x,   y,   z,   1.0f
	};
}

TMath::Matrix4 Camera::GetProjectionMatrix() const
{
	return (mProjectionMode == ProjectionMode::Perspective) ? GetPerspectiveMatrix() : GetOrthographicMatrix();
}

TMath::Matrix4 Camera::GetPerspectiveMatrix() const
{
	const float a = (mAspectRatio == 0.0f) ? GraphicsSystem::Get()->GetBackBufferAspectRatio() : mAspectRatio;
	const float h = 1.0f / tan(mFov * 0.5f);
	const float w = h / a;
	const float zf = mFarPlane;
	const float zn = mNearPlane;
	const float q = zf / (zf - zn);

	return {
		w,    0.0f, 0.0f,    0.0f,
		0.0f, h,    0.0f,    0.0f,
		0.0f, 0.0f, q,       1.0f,
		0.0f, 0.0f, -zn * q, 0.0f
	};
}

TMath::Matrix4 Camera::GetOrthographicMatrix() const
{
	const float w = (mWidth == 0.0f) ? GraphicsSystem::Get()->GetBackBufferWidth() : mWidth;
	const float h = (mHeight == 0.0f) ? GraphicsSystem::Get()->GetBackBufferHeight() : mHeight;
	const float f = mFarPlane;
	const float n = mNearPlane;
	return 	{
		2 / w, 0.0f,  0.0f,        0.0f,
		0.0f,  2 / h, 0.0f,        0.0f,
		0.0f,  0.0f,  1 / (f - n), 0.0f,
		0.0f,  0.0f,  n / (n - f), 1.0f
	};
}