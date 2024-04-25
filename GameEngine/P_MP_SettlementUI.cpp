#include "P_MP_SettlementUI.h"
#include"InterSceneData.h"
#include"Engine/Systems/ImageSystem.h"
#include"P_MP_SettlementUI_PotionList.h"
#include"P_MP_SettlementUI_TotalGain.h"
#include"SettlementUI_EarningTransition.h"
#include"InterSceneData.h"
#include"PlayerData.h"
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
	backImage.Load("Assets/Image/UIBaseImage2.png");
	//backImage.SetColor({ 0,0,0 });
	backImage.SetSize({ 32,20,0 });
	AddComponent<Image>(backImage);
	int totalGain = 0;
	PlayerData& pData = *InterSceneData::GetData<PlayerData>("Data01");
	for (PlayerData::PotionData& potionData : pData.potionDataList_)
	{
		if(potionData.isSale_)
		totalGain += potionData.price_*5;
	}
	Instantiate<P_MP_SettlementUI_TotalGain>(this)->SetData(totalGain,"ëÂê∑ãµ!");
	Instantiate<SettlementUI_EarningTransition>(this)->SetData({100,300,500,200,600});
	Instantiate<P_MP_SettlementUI_PotionList>(this)->CreateListUI(pData.potionDataList_);
	//potionDataList_ = InterSceneData::GetData<PlayerData>("Data01")->potionDataList_;

	//CreateResoultUI();
}

void P_MP_SettlementUI::Start()
{
}

void P_MP_SettlementUI::Update()
{
}

void P_MP_SettlementUI::CreateResoultUI()
{
	//XMFLOAT3 potionPos = { -0.7f,0.6f,0 };
	//for (int i=0;i<5;i++/*PlayerData::PotionData data : potionDataList_*/)
	//{
	//	//if (data.isSale_)
	//	//{
	//		P_MP_SettiementUI_Potion* potion = Instantiate<P_MP_SettiementUI_Potion>(this);
	//		potion->SetPotionData(1, "Potion", { 1,1,1 }, 100);
	//		potion->SetPosition(potionPos);
	//		//Image potion(this);
	//		//potion.Load("Assets/Image/Potion_BaseImage.png");
	//		//potion.SetSize({ 0.25f,0.25f,0 });
	//		//potion.SetColor(data.potionColor_);
	//		//potion.SetPosition(potionPos);
	//		//AddComponent<Image>(potion);
	//		potionPos.y -= 0.5f;
	//	//}
	//}
}

void P_MP_SettlementUI::Release()
{
}
