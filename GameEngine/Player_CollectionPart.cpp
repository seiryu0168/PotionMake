#include "Player_CollectionPart.h"
#include"Engine/Systems/ModelSystem.h"
#include"Engine/GameObject/CameraManager.h"
#include"Engine/DirectX_11/Input.h"
#include"CollectionPart/P_CP_Player_ItemGetter.h"
#include"CollectionPart/CollectionPart_Ground.h"
#include"Play_UIManager.h"
#include"CollectionPart/Play_CollectionPart_BaseUI.h"
#include"Engine/ResourceManager/AudioManager.h"
#include"Engine/Systems/AudioSystem.h"
namespace
{
	float ItemGetterMaxDist = 18.0f;
	float DashSpeedRatio = 2.0f;
}
Player_CollectionPart::Player_CollectionPart(Object* parent)
	:Player(parent,"Player_CollectionPart"),
	ground_(nullptr),
	hAudio_ItemGet_(-1),
	hAudio_Move_(-1),
	itemGetter_(nullptr)
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

	Audio moveAudio(this);
	moveAudio.Load("Assets/Audio/Walk01.wav");
	hAudio_Move_ = AddComponent<Audio>(moveAudio);
	Audio itemGetAudio(this);
	itemGetAudio.Load("Assets/Audio/Confirm34.wav", false, 1.0f, 5);
	hAudio_ItemGet_ = AddComponent<Audio>(itemGetAudio);
}

void Player_CollectionPart::Start()
{
	SetUIManager(FindObject("Play_UIManager"));
	ground_ = (CollectionPart_Ground*)FindObject("CollectionPart_Ground");
}

void Player_CollectionPart::Update()
{
	if (CanControll())
	{
		XMVECTOR pos = transform_->position_;
		MoveControll();

		int itemNum = itemGetter_->GetItemNumber();

		//アイテム番号が0以上だったら
		if (itemNum >= 0)
		{
			((Play_CollectionPart_BaseUI*)GetUIManager()->FindChild("Play_CollectionPart_BaseUI"))->DisplayItemName(itemNum);
			if (Input::IsMouseButtonDown(0))
			{
				GetComponent<Audio>(hAudio_ItemGet_).Play();
				AddItem(itemNum);
				itemGetter_->KillHitObject();
			}
		}
		else
			((Play_CollectionPart_BaseUI*)GetUIManager()->FindChild("Play_CollectionPart_BaseUI"))->	HiddenItemName();
		
		//カメラの動き
		CameraControll();
		
		//プレイヤーの位置
		RayCastData data;
		data.start = StoreFloat3(transform_->position_);
		data.dir = StoreFloat3(transform_->GetFront());
		ground_->GetComponent<Test_Model_ECSver>().RayCast(data);
		if (data.hit && data.dist <= ItemGetterMaxDist)
		{
			itemGetter_->GetTransform()->position_ = data.hitPos;
		}
		else itemGetter_->GetTransform()->position_ = XMVectorSet(0, 999, 0, 0);
	}
}

void Player_CollectionPart::MoveControll()
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
	
	//動きがあるなら
	if (VectorLength(GetMoveVec()) >= 0.01f)
	{
		//ダッシュ
		if (Input::IsKey(DIK_LSHIFT))
			GetMoveVec() *= DashSpeedRatio;
		
		//足音
		GetComponent<Audio>(hAudio_Move_).Play();
		
		////////プレイヤーが進む処理////////
		XMFLOAT3 moveBuff = StoreFloat3(XMVector3Rotate(GetMoveVec(), transform_->rotate_));
		XMFLOAT3 pos = StoreFloat3(transform_->position_);

		RayCastData data;
		data.start = StoreFloat3(XMVectorSet(pos.x + moveBuff.x, 999, pos.z + moveBuff.z, 0));
		data.dir = StoreFloat3(XMVectorSet(0, -1, 0, 0));

		//レイキャストで地面判定
		ground_->GetComponent<Test_Model_ECSver>().RayCast(data);
		moveBuff.y = 0;
		//当たってたら
		if (data.hit)
		{
			//当たった場所からy方向に＋10
			pos = StoreFloat3(data.hitPos);
			pos.y += 10;
			
			transform_->position_ = XMLoadFloat3(&pos);
			CameraManager::GetCamera(0).SetPosition(this->transform_->position_);
		}
		GetMoveVec() = XMVectorSet(0, 0, 0, 0);
		////////////////////////////////////
	}
}

void Player_CollectionPart::AddItem(int itemNum)
{
	if (itemCount_.find(itemNum) == itemCount_.end())
		itemCount_.insert({ itemNum, 1 });
	else
	{
		itemCount_[itemNum]++;
	}
}

void Player_CollectionPart::Release()
{
}
