#include "GameState.h"

using namespace TEngine;
using namespace TEngine::Graphics;
using namespace TEngine::Input;
using namespace TEngine::Audio;
using namespace TEngine::Physics;

void GameState::Initialize()
{
	mCamera.SetPosition({ 0.0f,1.0f,-3.0f });
	mCamera.SetLookAt({ 0.0f,0.0f,0.0f });

	mDirectionalLight.direction = Math::Normalize({ 1.0f, -1.0f, 1.0f });
	mDirectionalLight.ambient = { 0.5f, 0.5f, 0.5f, 1.0f };
	mDirectionalLight.diffuse = { 0.8f, 0.8f, 0.8f, 1.0f };
	mDirectionalLight.specular = { 1.0f, 1.0f, 1.0f, 1.0f };

	Mesh ground = MeshBuilder::CreateHorizontalPlane(10, 10, 1.0f);
	mGround.meshBuffer.Initialize(ground);
	mGround.diffuseMapId = TextureManager::Get()->LoadTexture("misc/concrete.jpg");

	Mesh skySphere = MeshBuilder::CreateSkySphere(100, 100, 100);
	mSkySphere.meshBuffer.Initialize(skySphere);
	mSkySphere.diffuseMapId = TextureManager::Get()->LoadTexture("skysphere/sky.jpg");

	mAgentModelId = ModelManager::Get()->LoadModelId("../../Assets/Models/Agent/Agent.Model");
	ModelManager::Get()->AddAnimation(mAgentModelId, "../../Assets/Models/Agent/Animations/AgentDodge.animset");
	ModelManager::Get()->AddAnimation(mAgentModelId, "../../Assets/Models/Agent/Animations/AgentShootingGun.animset");
	ModelManager::Get()->AddAnimation(mAgentModelId, "../../Assets/Models/Agent/Animations/AgentShooting.animset");
	ModelManager::Get()->AddAnimation(mAgentModelId, "../../Assets/Models/Agent/Animations/AgentDying.animset");

	mAgent = CreateRenderGroup(mAgentModelId, &mAgentAnimator);

	mNeoModelId = ModelManager::Get()->LoadModelId("../../Assets/Models/Neo/Neo.Model");
	ModelManager::Get()->AddAnimation(mNeoModelId, "../../Assets/Models/Neo/Animations/NeoDodge.animset");
	ModelManager::Get()->AddAnimation(mNeoModelId, "../../Assets/Models/Neo/Animations/NeoShootingGun.animset");
	ModelManager::Get()->AddAnimation(mNeoModelId, "../../Assets/Models/Neo/Animations/NeoShooting.animset");
	ModelManager::Get()->AddAnimation(mNeoModelId, "../../Assets/Models/Neo/Animations/Reacting.animset");
	ModelManager::Get()->AddAnimation(mNeoModelId, "../../Assets/Models/Neo/Animations/Convulsing.animset");
	mNeo = CreateRenderGroup(mNeoModelId, &mNeoAnimator);

	mTrinityModelId = ModelManager::Get()->LoadModelId("../../Assets/Models/Trinity/Trinity.Model");
	ModelManager::Get()->AddAnimation(mTrinityModelId, "../../Assets/Models/Trinity/Animations/TrinityShootingGun.animset");
	mTrinity = CreateRenderGroup(mTrinityModelId, &mTrinityAnimator);

	mAgentAnimator.Initialize(mAgentModelId);
	mNeoAnimator.Initialize(mNeoModelId);
	mTrinityAnimator.Initialize(mTrinityModelId);

	std::filesystem::path shaderFilePath = L"../../Assets/Shaders/Standard.fx";
	mStandardEffect.Initialize(shaderFilePath);
	mStandardEffect.SetCamera(mCamera);
	mStandardEffect.SetDirectionalLight(mDirectionalLight);

	SoundEffectManager* sem = SoundEffectManager::Get();
	mEventSoundIds.push_back(sem->Load("megamanx_blast.wav"));
	mEventSoundIds.push_back(sem->Load("photongun1.wav"));
	mEventSoundIds.push_back(sem->Load("explosion.wav"));
	mEventSoundIds.push_back(sem->Load("hurt.wav"));

	mParticleEffect.Initialize();
	mParticleEffect.SetCamera(mCamera);

	ParticleSystemInfo info;
	info.maxParticles = 100;
	info.particleTextureId = TextureManager::Get()->LoadTexture("Images/bullet_bill.png");
	info.spawnPosition = Math::Vector3::Zero;
	info.spawnDirection = -Math::Vector3::ZAxis;
	info.spawnDelay = 0.0f;
	info.spawnLifeTime = 999999999999999.0f;
	info.minParticlesPerEmit = 1;
	info.maxParticlesPerEmit = 1;
	info.minTimeBetweenEmit = 0.25f;
	info.maxTimeBetweenEmit = 0.5f;
	info.minSpawnAngle = Math::Constants::Pi;
	info.maxSpawnAngle = Math::Constants::Pi;
	info.minSpeed = 40.0f;
	info.maxSpeed = 40.0f;
	info.minParticleLifetime = 5.0f;
	info.maxParticleLifetime = 5.0f;
	info.minStartColor = Colors::Red;
	info.maxStartColor = Colors::Yellow;
	info.minEndColor = Colors::White;
	info.maxEndColor = Colors::Orange;
	info.minStartScale = Math::Vector3::One;
	info.maxStartScale = { 0.5f,0.5f,0.5f };
	info.minEndScale = { 0.5f,0.5f,0.5f };
	info.maxEndScale = { 0.5f,0.5f,0.5f };

	mParticleSystem.Initialize(info);

	info.maxParticles = 100;
	info.particleTextureId = TextureManager::Get()->LoadTexture("Images/bullet_bill.png");
	info.spawnPosition = Math::Vector3::Zero;
	info.spawnDirection = Math::Vector3::ZAxis;
	info.spawnDelay = 0.0f;
	info.spawnLifeTime = 999999999999999.0f;
	info.minParticlesPerEmit = 1;
	info.maxParticlesPerEmit = 1;
	info.minTimeBetweenEmit = 0.25f;
	info.maxTimeBetweenEmit = 0.5f;
	info.minSpawnAngle = Math::Constants::Pi;
	info.maxSpawnAngle = Math::Constants::Pi;
	info.minSpeed = 40.0f;
	info.maxSpeed = 40.0f;
	info.minParticleLifetime = 5.0f;
	info.maxParticleLifetime = 5.0f;
	info.minStartColor = Colors::Red;
	info.maxStartColor = Colors::Yellow;
	info.minEndColor = Colors::White;
	info.maxEndColor = Colors::Orange;
	info.minStartScale = Math::Vector3::One;
	info.maxStartScale = { 0.5f,0.5f,0.5f };
	info.minEndScale = { 0.5f,0.5f,0.5f };
	info.maxEndScale = { 0.5f,0.5f,0.5f };

	mParticleSystem2.Initialize(info);
	mParticleSystem.SetCamera(mCamera);

	AnimationCallback neoDodge = [&]() 
		{
			//SoundEffectManager::Get()->Play(mEventSoundIds[0]);
			//mAgentAnimator.PlayAnimation(1, true);
			mNeoAnimator.PlayAnimation(1, true);
		};
	AnimationCallback agentDodge = [&]()
		{
			//SoundEffectManager::Get()->Play(mEventSoundIds[0]);
			//mAgentAnimator.PlayAnimation(1, true);
			mAgentAnimator.PlayAnimation(1, true);
			speedUpEnabled = true;
		};

	AnimationCallback setCameraNeo = [&]()
		{
			//SoundEffectManager::Get()->Play(mEventSoundIds[0]);
			//mAgentAnimator.PlayAnimation(1, true);
			lookTarget = { 0.0f,1.5f,3.0f };
		};
	AnimationCallback setCameraNeoLow = [&]()
		{
			//SoundEffectManager::Get()->Play(mEventSoundIds[0]);
			//mAgentAnimator.PlayAnimation(1, true);
			lookTarget = { 0.0f,0.5f,3.0f };
		};

	AnimationCallback setCameraAgent = [&]()
		{
			//SoundEffectManager::Get()->Play(mEventSoundIds[0]);
			//mAgentAnimator.PlayAnimation(1, true);
			lookTarget = { 0.0f,1.5f,-3.0f };
		};
	AnimationCallback setCameraAgentNew = [&]()
		{
			//SoundEffectManager::Get()->Play(mEventSoundIds[0]);
			//mAgentAnimator.PlayAnimation(1, true);
			lookTarget = { 1.0f,1.0f,3.0f };
		};

	AnimationCallback setCameraTrinity = [&]()
		{
			//SoundEffectManager::Get()->Play(mEventSoundIds[0]);
			//mAgentAnimator.PlayAnimation(1, true);
			lookTarget = { 1.0f,1.0f,3.0f };
		};

	AnimationCallback neoShoot = [&]()
		{
			//SoundEffectManager::Get()->Play(mEventSoundIds[0], true);
			mNeoAnimator.PlayAnimation(2, true);
		};

	AnimationCallback neoShootBullets = [&]()
		{
			//SoundEffectManager::Get()->Play(mEventSoundIds[0], true);
			mParticleSystem.SetPosition({ 0,1,3 });
			emitParticles = true;
		};

	AnimationCallback neoKeepShooting = [&]()
		{
			//SoundEffectManager::Get()->Play(mEventSoundIds[0]);
			mNeoAnimator.PlayAnimation(3, true);
		};

	AnimationCallback neoSurprised = [&]()
		{
			//SoundEffectManager::Get()->Play(mEventSoundIds[0]);
			mNeoAnimator.PlayAnimation(4, true);
			emitParticles = false;
		};

	AnimationCallback agentShoot = [&]()
		{
			//SoundEffectManager::Get()->Play(mEventSoundIds[0]);
			mAgentAnimator.PlayAnimation(2, true);
			speedUpEnabled = false;
		};

	AnimationCallback agentShootBullets = [&]()
		{
			//SoundEffectManager::Get()->Play(mEventSoundIds[0]);
			mParticleSystem2.SetPosition({ 0,1,-3 });
			emitParticles2 = true;
		};

	AnimationCallback agentShootNew = [&]()
		{
			//SoundEffectManager::Get()->Play(mEventSoundIds[0]);
			mAgentAnimator.PlayAnimation(2, true);
		};

	AnimationCallback agentKeepShooting = [&]()
		{
			//SoundEffectManager::Get()->Play(mEventSoundIds[0]);
			mAgentAnimator.PlayAnimation(3, true);
		};

	AnimationCallback startSlowMo = [&]()
		{
			//SoundEffectManager::Get()->Play(mEventSoundIds[0]);
			slowMoEnabled = true;
		};

	AnimationCallback stopSlowMo = [&]()
		{
			//SoundEffectManager::Get()->Play(mEventSoundIds[0]);
			slowMoEnabled = false;
		};

	AnimationCallback neoConvulsing = [&]()
		{
			//SoundEffectManager::Get()->Play(mEventSoundIds[0]);
			mNeoAnimator.PlayAnimation(5, false);
			emitParticles2 = false;
		};

	AnimationCallback trinityShoot = [&]()
		{
			//SoundEffectManager::Get()->Play(mEventSoundIds[0]);
			mTrinityAnimator.PlayAnimation(1, false);
		};
	AnimationCallback agentDying = [&]()
		{
			//SoundEffectManager::Get()->Play(mEventSoundIds[0]);
			mAgentAnimator.PlayAnimation(4, false);
		};

	AnimationCallback shootAudio = [&]()
		{
			SoundEffectManager::Get()->Play(mEventSoundIds[0], true);
		};

	AnimationCallback stopShootAudio = [&]()
		{
			SoundEffectManager::Get()->Stop(mEventSoundIds[0]);
		};

	AnimationCallback shootAudioOnce = [&]()
		{
			SoundEffectManager::Get()->Play(mEventSoundIds[0], false);
		};

	AnimationCallback hurtAudio = [&]()
		{
			SoundEffectManager::Get()->Play(mEventSoundIds[3], false);
		};
	mEventAnimationTime = 0.0f;

	mCameraAnimation = AnimationBuilder()
		.AddEventKey(setCameraNeo, 0.1f) //neo shoot 1
		.AddPositionKey({ 0,1.5,2 }, 2.0f) 
		.AddEventKey(setCameraAgent, 2.0001f)
		.AddPositionKey({ 0,1.5,-2 }, 2.0002f) //agent dodge 1
		.AddPositionKey({ 0,1.5,-2 }, 4.f) //agent dodge 1
		.AddEventKey(setCameraNeo, 4.00001f)//neo shoot 2
		.AddPositionKey({ -0.2,1.5,1.5 }, 4.00002f)
		.AddPositionKey({ -0.2,1.5,1.5 }, 6.0f)
		.AddEventKey(setCameraAgent, 6.0001f) //agent dodge 2
		.AddPositionKey({ 0,1.5,-2 }, 6.0002f) 
		.AddPositionKey({ 0,1.5,-2 }, 10.0f)
		.AddEventKey(setCameraNeo, 10.00001f)//neo surprised
		.AddPositionKey({ 0,1.5,2 }, 10.00002f)
		.AddPositionKey({ 0,1.5,2 }, 12.0f)
		.AddEventKey(setCameraAgent, 12.0001f) //agent shoot
		.AddPositionKey({ 0,1.5,-2 }, 12.0002f)
		.AddPositionKey({ 0,1.5,-2 }, 15.0f)

		.AddEventKey(startSlowMo, 15.0f)
		.AddEventKey(setCameraNeo, 15.00001f)
		.AddPositionKey({ 0,1,6 }, 15.00002f, EaseType::Linear)//neo dodge start
		.AddPositionKey({ -2.0,1,5.2 }, 16.0f, EaseType::Linear)
		.AddPositionKey({ -3,1,3 }, 17.0f, EaseType::Linear)
		.AddPositionKey({ -2,1,0.8 }, 18.0f, EaseType::Linear)
		.AddPositionKey({ 0,1,0 }, 19.0f, EaseType::Linear)
		.AddPositionKey({ 2,1,0.8 }, 20.0f, EaseType::Linear)
		.AddPositionKey({ 3,1,3 }, 21.0f, EaseType::Linear)
		.AddPositionKey({ 2,1,5.2 }, 22.0f, EaseType::Linear)
		.AddPositionKey({ 0,1,6 }, 23.0f, EaseType::Linear) // neo dodge end
		.AddEventKey(stopSlowMo, 23.00001f)
		.AddEventKey(setCameraNeoLow, 23.00001f)
		.AddPositionKey({ 1,0.5,3 }, 23.00001f, EaseType::Linear)//neo shot
		.AddPositionKey({ 1,0.5,3 }, 25.0f, EaseType::Linear)
		.AddPositionKey({ 0,1.5,2 }, 25.00001f, EaseType::Linear)//neo lays on ground
		.AddPositionKey({ 0,1.5,2 }, 27.0f, EaseType::Linear)
		.AddPositionKey({ -1,1,2 }, 27.00001f, EaseType::Linear)
		.AddPositionKey({ -1,1,2 }, 28.0f, EaseType::Linear)
		.AddEventKey(setCameraAgentNew, 28.00001f)
		.AddPositionKey({ 0,1.5,3 }, 28.00001f, EaseType::Linear) //agent shoot
		.AddPositionKey({ 0,1.5,3 }, 29.0f, EaseType::Linear)
		.AddPositionKey({ -1,1,3 }, 29.00001f, EaseType::Linear)
		.AddPositionKey({ -1,1,3 }, 32.0f, EaseType::Linear)

		.Build();
	
	mNeoAnimation = AnimationBuilder() // not working for some reason
		.AddRotationKey({ Quaternion::CreateFromYawPitchRoll(3.14/1.2, 0, 0) }, 0.0f)
		.AddPositionKey({ 0.0f,0.0f,3.0f }, 0.0f)
		.AddEventKey(neoShoot, 0.1f)
		.AddEventKey(neoShootBullets, 2.0f)
		.AddEventKey(shootAudio, 2.0f)
		.AddRotationKey({ Quaternion::CreateFromYawPitchRoll(0, 0, 0) }, 4.0f)
		.AddEventKey(neoKeepShooting, 4.0f)
		.AddEventKey(neoSurprised, 10.0f)
		.AddEventKey(stopShootAudio, 10.0f)
		.AddRotationKey({ Quaternion::CreateFromYawPitchRoll(0, 0, 0) }, 15.0f)
		.AddRotationKey({ Quaternion::CreateFromYawPitchRoll(0, 0.45, 0) }, 15.00001f)
		.AddEventKey(neoDodge, 15.0f)
		.AddRotationKey({ Quaternion::CreateFromYawPitchRoll(0, 0, 0) }, 25.0f)
		.AddRotationKey({ Quaternion::CreateFromYawPitchRoll(3.14 / 2, 0, 0) }, 25.00001f)
		.AddEventKey(neoConvulsing, 25.0f)
		.AddEventKey(hurtAudio, 25.0f)
		.AddEventKey(stopShootAudio, 25.0f)

		.Build();

	mAgentAnimation = AnimationBuilder()
		.AddPositionKey({ 0.0f,0.0f,-3.0f }, 0.0f)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(3.14, 0, 0), 0)
		.AddEventKey(agentDodge, 2.0f)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(3.14, 0, 0), 12.0f)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(1.5 * 3.14, 0, 0), 12.00001f)
		.AddEventKey(agentShoot, 12.0002f)
		.AddEventKey(agentShootBullets, 13.0f)
		.AddEventKey(shootAudio, 13.0f)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(1.5 * 3.14, 0, 0), 15.0f)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(3.14, 0, 0), 15.000001)
		.AddEventKey(agentKeepShooting, 15.000001f)
		.AddEventKey(agentShootNew, 27.5)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(3.14, 0, 0), 28)
		.AddPositionKey({ 0.0f,0.0f,-3.0f }, 28.0f)
		.AddPositionKey({ 1.0f,0.0f,3.0f }, 28.00001f)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(3.14, 0, 0), 28.00001)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(3.14, 0, 0), 29.0)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(0, 0, 0), 29.00001)
		.AddEventKey(agentDying, 29)
		.AddEventKey(hurtAudio, 29.0f)
		.AddPositionKey({ 1.0f,0.0f,3.0f }, 29.0f)
		.AddPositionKey({ 1.0f,0.0f,5.0f }, 30.5f)
		.Build();

	mTrinityAnimation = AnimationBuilder()
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(3.14, 0, 0), 0)
		.AddPositionKey({ 100.0f,100.0f,100.0f }, 0.0f)
		.AddEventKey(trinityShoot, 27.5f)
		.AddPositionKey({ 100.0f,100.0f,100.0f }, 29.0f)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(3.14, 0, 0), 29)
		.AddPositionKey({ 1.0f,0.0f,2.0f }, 29.00001f)
		.AddRotationKey(Quaternion::CreateFromYawPitchRoll(3.14/2, 0, 0), 29.00001)
		.AddEventKey(shootAudioOnce, 29.0)
		.Build();

	EventManager* em = EventManager::Get();
	mSpaceEventId = em->AddListener(EventType::SpacePressedEvent, std::bind(&GameState::OnSpaceEvent, this, std::placeholders::_1));
	mAnimEventId = em->AddListener(EventType::AnimEvent, std::bind(&GameState::OnAnimEvent, this, std::placeholders::_1));
}

