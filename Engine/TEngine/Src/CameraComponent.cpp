#include "Precompiled.h"
#include "CameraComponent.h"

using namespace TEngine;
using namespace TEngine::Graphics;


void CameraComponent::Initialize()
{
	//TODO
}

void CameraComponent::Terminate()
{
	//TODO
}

void CameraComponent::DebugUI()
{
	Vector3 pos = mCamera.GetPosition();
	if (ImGui::DragFloat3("Position", &pos.x, 0.1f))
	{
		mCamera.SetPosition(pos);
	}
	Matrix4 matTrans = Matrix4::Translation(mCamera.GetPosition());
	SimpleDraw::AddTransform(matTrans);
}

Camera& CameraComponent::GetCamera()
{
	return mCamera;
}

const Camera& CameraComponent::GetCamera() const
{
	return mCamera;
}
