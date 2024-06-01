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
	//hAudio_Move_ = AudioManager::Load("Assets/Audio/Walk01.wav");
	//hAudio_ItemGet_ = AudioManager::Load("Assets/Audio/Confirm34.wav",false,1.0f,3);
}

void Player_CollectionPart::Start()
{
	SetUIManager(FindObject("Play_UIManager"));
	ground_ = (CollectionPart_Ground*)FindObject("CollectionPart_Ground");
	//uiManager_ = (Play_UIManager*)FindObject("Play_UIManager");
}

void Player_CollectionPart::Update()
{
	if (CanControll())
	{
		XMVECTOR pos = transform_->position_;
		MoveControll();

		int itemNum = itemGetter_->GetItemNumber();

		//ƒAƒCƒeƒ€”Ô†‚ª0ˆÈã‚¾‚Á‚½‚ç
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

void Player_CollectionPart::MoveControll()
{
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
	if (VectorLength(GetMoveVec()) >= 0.01f)
	{

		GetComponent<Audio>(hAudio_Move_).Play();
		XMFLOAT3 moveBuff = StoreFloat3(XMVector3Rotate(GetMoveVec(), transform_->rotate_));

		XMFLOAT3 pos = StoreFloat3(transform_->position_);

		RayCastData data;
		data.start = StoreFloat3(XMVectorSet(pos.x + moveBuff.x, 999, pos.z + moveBuff.z, 0));
		data.dir = StoreFloat3(XMVectorSet(0, -1, 0, 0));

		ground_->GetComponent<Test_Model_ECSver>().RayCast(data);
		moveBuff.y = 0;

		if (data.hit)
		{
			pos = StoreFloat3(data.hitPos);
			pos.y += 10;
			//GetMoveVec() = XMLoadFloat3(&moveBuff);
			transform_->position_ = XMLoadFloat3(&pos);//XMVector3Normalize(GetMoveVec()) * GetSpeed();
			CameraManager::GetCamera(0).SetPosition(this->transform_->position_);
		}
		GetMoveVec() = XMVectorSet(0, 0, 0, 0);
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

void Player_CollectionPart::Release()
{
}