void GameState::Terminate()
{
	mParticleEffect.Terminate();
	mParticleSystem2.Terminate();
	mParticleSystem.Terminate();
	mStandardEffect.Terminate();
	CleanupRenderGroup(mNeo);
	CleanupRenderGroup(mAgent);
	CleanupRenderGroup(mTrinity);
	mGround.Terminate();
	mSkySphere.Terminate();
}

void GameState::Update(float deltaTime)
{
	mTrinityAnimator.Update(deltaTime);
	if (slowMoEnabled) 
	{
		mNeoAnimator.Update(deltaTime/2);
	}
	else 
	{
		mNeoAnimator.Update(deltaTime);
	}

	if (speedUpEnabled)
	{
		mAgentAnimator.Update(2 * deltaTime);
	}
	else
	{
		mAgentAnimator.Update(deltaTime);
	}

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
	timer += deltaTime;
	mAgentAnimation.PlayEvents(prevTime, mEventAnimationTime);
	mNeoAnimation.PlayEvents(prevTime, mEventAnimationTime);
	mCameraAnimation.PlayEvents(prevTime, mEventAnimationTime);
	mTrinityAnimation.PlayEvents(prevTime, mEventAnimationTime);

	if(emitParticles)
	{
		mParticleSystem.Update(deltaTime);
	}
	if (emitParticles2)
	{
		mParticleSystem2.Update(deltaTime/2);
	}
	while (mEventAnimationTime >= mCameraAnimation.GetDuration())
	{
		mEventAnimationTime -= mCameraAnimation.GetDuration();
		timer = 0;
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
	for (auto& ro : mTrinity)
	{
		ro.transform = mTrinityAnimation.GetTransform(mEventAnimationTime);
	}
	mCamera.SetPosition(mCameraAnimation.GetTransform(mEventAnimationTime).position);
	mCamera.SetLookAt(lookTarget);

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
	//SimpleDraw::AddGroundPlane(10.0f, Colors::White);
	SimpleDraw::Render(mCamera);

	mParticleEffect.Begin();
		if (emitParticles)
		{
			mParticleSystem.Render(mParticleEffect);
		}
		if (emitParticles2)
		{
			mParticleSystem2.Render(mParticleEffect);
		}
	mParticleEffect.End();
	if (!mDrawSkeleton)
	{
		mStandardEffect.Begin();
			DrawRenderGroup(mStandardEffect, mAgent);
			DrawRenderGroup(mStandardEffect, mNeo);
			DrawRenderGroup(mStandardEffect, mTrinity);
			mStandardEffect.Render(mGround); 
			mStandardEffect.Render(mSkySphere);
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

		if (ImGui::DragFloat("Timer", &timer, 0.01f))
		{
		}
		ImGui::Checkbox("DrawSkeleton", &mDrawSkeleton);

		/*if (ImGui::DragInt("Animation", &mAnimIndex, 1, -1, mAgentAnimator.GetAnimationCount() - 1))
		{
			mAgentAnimator.PlayAnimation(mAnimIndex, true);
		}
		if (ImGui::DragInt("Animation", &mAnimIndex, 1, -1, mNeoAnimator.GetAnimationCount() - 1))
		{
			mNeoAnimator.PlayAnimation(mAnimIndex, true);
		}*/
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