#include "P_MP_SettlementUI_PotionList.h"
#include"Engine/Systems/ImageSystem.h"
#include"Engine/Systems/TextSystem.h"
#include"P_MP_SettiementUI_Potion.h"
#include"Engine/DirectX_11/Input.h"

P_MP_SettlementUI_PotionList::P_MP_SettlementUI_PotionList(Object* parent)
	:GameObject(parent,"P_MP_SettlementUI_PotionList"),
	uiPos_({ -0.6f,0.0f,0 }),
	move_(0),
	scrollSpeed_(0.1f)
{
}

P_MP_SettlementUI_PotionList::~P_MP_SettlementUI_PotionList()
{
}

void P_MP_SettlementUI_PotionList::Initialize()
{
	Image back(this);
	back.Load("Assets/Image/UIBaseImage2.png");
	back.SetSize({ 9,15,0 });
	back.SetPosition({ -0.6f,0.0f,0 });
	AddComponent<Image>(back);

	CreateListUI();
}

void P_MP_SettlementUI_PotionList::Start()
{
}

void P_MP_SettlementUI_PotionList::Update()
{
	float scroll = -XMVectorGetZ(XMVector3Normalize(Input::GetMouseMove()))* scrollSpeed_;
	if (GetComponent<Image>().IsHitCursor() && abs(scroll)>=0.1f)
	{
		move_ += scroll;
		move_ = Clamp(move_, 0.0f, 0.8f);
		for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
		{
			((P_MP_SettiementUI_Potion*)itr->get())->AddPosition(move_);
		}
	}

}

void P_MP_SettlementUI_PotionList::CreateListUI()
{
	XMFLOAT3 potionPos = { 0,0.6f,0 };
	for (int i=0;i<5;i++/*PlayerData::PotionData data : potionDataList_*/)
	{
		//if (data.isSale_)
		//{
			P_MP_SettiementUI_Potion* potion = Instantiate<P_MP_SettiementUI_Potion>(this);
			potion->SetPotionData(1, "Potion", { 1,1,1 }, 100);
			potion->SetFirstPosition({ uiPos_.x + potionPos.x,uiPos_.y + potionPos.y,0 });
			potionPos.y -= 0.5f;
		//}
	}
}

void P_MP_SettlementUI_PotionList::Release()
{
}