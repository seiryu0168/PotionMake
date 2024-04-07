#include "P_MP_PotionManagerUI_PotionStockUI.h"
#include"Engine/Systems/ImageSystem.h"
#include"Engine/Systems/TextSystem.h"
#include"PotionStock.h"
#include"InterSceneData.h"
#include"PlayerData.h"
#include"PotionMenu.h"
P_MP_PotionManagerUI_PotionStockUI::P_MP_PotionManagerUI_PotionStockUI(Object* parent)
	:GameObject(parent,"P_MP_PotionManagerUI_PotionStockUI"),
	potionImageBasePos_({0.1f,0.6f})
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
	//int i = 0;
	XMFLOAT2 diff = { 0,0 };
	for (int i=0;i<30;i++)
	{
		PotionStock* stock = Instantiate<PotionStock>(this);
		stock->GetComponent<Image>().SetPosition({ potionImageBasePos_.x + diff.x,potionImageBasePos_.y + diff.y,0 });

		if (i < data->potionDataList_.size())
		{

			//ポーションの各データを入れる
			stock->SetPotionStatus_(i, data->potionDataList_[i].potionName_,
									   data->potionDataList_[i].potionStatus_[0],
									   data->potionDataList_[i].potionStatus_[1],
									   data->potionDataList_[i].potionStatus_[2],
									   data->potionDataList_[i].potionStatus_[3],
									   data->potionDataList_[i].potionStatus_[4]);
		}
		potionList_.push_back(stock);
		diff.x += 0.15f;
		if ((i + 1) % 5 == 0)
		{
			diff.x = 0;
			diff.y -= 0.3f;
		}
	}
}

void P_MP_PotionManagerUI_PotionStockUI::CreatePotionMenu(int potionNum, const std::string& name, const XMFLOAT3& color)
{
	GameObject* potionMenu = Instantiate<PotionMenu>(this);
	potionMenu->GetComponent<Image>().SetPosition({ 0.5f,0,0 });
	((PotionMenu*)potionMenu)->CreateMenu(potionNum, name, color);
}

void P_MP_PotionManagerUI_PotionStockUI::SetEnablePotionStock(bool isEnable)
{
	for (auto potion : potionList_)
	{
			((PotionStock*)potion)->isSelect_ = isEnable;
	}
}

void P_MP_PotionManagerUI_PotionStockUI::Release()
{
}
