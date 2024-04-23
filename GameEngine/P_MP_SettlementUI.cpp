#include "P_MP_SettlementUI.h"
#include"InterSceneData.h"
#include"Engine/Systems/ImageSystem.h"
#include"P_MP_SettiementUI_Potion.h"
P_MP_SettlementUI::P_MP_SettlementUI(Object* parent)
	:GameObject(parent,"P_MP_SettlementUI")
{
}

P_MP_SettlementUI::~P_MP_SettlementUI()
{
}

void P_MP_SettlementUI::Initialize()
{
	Image backImage(this);
	backImage.Load("Assets/Image/PotionManagerUIBase1.png");
	backImage.SetSize({ 2,2,0 });
	AddComponent<Image>(backImage);

	//potionDataList_ = InterSceneData::GetData<PlayerData>("Data01")->potionDataList_;

	CreateResoultUI();
}

void P_MP_SettlementUI::Start()
{
}

void P_MP_SettlementUI::Update()
{
}

void P_MP_SettlementUI::CreateResoultUI()
{
	XMFLOAT3 potionPos = { -0.7f,0.6f,0 };
	for (int i=0;i<5;i++/*PlayerData::PotionData data : potionDataList_*/)
	{
		//if (data.isSale_)
		//{
			P_MP_SettiementUI_Potion* potion = Instantiate<P_MP_SettiementUI_Potion>(this);
			potion->SetPotionData(1, "Potion", { 1,1,1 }, 100);
			potion->SetPosition(potionPos);
			//Image potion(this);
			//potion.Load("Assets/Image/Potion_BaseImage.png");
			//potion.SetSize({ 0.25f,0.25f,0 });
			//potion.SetColor(data.potionColor_);
			//potion.SetPosition(potionPos);
			//AddComponent<Image>(potion);
			potionPos.y -= 0.5f;
		//}
	}
}

void P_MP_SettlementUI::Release()
{
}
