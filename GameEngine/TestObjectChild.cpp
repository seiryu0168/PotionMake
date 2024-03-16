#include "TestObjectChild.h"
#include"Engine/Systems/PhysicsSystem.h"
#include"Engine/Systems/TextSystem.h"
#include"Engine/Systems/ImageSystem.h"
#include"Engine/Systems/ModelSystem.h"
#include"Engine/Systems/ParticleSystem.h"
#include"Engine/GameObject/CameraManager.h"
TestObjectChild::TestObjectChild(Object* parent)
	:GameObject(parent,"TestObjectChild"),
	hModel_(-1),
	time_(0)
{
	//CameraManager::AllRmoveCamera(0);
	//
	//XMFLOAT2 screenWidth = { (float)Direct3D::GetScreenWidth(),(float)Direct3D::GetScreenHeight() };
	//Camera camera;
	//camera.Initialize(screenWidth.x / 2.0f, screenWidth .y/2.0f, 0.1f, 100.0f);
	////camera.SetAOV((float)Direct3D::GetScreenHeight() / (float)Direct3D::GetScreenWidth());
	//camera.SetPosition(XMVectorSet(-30, 10, -30, 0));
	//camera.SetTarget(XMVectorSet(0, 0, 0, 0));
	//camera.SetViewPort(screenWidth.x / 2.0f, screenWidth .y/2.0f, 0.0f, 1.0f, 0, screenWidth.y / 4.0f);
	//CameraManager::AddCamera(camera);
	//
	//Camera camera2;
	//camera2.Initialize(screenWidth.x / 2.0f, screenWidth .y/2.0f, 0.1f, 100.0f);
	////camera2.SetAOV((float)Direct3D::GetScreenHeight() / (float)Direct3D::GetScreenWidth());
	//camera2.SetPosition(XMVectorSet(0, 10, -40, 0));
	//camera2.SetTarget(XMVectorSet(0, 0, 0, 0));
	//camera2.SetViewPort(screenWidth.x / 2.0f, screenWidth .y/2.0f, 0.0f, 1.0f, screenWidth .x/2.0f, screenWidth .y/4.0f);
	//CameraManager::AddCamera(camera2);
}

TestObjectChild::~TestObjectChild()
{
}

void TestObjectChild::Initialize()
{
	Text text;
	text.SetText("GameSelect");
	//text.SetPosition({ 0,0 });
	text.SetColor({ 0,0,1,1 });
	AddComponent<Text>(text);
	
	//Image image;
	//image.Load("Assets\\Image\\Line.png");
	//image.SetDrawTarget(1);
	//AddComponent<Image>(image);

	Test_Model_ECSver model(this);
	model.Load("Assets\\Model\\AAA.fbx");
	AddComponent<Test_Model_ECSver>(model);
	Particle particle(this);
	EmitterData data;
	data.acceleration = 0.3f;
	data.delay = 30;
	data.position = { 0,0,0 };
	data.positionErr = { 10,10,10 };
	data.dir = { 1,0,0 };
	data.dirErr = { 0,0,0 };
	data.gravity = -0.01f;
	data.firstSpeed = 0.001f;
	data.lifeTime = 100;
	data.number = 10;
	data.scale = { 1.0f,1.0f };
	data.size = { 1,1 };
	data.sizeErr = { 0,0 };
	data.textureFileName = "Assets\\Image\\BrickTexture.jpg";
	data.blendMode = BLEND_MODE::BLEND_DEFAULT;
	particle.SetData(data);
	AddComponent<Particle>(particle);
}

void TestObjectChild::Update()
{
	time_++;
	transform_->position_ = XMVectorSet(0.0f,sinf(XMConvertToRadians((float)time_)*2.0f),0.0f,0.0f)*4.0f;
	
}

void TestObjectChild::Draw()
{
	//ModelManager::SetTransform(hModel_, *transform_);
	//ModelManager::Draw(hModel_);
}

void TestObjectChild::Release()
{
}

void TestObjectChild::OnCollision(Object* target)
{
	int a = 0;
}
