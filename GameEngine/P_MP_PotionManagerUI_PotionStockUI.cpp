#include "P_MP_PotionManagerUI_PotionStockUI.h"
#include"Engine/Systems/ImageSystem.h"
#include"Engine/Systems/TextSystem.h"
#include"PotionStock.h"
#include"PotionStockDummy.h"
#include"InterSceneData.h"
#include"PlayerData.h"
#include"PotionMenu.h"
#include"PotionManagementConfirmButton.h"
#include"P_MP_PotionManagerUI_SellStockUI.h"
#include"P_MP_PotionManagerUI_DisposeStockUI.h"
P_MP_PotionManagerUI_PotionStockUI::P_MP_PotionManagerUI_PotionStockUI(Object* parent)
	:GameObject(parent,"P_MP_PotionManagerUI_PotionStockUI"),
	potionImageBasePos_({-0.1f,0.48f})
{
}

P_MP_PotionManagerUI_PotionStockUI::~P_MP_PotionManagerUI_PotionStockUI()
{
}

void P_MP_PotionManagerUI_PotionStockUI::Initialize()
{
	Image uiBaseImage(this);
	uiBaseImage.Load("Assets/Image/PotionManagerUIBase1.png");
	uiBaseImage.SetPosition({ 0.35f,-0.1f,0 });
	uiBaseImage.SetSize({ 1,0.8f,0 });
	AddComponent<Image>(uiBaseImage);

	InputPotionData();
	GameObject* confirmButton = Instantiate<PotionManagementConfirmButton>(this);
	confirmButton->GetComponent<Image>().SetPosition({ 0.7f,-0.7f,0 });
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
		GameObject* stock;
		if (i < data->potionDataList_.size())
		{
			stock = Instantiate<PotionStock>(this);
			stock->GetComponent<Image>().SetPosition({ potionImageBasePos_.x + diff.x,potionImageBasePos_.y + diff.y,0 });

			//ポーションの各データを入れる
			((PotionStock*)stock)->SetPotionStatus_(i, data->potionDataList_[i].potionName_,
				data->potionDataList_[i].isSale_,
				data->potionDataList_[i].potionStatus_[0],
				data->potionDataList_[i].potionStatus_[1],
				data->potionDataList_[i].potionStatus_[2],
				data->potionDataList_[i].potionStatus_[3],
				data->potionDataList_[i].potionStatus_[4]);
			potionList_.push_back(stock);
		}
		else
		{
			stock = Instantiate<PotionStockDummy>(this);
			stock->GetComponent<Image>().SetPosition({ potionImageBasePos_.x + diff.x,potionImageBasePos_.y + diff.y,0 });
		}
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
	//GameObject* potionMenu = Instantiate<PotionMenu>(this);
	//potionMenu->GetComponent<Image>().SetPosition({ 0.5f,0,0 });
	//((PotionMenu*)potionMenu)->CreateMenu(potionNum, name, color);
}

void P_MP_PotionManagerUI_PotionStockUI::ConfirmPotionManagement()
{
	
	//((P_MP_PotionManagerUI_SellStockUI*)FindObject("P_MP_PotionManagerUI_SellStockUI"))->
	//((P_MP_PotionManagerUI_DisposeStockUI*)FindObject("P_MP_PotionManagerUI_SellStockUI"))->
	
	std::vector<PlayerData::PotionData> newPotionDataList;
	for (int i = 0; i < potionList_.size(); i++)
	{
		if (((PotionStock*)potionList_[i])->GetPotionNumber() != -1 && ((PotionStock*)potionList_[i])->GetSelectedSlot() != PotionStock::SelectSlot::Dispose)
		{
			PlayerData::PotionData pData;
			pData.potionName_ = ((PotionStock*)potionList_[i])->GetPotionName();
			pData.potionStatus_ = ((PotionStock*)potionList_[i])->GetPotionStatus();
			if (((PotionStock*)potionList_[i])->GetSelectedSlot() == PotionStock::SelectSlot::Sell)
				pData.isSale_ = true;
			newPotionDataList.push_back(pData);
		}

	}
	
	PlayerData* data = InterSceneData::GetData<PlayerData>("Data01");
	data->potionDataList_ = newPotionDataList;

	pParent_->KillMe();
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
