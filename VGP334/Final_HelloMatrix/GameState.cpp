#include "GameState.h"

using namespace TEngine;
using namespace TEngine::Graphics;
using namespace TEngine::Input;
using namespace TEngine::Audio;

void GameState::Initialize()
{
	mCamera.SetPosition({ 0.0f,1.0f,-3.0f });
	mCamera.SetLookAt({ 0.0f,0.0f,0.0f });

	mDirectionalLight.direction = Math::Normalize({ 1.0f, -1.0f, 1.0f });
	mDirectionalLight.ambient = { 0.5f, 0.5f, 0.5f, 1.0f };
	mDirectionalLight.diffuse = { 0.8f, 0.8f, 0.8f, 1.0f };
	mDirectionalLight.specular = { 1.0f, 1.0f, 1.0f, 1.0f };

	mAgentModelId = ModelManager::Get()->LoadModelId("../../Assets/Models/Agent/Agent.Model");
	ModelManager::Get()->AddAnimation(mAgentModelId, "../../Assets/Models/Ninja/Animations/Dying.animset");
	mAgent = CreateRenderGroup(mAgentModelId, &mAgentAnimator);

	mNeoModelId = ModelManager::Get()->LoadModelId("../../Assets/Models/Neo/Neo.Model");
	ModelManager::Get()->AddAnimation(mNeoModelId, "../../Assets/Models/Ninja/Animations/Dying.animset");
	mNeo = CreateRenderGroup(mNeoModelId, &mNeoAnimator);

	mAgentAnimator.Initialize(mAgentModelId);
	mNeoAnimator.Initialize(mNeoModelId);

	std::filesystem::path shaderFilePath = L"../../Assets/Shaders/Standard.fx";
	mStandardEffect.Initialize(shaderFilePath);
	mStandardEffect.SetCamera(mCamera);
	mStandardEffect.SetDirectionalLight(mDirectionalLight);

	SoundEffectManager* sem = SoundEffectManager::Get();
	mEventSoundIds.push_back(sem->Load("megamanx_blast.wav"));
	mEventSoundIds.push_back(sem->Load("photongun1.wav"));
	mEventSoundIds.push_back(sem->Load("explosion.wav"));

	AnimationCallback cb = [&]() 
		{
			SoundEffectManager::Get()->Play(mEventSoundIds[0]);
			mAgentAnimator.PlayAnimation(1, true);
			//mNeoAnimator.PlayAnimation(1, true);
		};

	mEventAnimationTime = 0.0f;
	mAgentAnimation = AnimationBuilder()
		.AddPositionKey({ 0.0f,0.0f,0.0f }, 0.0f)
		.AddPositionKey({ 0.0f,0.0f,0.0f }, 0.0f)
		.AddPositionKey({ 3.0f,0.0f,0.0f }, 2.0f)
		.AddPositionKey({ 0.0f,0.0f,0.0f }, 3.0f)
		.AddEventKey(cb, 1.0f)
		.AddEventKey(std::bind(&GameState::OnEvent2, this), 2.0f)
		.AddEventKey(std::bind(&GameState::OnEvent3, this), 3.0f)
		.Build();

	//mNeoAnimation = AnimationBuilder()
	//	.Build();

	EventManager* em = EventManager::Get();
	mSpaceEventId = em->AddListener(EventType::SpacePressedEvent, std::bind(&GameState::OnSpaceEvent, this, std::placeholders::_1));
	mAnimEventId = em->AddListener(EventType::AnimEvent, std::bind(&GameState::OnAnimEvent, this, std::placeholders::_1));
}

void GameState::Terminate()
{
	mStandardEffect.Terminate();
	CleanupRenderGroup(mNeo);
	CleanupRenderGroup(mAgent);
}

void GameState::Update(float deltaTime)
{
	mAgentAnimator.Update(deltaTime);
	mNeoAnimator.Update(deltaTime);

	auto input = Input::InputSystem::Get();
	const float moveSpeed = input->IsKeyDown(KeyCode::LSHIFT) ? 10.0f : 1.0f;
	const float turnSpeed = 0.1f;

	if (input->IsKeyDown(KeyCode::W))
	{
		mCamera.Walk(moveSpeed * deltaTime);
	}
	if (input->IsKeyDown(KeyCode::S))
	{
		mCamera.Walk(-moveSpeed * deltaTime);
	}
	if (input->IsKeyDown(KeyCode::A))
	{
		mCamera.Strafe(-moveSpeed * deltaTime);
	}
	if (input->IsKeyDown(KeyCode::D))
	{
		mCamera.Strafe(moveSpeed * deltaTime);
	}
	if (input->IsKeyDown(KeyCode::E))
	{
		mCamera.Rise(moveSpeed * deltaTime);
	}
	if (input->IsKeyDown(KeyCode::Q))
	{
		mCamera.Rise(-moveSpeed * deltaTime);
	}
	if (input->IsMouseDown(MouseButton::RBUTTON))
	{
		mCamera.Yaw(input->GetMouseMoveX() * turnSpeed * deltaTime);
		mCamera.Pitch(input->GetMouseMoveY() * turnSpeed * deltaTime);
	}

	if (input->IsKeyPressed(KeyCode::SPACE))
	{
		SpacePressedEvent spacePressed;
		EventManager::Broadcast(&spacePressed);
	}

	float prevTime = mEventAnimationTime;
	mEventAnimationTime += deltaTime;
	mAgentAnimation.PlayEvents(prevTime, mEventAnimationTime);
	while (mEventAnimationTime >= mAgentAnimation.GetDuration())
	{
		mEventAnimationTime -= mAgentAnimation.GetDuration();
	}
}

