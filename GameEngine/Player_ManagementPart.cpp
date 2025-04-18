#include "Player_ManagementPart.h"
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
#include"Engine/ResourceManager/AudioManager.h"
Player_ManagementPart::Player_ManagementPart(Object* parent)
	:Player(parent,"Player_ManagementPart"),
	canMoveArea_({18,20}),
	hAudio_Move_(-1)
{
}

Player_ManagementPart::~Player_ManagementPart()
{
}

void Player_ManagementPart::Initialize()
{
	HitBox collShape({ 3,2,3 });
	Collider coll({ 0,-5,0 });
	coll.SetCollider(collShape);
	coll.SetAttachObject(this);
	AddComponent<Collider>(coll);

	transform_->position_ = XMVectorSet(0, 10, 0, 0);
	CameraManager::GetCamera(0).SetPosition(this->transform_->position_);
	CameraManager::GetCamera(0).SetTarget(XMVectorSet(0, 10, 1, 0));

	hAudio_Move_ = AudioManager::Load("Assets/Audio/Walk01.wav");
}

void Player_ManagementPart::Start()
{
	SetUIManager(FindObject("Play_UIManager"));
}

void Player_ManagementPart::Update()
{
	if (CanControll())
	{

		if (((Play_UIManager*)GetUIManager())->IsAccessUI())
			return;
		MoveControll();


		CameraControll();


		//机か棚かドアに当たっていたら
		{
			//Collider colll= GetComponent<Collider>();
		}
		if (GetComponent<Collider>().IsHit())
		{
			((Play_ManagementPart_BaseUI*)GetUIManager()->FindChild("Play_ManagementPart_BaseUI"))->DisplayAction(collisionObjectName_, true);//->GetComponent<Text>().SetText(collisionObjectName_);

			if (Input::IsKeyDown(DIK_F))
			{
				((Play_UIManager*)GetUIManager())->AccessUI(collisionUINum_);
			}

		}
		else
			((Play_ManagementPart_BaseUI*)GetUIManager()->FindChild("Play_ManagementPart_BaseUI"))->DisplayAction("", false);
	}
	else
		((Play_ManagementPart_BaseUI*)GetUIManager()->FindChild("Play_ManagementPart_BaseUI"))->DisplayAction("", false);
}

void Player_ManagementPart::MoveControll()
{
	//前後左右
	if (Input::IsKey(DIK_W))
	{
		GetMoveVec() += XMVectorSet(0, 0, GetSpeed(), 0);
	}
	if (Input::IsKey(DIK_A))
	{
		GetMoveVec() += XMVectorSet(-GetSpeed(), 0, 0, 0);
	}
	if (Input::IsKey(DIK_S))
	{
		GetMoveVec() += XMVectorSet(0, 0, -GetSpeed(), 0);
	}
	if (Input::IsKey(DIK_D))
	{
		GetMoveVec() += XMVectorSet(GetSpeed(), 0, 0, 0);
	}
	
	//動きがあったら
	if (VectorLength(GetMoveVec()) >= 0.01f)
	{
		//足音
		AudioManager::Play(hAudio_Move_);
		
		////////プレイヤーが進む処理////////
		XMFLOAT3 moveBuff = StoreFloat3(XMVector3Rotate(GetMoveVec(), transform_->rotate_));
		moveBuff.y = 0;
		GetMoveVec() = XMLoadFloat3(&moveBuff);

		transform_->position_ += XMVector3Normalize(GetMoveVec()) * GetSpeed();
		GetMoveVec() = XMVectorSet(0, 0, 0, 0);
		XMFLOAT3 pos = StoreFloat3(transform_->position_);
		pos.x = Clamp(pos.x, -canMoveArea_.x, canMoveArea_.x);
		pos.z = Clamp(pos.z, -canMoveArea_.y, canMoveArea_.y);
		transform_->position_ = XMVectorSet(pos.x, pos.y, pos.z, 0);
		CameraManager::GetCamera(0).SetPosition(this->transform_->position_);
		///////////////////////////////////
	}
	else
		AudioManager::Stop(hAudio_Move_);
}

void Player_ManagementPart::Release()
{
}

void Player_ManagementPart::OnCollisionStay(GameObject* pTarget)
{
	//当たってるオブジェクトの情報を取得
	collisionObjectName_ = ((ManagementPartObjectBase*)pTarget)->GetActionName();
	collisionUINum_ = ((ManagementPartObjectBase*)pTarget)->GetAccessUINumber();
}
