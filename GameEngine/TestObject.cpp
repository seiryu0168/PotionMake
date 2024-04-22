#include "TestObject.h"
//#include"Engine/ResourceManager/Model.h"
#include"Engine/Systems/PhysicsSystem.h"
#include"TestObjectChild.h"
#include"Engine/ECS/EntityManager.h"
#include"Engine/Collider/BoxCollider.h"
#include"Engine/Components/Test_Model_ECSver.h"
#include"Engine/Components/Text.h"
#include"AssimpLoader.h"
#include"Engine/Systems/ImageSystem.h"
#include"Engine/newSceneManager.h"
#include"Engine/DirectX_11/Input.h"

TestObject::TestObject(Object* parent)
	:GameObject(parent,"TestObject"),
	hModel_(-1),
	time_(0),
	vPos_(XMVectorSet(0,0,10.1f,0))
{
	//DrawComponent<Test_Model_ECSver>()
	
}

TestObject::~TestObject()
{
}

void TestObject::Initialize()
{
	//AssimpLoader loader;
	//std::vector<Mesh> mesh;
	//Mesh m;
	//mesh.push_back(m);
	//ImportSetting set("",mesh, true,true);
	//loader.Load(set);
	//Collider coll({ 0,0,0 });
	//HitSphere sphere(1.0f);
	//coll.SetCollider<HitSphere>(sphere);
	//coll.SetAttachObject(this);
	//AddComponent<Collider>(coll);
	//Instantiate<TestObjectChild>(this);
	//
	//Draw2DComponent textObj;
	//Text txt;
	//txt.Load("asdfg", "Sitka Text", { 0,0,100,100 }, LEFT_TOP);
	//txt.SetPosition({ 0,0 });
	//txt.SetColor({ 0, 0, 0, 1});
	//textObj.SetDrawObject<Text>(txt);
	//AddComponent<Draw2DComponent>(textObj);
	//
	//Draw3DComponent dObj;
	//Test_Model_ECSver model(this);
	//model.Load("Assets\\Model\\AAA.fbx");
	//dObj.SetDrawObject<Test_Model_ECSver>(model);
	//AddComponent<Draw3DComponent>(dObj);
	 
	//Draw3DComponent particle;
	//Particle particle(this);
	//EmitterData data;
	//data.acceleration = 0.3f;
	//data.delay = 30;
	//data.position = { 0,0,0 };
	//data.positionErr = { 10,10,10 };
	//data.dir = { 1,0,0 };
	//data.dirErr = { 0,0,0 };
	//data.gravity = -0.01f;
	//data.firstSpeed = 0.001f;
	//data.lifeTime = 100;
	//data.number = 10;
	//data.scale = { 1.0f,1.0f };
	//data.size = { 1,1 };
	//data.sizeErr = { 0,0 };
	//data.textureFileName = "Assets\\Image\\BrickTexture.jpg";
	//data.blendMode = BLEND_MODE::BLEND_DEFAULT;
	//particle.SetData(data);
	//AddComponent<Particle>(particle);
	
	//Test_Model_ECSver model(this);
	//model.Load("Assets\\Model\\AAA.fbx");
	//AddComponent<Test_Model_ECSver>(model);

	//Text text;
	//AddComponent<Text>(text);
	//Text text2;
	//text2.SetText("destroy");
	//text2.SetColor({ 1,0,0,1 });
	//AddComponent<Text>(text2);
	//text2.SetPosition({ 0,0 });
	//LineParticle line(this);
	//LineData lineData;
	//lineData.length = 100;
	//lineData.textureName = "Assets\\Image\\Effect01.png";
	//lineData.width = 0.5f;
	//lineData.endWidth = 0.0f;
	//line.SetLineParameter(lineData);
	//line.SetBlendMode(BLEND_MODE::BLEND_DEFAULT);
	//AddComponent<LineParticle>(line);
	
	
	
	Image image(this);
	image.Load("Assets\\Image\\ItemBaseImage.png");
	//XMFLOAT3 pos = { -1.0f,0.001f,0 };
	//image.SetPosition({1,0,0});
	//image.SetDrawTarget(0);
	image.SetSize({ 1,1,0 });

	AddComponent<Image>(image);	

	Text txt(this);
	txt.SetText("");
	txt.SetTextSize(40);
	AddComponent<Text>(txt);

	//Instantiate<TestObjectChild>(this);

}

void TestObject::Update()
{
	XMFLOAT3 pos = StoreFloat3(Input::GetMousePosition());
	std::string msg = "x:" + std::to_string(pos.x)+"\n";
	msg += "y:" + std::to_string(pos.y)+"\n";
	if (GetComponent<Image>().IsHitCursor())
	{
		msg += "Hit";
	}
	else
		msg += "NotHit";
	GetComponent<Text>().SetText(msg);

	//time_++;
	//vPos_ = XMVector3Rotate(vPos_, XMQuaternionRotationAxis(XMVectorSet(0, 1.0f, 0, 0), XMConvertToRadians(1)));
	//transform_->position_ = vPos_;
	//if (/*Input::IsPadAnyButtonDown(3) || */Input::IsMouseButtonDown(0))
	//{
	//	newSceneManager::ChangeScene(SCENE_ID::PLAY);
	//}
	//if(Input::IsMouseButtonDown(1))
	//	newSceneManager::ChangeScene(SCENE_ID::MENU);
	//if (Input::IsKeyDown(DIK_X))
	//	GetComponent<Particle>().Stop();
	//if (Input::IsKeyDown(DIK_L))
	//	GetComponent<Particle>().Restart();
	//
	//
	//WORD input;
	//
	//if (Input::GetPadAnyUp(0)!=PUSH)
	//	input = XINPUT_GAMEPAD_B;
}

void TestObject::Draw()
{
	//ModelManager::SetTransform(hModel_, *transform_);
	//ModelManager::Draw(hModel_);
}

void TestObject::Release()
{
}

void TestObject::OnCollision(Object* target)
{
}