#include "Player.h"
#include"Engine/DirectX_11/Input.h"
#include"Engine/DirectX_11/Math.h"
#include"Engine/Systems/ModelSystem.h"
#include"Engine/Systems/ColliderSystem.h"
#include"Engine/Systems/TextSystem.h"
#include"Engine/GameObject/CameraManager.h"
#include"Play_UIManager.h"
#include"ManagementPartObjectBase.h"
#include"Play_ManagementPart_BaseUI.h"
#include"UIBase.h"
Player::Player(Object* parent)
	:GameObject(parent, "Player"),
	moveVec_(XMVectorSet(0,0,0,0)),
	speed_(0.5),
	cameraRotate_({0,0}),
	cameraTargetVec_(XMVectorSet(0,0,1,0)),
	moveTime_(0),
	rotateUperLimitY_(60),
	rotateDownerLimitY_(-60),
	collisionObjectName_("")
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
	
	HitBox collShape({2,2,2});
	Collider coll({ 0,-5,0 });
	coll.SetCollider(collShape);
	coll.SetAttachObject(this);
	AddComponent<Collider>(coll);

	Text noticeText(this);
	noticeText.SetText("Name");
	TEXT_RECT rect = { 0,0,1000,500 };
	noticeText.SetRect(rect);
	noticeText.SetColor({ 0,0,0,1 });
	AddComponent<Text>(noticeText);
	transform_->position_ = XMVectorSet(0, 10, 0, 0);
	CameraManager::GetCamera(0).SetPosition(this->transform_->position_);
	CameraManager::GetCamera(0).SetTarget(XMVectorSet(0,10,1,0));
}

void Player::Start()
{
	UIManagerObject_ = FindObject("Play_UIManager");
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
	
	if (VectorLength(moveVec_) >= speed_)
	{
		XMFLOAT3 moveBuff = StoreFloat3(XMVector3Rotate(moveVec_, transform_->rotate_));
		moveBuff.y = 0;
		moveVec_ = XMLoadFloat3(&moveBuff);

		transform_->position_ += XMVector3Normalize(moveVec_)*0.1f;
		CameraManager::GetCamera(0).SetPosition(this->transform_->position_);
		moveVec_ = XMVectorSet(0, 0, 0, 0);
	}
	CameraControll();


	//Š÷‚©’I‚©ƒhƒA‚É“–‚½‚Á‚Ä‚¢‚½‚ç
	if (GetComponent<Collider>().IsHit())
	{
		UIManagerObject_->FindChild("Play_ManagementPart_BaseUI")->GetComponent<Text>().SetText(collisionObjectName_);
		//((Play_ManagementPart_BaseUI*)UIManagerObject_->FindChild("Play_ManagementPart_BaseUI"))->SetUINum()
		//
		if(Input::IsKeyDown(DIK_F))
		{
			((Play_ManagementPart_BaseUI*)UIManagerObject_->FindChild("Play_ManagementPart_BaseUI"))->AccessUI(collisionUINum_);
		}
		
	}
	else
		UIManagerObject_->FindChild("Play_ManagementPart_BaseUI")->GetComponent<Text>().SetText("");
}
void Player::CameraControll()
{
	XMFLOAT3 rotate = { 0,0,0 };
	rotate = StoreFloat3(Input::GetMouseMove()*0.03f);
	cameraRotate_.x += rotate.x;
	cameraRotate_.y += rotate.y;
	cameraRotate_.y = Clamp<float>(cameraRotate_.y, rotateDownerLimitY_, rotateUperLimitY_);
	transform_->RotateEular(cameraRotate_.y, cameraRotate_.x, 0);//RotateEular(XMConvertToDegrees(cameraRotate_.y), XMConvertToDegrees(cameraRotate_.x*10), 0);
	//XMFLOAT3 pos = CameraManager::GetCamera(0).GetPosition();
	//GetComponent<Text>().SetText("\nX:" + std::to_string(pos.x) +
	//	"\nY:" + std::to_string(pos.y) +
	//	"\nZ:" + std::to_string(pos.z));
	
	CameraManager::GetCamera(0).SetTarget(transform_->position_ + transform_->GetFront());
}
void Player::Release()
{
}

void Player::OnCollisionStay(GameObject* pTarget)
{
	//XMFLOAT3 pos = StoreFloat3(transform_->position_);
	//GetComponent<Text>().SetText(pTarget->GetObjectName() +
	//	"\nX:" + std::to_string(pos.x) +
	//	"\nY:" + std::to_string(pos.y) +
	//	"\nZ:" + std::to_string(pos.z));
	//GetComponent<Text>().SetText("Exit");
	collisionObjectName_ = ((ManagementPartObjectBase*)pTarget)->GetActionName();
	collisionUINum_ = ((ManagementPartObjectBase*)pTarget)->GetAccessUINumber();
	//UIManagerObject_->FindChild("Play_ManagementPart_BaseUI")->GetComponent<Text>().SetText(pTarget->GetObjectName());
	//GetComponent<Text>().SetText(pTarget->GetObjectName());
}

void Player::OnCollisionExit(GameObject* pTarget)
{
}

//void Player::OnCollision(Object* pTarget)
//{
//
//		XMFLOAT3 pos = StoreFloat3(transform_->position_);
//		GetComponent<Text>().SetText(pTarget->GetObjectName() +
//									 "\nX:" + std::to_string(pos.x) +
//									 "\nY:" + std::to_string(pos.y) +
//									 "\nZ:" + std::to_string(pos.z));
//	//if (pTarget->GetObjectName() == "Play_ManagementPart_Shelf")
//	//{
//	//	XMFLOAT3 pos = StoreFloat3(transform_->position_);
//	//	GetComponent<Text>().SetText(pTarget->GetObjectName()+
//	//								 "\nX:"+std::to_string(pos.x)+
//	//								 "\nY:"+std::to_string(pos.y)+
//	//								 "\nZ:"+std::to_string(pos.z));
//	//}
//	//else if(pTarget->GetObjectName() == "Play_ManagementPart_CraftTable")
//	//{
//	//
//	//}
//
//
//}
