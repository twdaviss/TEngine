#include "GameState.h"
using namespace TEngine;
using namespace TEngine::Graphics;
using namespace TEngine::Input;

void SolarSystem::Initialize()
{
	mCamera.SetPosition({ 0.0f,100.0f,-15.0f });
	mCamera.SetLookAt({ 0.0f,0.0f,0.0f });

	auto device = GraphicsSystem::Get()->GetDevice();

	//create a shape
	InitializePlanets();
	mMesh = MeshBuilder::CreateSkySpherePX(1000,1000,5000);

	std::filesystem::path shaderFilePath = L"../../Assets/Shaders/DoTexturing.fx";
	mConstantBuffer.Initialize(sizeof(Math::Matrix4));
	mMeshBuffer.Initialize(mMesh);
	mVertexShader.Initialize<VertexPX>(shaderFilePath);
	mPixelShader.Initialize(shaderFilePath);
	mTexture.Initialize(L"../../Assets/Images/skysphere/space.jpg");
	mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
}

void SolarSystem::Terminate()
{
	mSampler.Terminate();
	mTexture.Terminate();
	mPixelShader.Terminate();
	mVertexShader.Terminate();
	mMeshBuffer.Terminate();
	mConstantBuffer.Terminate();
}

void SolarSystem::Update(float deltaTime)
{
	UpdatePlanets(deltaTime);
	auto input = Input::InputSystem::Get();
	const float moveSpeed = input->IsKeyDown(KeyCode::LSHIFT) ? 50.0f : 10.0f;
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
}

void SolarSystem::Render()
{
	//bind
	mVertexShader.Bind();
	mPixelShader.Bind();
	mSampler.BindPS(0);
	mTexture.BindPS(0);
	Math::Matrix4 matWorld = Math::Matrix4::Identity;
	Math::Matrix4 matView = mCamera.GetViewMatrix();
	Math::Matrix4 matProj = mCamera.GetProjectionMatrix();
	Math::Matrix4 matFinal = matWorld * matView * matProj;
	Math::Matrix4 wvp = Transpose(matFinal);

	mConstantBuffer.Update(&wvp);
	mConstantBuffer.BindVS(0);

	mMeshBuffer.Render();

	RenderPlanets();
}
Color ringColor = Colors::White;
Color gridColor = Colors::White;
bool ringsOn = false;
bool gridOn = false;
bool pause = true;


float orbitSpeedMod = 1.0f;
float rotationSpeedMod = 1.0f;

