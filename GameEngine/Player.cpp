#include "Player.h"
#include"Engine/DirectX_11/Input.h"
#include"Engine/DirectX_11/Math.h"
#include"Engine/Systems/ModelSystem.h"
#include"Engine/Systems/ColliderSystem.h"
#include"Engine/Systems/TextSystem.h"
#include"Engine/GameObject/CameraManager.h"
#include"Play_UIManager.h"
#include"ManagementPartObjectBase.h"
#include"ManagementPart/Play_ManagementPart_BaseUI.h"
#include"UIBase.h"
Player::Player(Object* parent, std::string name)
	:GameObject(parent, name),
	moveVec_(XMVectorSet(0,0,0,0)),
	speed_(0.3f),
	canControll_(true),
	cameraRotate_({0,0}),
	cameraTargetVec_(XMVectorSet(0,0,1,0)),
	moveTime_(0),
	rotateUperLimitY_(60),
	rotateDownerLimitY_(-60),
	collisionObjectName_(""),
	UIManagerObject_(nullptr),
	collisionUINum_(-1)
{
}

Player::~Player()
{
}

void Player::MoveControll()
{
	if (Input::IsKey(DIK_W))
	{
		moveVec_ += XMVectorSet(0, 0, speed_, 0);
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
	if (VectorLength(moveVec_) >= 0.01f)
	{
		XMFLOAT3 moveBuff = StoreFloat3(XMVector3Rotate(moveVec_, transform_->rotate_));
		moveBuff.y = 0;
		moveVec_ = XMLoadFloat3(&moveBuff);

		transform_->position_ += XMVector3Normalize(moveVec_) * speed_;
		CameraManager::GetCamera(0).SetPosition(this->transform_->position_);
		moveVec_ = XMVectorSet(0, 0, 0, 0);
	}
}
void Player::CameraControll()
{
	XMFLOAT3 rotate = { 0,0,0 };
	rotate = StoreFloat3(Input::GetMouseMove()*0.03f);
	cameraRotate_.x += rotate.x;
	cameraRotate_.y += rotate.y;
	cameraRotate_.y = Clamp<float>(cameraRotate_.y, rotateDownerLimitY_, rotateUperLimitY_);
	transform_->RotateEular(cameraRotate_.y, cameraRotate_.x, 0);
	
	CameraManager::GetCamera(0).SetTarget(transform_->position_ + transform_->GetFront());
}
void Player::SetUIManager(Object* uiManager)
{
	if(uiManager!=nullptr&&UIManagerObject_==nullptr)
	UIManagerObject_ = uiManager;
}
void Player::Release()
{
}