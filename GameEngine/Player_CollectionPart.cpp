#include "Player_CollectionPart.h"
#include"Engine/Systems/ModelSystem.h"
#include"Engine/GameObject/CameraManager.h"
#include"Engine/DirectX_11/Input.h"
Player_CollectionPart::Player_CollectionPart(Object* parent)
	:Player(parent,"Player_CollectionPart")
{
}

Player_CollectionPart::~Player_CollectionPart()
{
}

void Player_CollectionPart::Initialize()
{
	//Test_Model_ECSver playerModel(this);
	//playerModel.Load("Assets/Model/Farmer_AtandardAction_Test01.fbx");
	//AddComponent<Test_Model_ECSver>(playerModel);
	//transform_->position_ = XMVectorSet(0, 10, 0, 0);

	transform_->position_ = XMVectorSet(0, 10, 0, 0);
	CameraManager::GetCamera(0).SetPosition(this->transform_->position_);
	CameraManager::GetCamera(0).SetTarget(XMVectorSet(0, 10, 1, 0));
}

void Player_CollectionPart::Start()
{
	SetUIManager(FindObject("Play_UIManager"));
}

void Player_CollectionPart::Update()
{
	MoveControll();

	CameraControll();
}

//void Player_CollectionPart::CameraControll()
//{
//	XMFLOAT3 rotate = { 0,0,0 };
//	rotate = StoreFloat3(Input::GetMouseMove() * 0.03f);
//	cameraRotate_.x += rotate.x;
//	cameraRotate_.y += rotate.y;
//	cameraRotate_.y = Clamp<float>(cameraRotate_.y, rotateDownerLimitY_, rotateUperLimitY_);
//	transform_->RotateEular(cameraRotate_.y, cameraRotate_.x, 0);
//
//	CameraManager::GetCamera(0).SetTarget(transform_->position_ + transform_->GetFront());
//}

void Player_CollectionPart::Release()
{
}