void GameState::Render()
{
	for (auto& ro : mAgent)
	{
		ro.transform = mAgentAnimation.GetTransform(mEventAnimationTime);
	}
	for (auto& ro : mNeo)
	{
		ro.transform = mNeoAnimation.GetTransform(mEventAnimationTime);
	}
	if (mDrawSkeleton)
	{
		Matrix4 transform = mAgent[0].transform.GetMatrix4();
		AnimationUtil::BoneTransforms boneTransforms;
		AnimationUtil::ComputeBoneTransforms(mAgentModelId, boneTransforms, &mAgentAnimator);
		for (auto& boneTransform : boneTransforms)
		{
			boneTransform = boneTransform * transform;
		}
		AnimationUtil::DrawSkeleton(mAgentModelId, boneTransforms);

		transform = mNeo[0].transform.GetMatrix4();
		AnimationUtil::ComputeBoneTransforms(mNeoModelId, boneTransforms, &mNeoAnimator);
		for (auto& boneTransform : boneTransforms)
		{
			boneTransform = boneTransform * transform;
		}
		AnimationUtil::DrawSkeleton(mNeoModelId, boneTransforms);
	}
	SimpleDraw::AddGroundPlane(10.0f, Colors::White);
	SimpleDraw::Render(mCamera);

	if (!mDrawSkeleton)
	{
		mStandardEffect.Begin();
			DrawRenderGroup(mStandardEffect, mAgent);
			DrawRenderGroup(mStandardEffect, mNeo);
		mStandardEffect.End();
	}
}

void GameState::DebugUI()
{
	ImGui::Begin("Debug Controls", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
		if (ImGui::CollapsingHeader("Light", ImGuiTreeNodeFlags_DefaultOpen))
		{
			if (ImGui::DragFloat3("Direction", &mDirectionalLight.direction.x, 0.01f))
			{
				mDirectionalLight.direction = Math::Normalize(mDirectionalLight.direction);
			}
			ImGui::ColorEdit4("Ambient##Light", &mDirectionalLight.ambient.r);
			ImGui::ColorEdit4("Diffuse##Light", &mDirectionalLight.diffuse.r);
			ImGui::ColorEdit4("Specular##Light", &mDirectionalLight.specular.r);
		}

		ImGui::Checkbox("DrawSkeleton", &mDrawSkeleton);
		if (ImGui::DragInt("Animation", &mAnimIndex, 1, -1, mAgentAnimator.GetAnimationCount() - 1))
		{
			mAgentAnimator.PlayAnimation(mAnimIndex, true);
		}
		if (ImGui::DragInt("Animation", &mAnimIndex, 1, -1, mNeoAnimator.GetAnimationCount() - 1))
		{
			mNeoAnimator.PlayAnimation(mAnimIndex, true);
		}
		mStandardEffect.DebugUI();
	ImGui::End();
}

void GameState::OnEvent2()
{
	SoundEffectManager::Get()->Play(mEventSoundIds[1]);
	AnimEvent animEvent;
	animEvent.eventName = "Shoot";
	EventManager::Broadcast(&animEvent);
}

void GameState::OnEvent3()
{
	SoundEffectManager::Get()->Play(mEventSoundIds[2]);
	AnimEvent animEvent;
	animEvent.eventName = "Explode";
	EventManager::Broadcast(&animEvent);
}

void GameState::OnSpaceEvent(const TEngine::Event* event)
{
	LOG("SPACE EVENT OCCURED");
	SoundEffectManager::Get()->Stop(mEventSoundIds[2]);
	SoundEffectManager::Get()->Play(mEventSoundIds[2]);
}

void GameState::OnAnimEvent(const TEngine::Event* event)
{
	AnimEvent* eventData = (AnimEvent*)event;
	if (eventData->eventName == "Shoot")
	{
		LOG("SHOOT EVENT OCCURED");
	}
	else if (eventData->eventName == "Explode")
	{
		LOG("EXPLODE EVENT OCCURED");
	}
}