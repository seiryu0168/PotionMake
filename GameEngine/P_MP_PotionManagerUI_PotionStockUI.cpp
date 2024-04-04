#include "P_MP_PotionManagerUI_PotionStockUI.h"
#include"Engine/Systems/ImageSystem.h"
#include"Engine/Systems/TextSystem.h"
#include"PotionStock.h"
#include"InterSceneData.h"
#include"PlayerData.h"
P_MP_PotionManagerUI_PotionStockUI::P_MP_PotionManagerUI_PotionStockUI(Object* parent)
	:GameObject(parent,"P_MP_PotionManagerUI_PotionStockUI")
{
}

P_MP_PotionManagerUI_PotionStockUI::~P_MP_PotionManagerUI_PotionStockUI()
{
}

void P_MP_PotionManagerUI_PotionStockUI::Initialize()
{
	Image uiBaseImage(this);
	uiBaseImage.Load("Assets/Image/PotionManagerUIBase1.png");
	uiBaseImage.SetPosition({ 0.45f,-0.1f,0 });
	uiBaseImage.SetSize({ 1,0.8f,0 });
	AddComponent<Image>(uiBaseImage);

	InputPotionData();
}

void P_MP_PotionManagerUI_PotionStockUI::Start()
{
}

void P_MP_PotionManagerUI_PotionStockUI::Update()
{
}

void P_MP_PotionManagerUI_PotionStockUI::InputPotionData()
{
	PlayerData* data = InterSceneData::GetData<PlayerData>("Data01");
	int i = 0;
	for (auto &potion : data->potionDataList_)
	{
		PotionStock* stock = Instantiate<PotionStock>(this);
		//ポーションの各データを入れる
		stock->SetPotionStatus_(i, potion.potionName_, potion.potionStatus_[0],
													   potion.potionStatus_[1],
													   potion.potionStatus_[2],
													   potion.potionStatus_[3],
													   potion.potionStatus_[4]);
	}
}

void P_MP_PotionManagerUI_PotionStockUI::Release()
{
}
