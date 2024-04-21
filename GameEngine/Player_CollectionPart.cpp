#include "Player_CollectionPart.h"
#include"Engine/Systems/ModelSystem.h"
#include"Engine/GameObject/CameraManager.h"
#include"Engine/DirectX_11/Input.h"
#include"P_CP_Player_ItemGetter.h"
#include"CollectionPart_Ground.h"
#include"Play_UIManager.h"
#include"Play_CollectionPart_BaseUI.h"
Player_CollectionPart::Player_CollectionPart(Object* parent)
	:Player(parent,"Player_CollectionPart"),
	canControl_(true)
{
}

Player_CollectionPart::~Player_CollectionPart()
{
}

void Player_CollectionPart::Initialize()
{
	transform_->position_ = XMVectorSet(0, 10, 0, 0);
	CameraManager::GetCamera(0).SetPosition(this->transform_->position_);
	CameraManager::GetCamera(0).SetTarget(XMVectorSet(0, 10, 1, 0));

	itemGetter_ = Instantiate<P_CP_Player_ItemGetter>(pParent_);
}

void Player_CollectionPart::Start()
{
	SetUIManager(FindObject("Play_UIManager"));
	ground_ = (CollectionPart_Ground*)FindObject("CollectionPart_Ground");
	uiManager_ = (Play_UIManager*)FindObject("Play_UIManager");
}

void Player_CollectionPart::Update()
{
	if (canControl_)
	{

		MoveControll();

		int itemNum = itemGetter_->GetItemNumber();

		if (itemNum >= 0)
		{
			((Play_CollectionPart_BaseUI*)uiManager_->FindChild("Play_CollectionPart_BaseUI"))->DisplayItemName(itemNum);
			if (Input::IsMouseButtonDown(0))
			{
				AddItem(itemNum);
				itemGetter_->KillHitObject();
			}
		}
		else
			((Play_CollectionPart_BaseUI*)uiManager_->FindChild("Play_CollectionPart_BaseUI"))->HiddenItemName();

		CameraControll();

		RayCastData data;
		data.start = StoreFloat3(transform_->position_);
		data.dir = StoreFloat3(transform_->GetFront());
		ground_->GetComponent<Test_Model_ECSver>().RayCast(data);
		if (data.hit && data.dist <= 15.0f)
		{
			itemGetter_->GetTransform()->position_ = data.hitPos;
		}
	}
}

void Player_CollectionPart::AddItem(int itemNum)
{
	//auto itemData = itemCount_.find(itemNum);
	if (itemCount_.find(itemNum) == itemCount_.end())
		itemCount_.insert({ itemNum, 1 });
	else
	{
		itemCount_[itemNum]++;
	}
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
