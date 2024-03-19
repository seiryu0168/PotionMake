#include "Player.h"
#include"Engine/DirectX_11/Input.h"
#include"Engine/DirectX_11/Math.h"
#include"Engine/Systems/ModelSystem.h"
#include"Engine/GameObject/CameraManager.h"
Player::Player(Object* parent)
	:GameObject(parent, "Player"),
	moveVec_(XMVectorSet(0,0,0,0)),
	speed_(0.5),
	cameraRotate_({0,0}),
	cameraTargetVec_(XMVectorSet(0,0,1,0)),
	moveTime_(0)
{
}

Player::~Player()
{
}

void Player::Initialize()
{
	//Test_Model_ECSver floorModel(this);
	//floorModel.Load("Assets/Model/ground_grass.fbx");
	//AddComponent<Test_Model_ECSver>(floorModel);
	transform_->position_ = XMVectorSet(0, 10, 0, 0);
	CameraManager::GetCamera(0).SetPosition(this->transform_->position_);
	CameraManager::GetCamera(0).SetTarget(XMVectorSet(0,10,1,0));
}

void Player::Update()
{
	if (Input::IsKey(DIK_W))
	{
		moveVec_ += XMVectorSet(0,0, speed_, 0);
	}
	if (Input::IsKey(DIK_A))
	{
		moveVec_ += XMVectorSet(-speed_, 0, 0, 0);
	}
	if (Input::IsKey(DIK_S))
	{
		moveVec_ += XMVectorSet(0, 0, -speed_, 0);
	}
	if (Input::IsKey(DIK_D))
	{
		moveVec_ += XMVectorSet(speed_, 0, 0, 0);
	}
	
	if (VectorLength(moveVec_) >= 0.1f)
	{
		XMFLOAT3 moveBuff = StoreFloat3(XMVector3Rotate(moveVec_, transform_->rotate_));
		moveBuff.y = 0;
		moveVec_ = XMLoadFloat3(&moveBuff);

		transform_->position_ += XMVector3Normalize(moveVec_)*0.3f;
		CameraManager::GetCamera(0).SetPosition(this->transform_->position_);
		//CameraManager::GetCamera(0).SetTarget(this->transform_->position_ + XMVectorSet(0, 0, 1, 0));
		moveVec_ = XMVectorSet(0, 0, 0, 0);
	}
	CameraControll();
}
void Player::CameraControll()
{
	XMFLOAT3 rotate = { 0,0,0 };
	rotate = StoreFloat3(Input::GetMouseMove()*0.03f);
	cameraRotate_.x += rotate.x;
	cameraRotate_.y += rotate.y;
	cameraRotate_.y = Clamp<float>(cameraRotate_.y, -60.0f, 60.0f);
	transform_->RotateEular(cameraRotate_.y, cameraRotate_.x, 0);//RotateEular(XMConvertToDegrees(cameraRotate_.y), XMConvertToDegrees(cameraRotate_.x*10), 0);
	CameraManager::GetCamera(0).SetTarget(transform_->position_ + transform_->GetFront());
}
void Player::Release()
{
}