void SolarSystem::DebugUI()
{
	gridColor.a = 0.5f;
	DebugUI::SetTheme(DebugUI::Theme::Dark);
	ImGui::Begin("DebugUI", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::LabelText("","Solar System");
	
	if (ImGui::CollapsingHeader("Settings", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::ColorEdit4("Ring Color", &ringColor.r);
		ImGui::ColorEdit4("Grid Color", &gridColor.r);
		ImGui::DragFloat("Orbit Speed", &orbitSpeedMod,0.05f, 0.0f, 10.0f);
		ImGui::DragFloat("Rotation Speed", &rotationSpeedMod, 0.05f, 0.0f, 10.0f);
	}
	
	if (ImGui::Checkbox("Enable Rings", &ringsOn))
	{
		//do stuff
		
	}
	if (ImGui::Checkbox("Enable Grid", &gridOn))
	{
		//do stuff

	}
	if (ImGui::Checkbox("Pause", &pause))
	{
		//do stuff

	}
	ImGui::End();

	if (gridOn)
	{
		SimpleDraw::AddTransform(Matrix4::Identity);
		SimpleDraw::AddGroundPlane(1600, gridColor);
		
	}
	if (ringsOn)
	{
		SimpleDraw::AddGroundCircle(60, mercury.GetOrbitDist(), ringColor);
		SimpleDraw::AddGroundCircle(60, venus.GetOrbitDist(), ringColor);
		SimpleDraw::AddGroundCircle(60, earth.GetOrbitDist(), ringColor);
		SimpleDraw::AddGroundCircle(60, mars.GetOrbitDist(), ringColor);
		SimpleDraw::AddGroundCircle(60, jupiter.GetOrbitDist(), ringColor);
		SimpleDraw::AddGroundCircle(60, saturn.GetOrbitDist(), ringColor);
		SimpleDraw::AddGroundCircle(60, uranus.GetOrbitDist(), ringColor);
		SimpleDraw::AddGroundCircle(60, neptune.GetOrbitDist(), ringColor);
		SimpleDraw::AddGroundCircle(60, pluto.GetOrbitDist(), ringColor);
	}
	SimpleDraw::Render(mCamera);
}

void SolarSystem::InitializePlanets()
{
	sun.Initialize("sun", 20, 0, 0, 0, "../../Assets/Images/planets/sun.jpg");
	mercury.Initialize("mercury",2,35,0.0017, 2,"../../Assets/Images/planets/mercury.jpg");
	venus.Initialize("venus", 3, 50, 0.0004, 1.15f, "../../Assets/Images/planets/venus.jpg");
	earth.Initialize("earth", 3, 60, 0.1, 1, "../../Assets/Images/planets/earth/earth.jpg");
	mars.Initialize("mars", 2, 70, 0.1, 0.82, "../../Assets/Images/planets/mars.jpg");
	jupiter.Initialize("jupiter", 8, 160, 0.24f, 0.44, "../../Assets/Images/planets/jupiter.jpg");
	saturn.Initialize("saturn", 7, 290, 0.23f, 0.33, "../../Assets/Images/planets/saturn.jpg");
	uranus.Initialize("uranus", 4, 500, 0.14, 0.23, "../../Assets/Images/planets/uranus.jpg");
	neptune.Initialize("neptune", 4, 600, 0.15, 0.18, "../../Assets/Images/planets/neptune.jpg");
	pluto.Initialize("pluto", 1, 800, 0.15, 0.12, "../../Assets/Images/planets/pluto.jpg");
	moon.Initialize("moon", 1, 6, 0.004, 2, "../../Assets/Images/planets/moon.jpg");
}

void SolarSystem::TerminatePlanets()
{
	moon.Terminate();
	pluto.Terminate();
	neptune.Terminate();
	uranus.Terminate();
	saturn.Terminate();
	jupiter.Terminate();
	mars.Terminate();
	earth.Terminate();
	venus.Terminate();
	mercury.Terminate();
	sun.Terminate();
}

void SolarSystem::UpdatePlanets(float deltaTime)
{
	sun.Update(deltaTime);
	mercury.Update(deltaTime);
	venus.Update(deltaTime);
	earth.Update(deltaTime);
	mars.Update(deltaTime);
	jupiter.Update(deltaTime);
	saturn.Update(deltaTime);
	uranus.Update(deltaTime);
	neptune.Update(deltaTime);
	pluto.Update(deltaTime);
	moon.UpdateOrbitMatrix(earth.worldMatrix);
	moon.Update(deltaTime);

}

void SolarSystem::RenderPlanets()
{
	Math::Matrix4 matView = mCamera.GetViewMatrix();
	Math::Matrix4 matProj = mCamera.GetProjectionMatrix();

	//sun;
	Math::Matrix4 wvp = Transpose(sun.worldMatrix * matView * matProj);
	mConstantBuffer.Update(&wvp);
	sun.Render();

	//mercury;
	wvp = Transpose(mercury.worldMatrix * matView * matProj);
	mConstantBuffer.Update(&wvp);
	mercury.Render();

	//venus;
	wvp = Transpose(venus.worldMatrix * matView * matProj);
	mConstantBuffer.Update(&wvp);
	venus.Render();

	//earth;
	wvp = Transpose(earth.worldMatrix * matView * matProj);
	mConstantBuffer.Update(&wvp);
	earth.Render();

	//mars;
	wvp = Transpose(mars.worldMatrix * matView * matProj);
	mConstantBuffer.Update(&wvp);
	mars.Render();

	//jupiter;
	wvp = Transpose(jupiter.worldMatrix * matView * matProj);
	mConstantBuffer.Update(&wvp);
	jupiter.Render();

	//saturn;
	wvp = Transpose(saturn.worldMatrix * matView * matProj);
	mConstantBuffer.Update(&wvp);
	saturn.Render();

	//uranus;
	wvp = Transpose(uranus.worldMatrix * matView * matProj);
	mConstantBuffer.Update(&wvp);
	uranus.Render();

	//neptune;
	wvp = Transpose(neptune.worldMatrix * matView * matProj);
	mConstantBuffer.Update(&wvp);
	neptune.Render();

	//pluto;
	wvp = Transpose(pluto.worldMatrix * matView * matProj);
	mConstantBuffer.Update(&wvp);
	pluto.Render();

	//moon;
	wvp = Transpose(moon.worldMatrix * matView * matProj);
	mConstantBuffer.Update(&wvp);
	moon.Render();

	mConstantBuffer.BindVS(0);
}

void Planet::Initialize(std::string _name, int _radius, int _orbitDist, float _rotationSpeed, float _orbitSpeed, std::string _texturePath)
{
	name = _name;
	radius = _radius;
	orbitDist = _orbitDist;
	orbitSpeed = _orbitSpeed;
	rotationSpeed = _rotationSpeed;
	texturePath = _texturePath;
	worldMatrix = worldMatrix * Matrix4::Translation(orbitDist, 0, 0);
	mMesh = MeshBuilder::CreateSpherePX(60, 60, radius);
	mMeshBuffer.Initialize(mMesh);
	mTexture.Initialize(texturePath);
}

void Planet::Render()
{
	mTexture.BindPS(0);
	mMeshBuffer.Render();
}

void Planet::Terminate()
{
	mMeshBuffer.Terminate();
	mTexture.Terminate();
}

void Planet::Update(float deltaTime)
{
	if (pause) { return; }
	currentRotation += rotationSpeed * rotationSpeedMod * deltaTime;
	currentOrbit += orbitSpeed * orbitSpeedMod * deltaTime;

	worldMatrix = Matrix4::RotationY(currentRotation) * Matrix4::Translation(orbitDist, 0, 0) * Matrix4::RotationY(currentOrbit);
	if (name == "moon")
	{
		worldMatrix = worldMatrix * orbitMatrix;
	}
}
