#include "P_MP_PotionManagerUI_PotionStockUI.h"
#include"../../Engine/Systems/ImageSystem.h"
#include"../../Engine/Systems/TextSystem.h"
#include"PotionStock.h"
#include"PotionStockDummy.h"
#include"../../InterSceneData.h"
#include"../../PlayerData.h"
#include"PotionMenu.h"
#include"PotionManagementConfirmButton.h"
#include"P_MP_PotionManagerUI_SellStockUI.h"
#include"P_MP_PotionManagerUI_DisposeStockUI.h"
P_MP_PotionManagerUI_PotionStockUI::P_MP_PotionManagerUI_PotionStockUI(Object* parent)
	:GameObject(parent,"P_MP_PotionManagerUI_PotionStockUI"),
	potionImageBasePos_({-0.024f,0.453f}),
	uiPos_({ 0.35f,-0.1f,0 })
{
}

P_MP_PotionManagerUI_PotionStockUI::~P_MP_PotionManagerUI_PotionStockUI()
{
}

void P_MP_PotionManagerUI_PotionStockUI::Initialize()
{
	//Image uiBaseImage(this);
	//uiBaseImage.Load("Assets/Image/PotionManagerUIBase1.png");
	//uiBaseImage.SetPosition(uiPos_);
	//uiBaseImage.SetSize({ 1,0.8f,0 });
	//AddComponent<Image>(uiBaseImage);

	CreateBase();

	InputPotionData();
	Instantiate<PotionManagementConfirmButton>(this);
	//GameObject* confirmButton = 
	//confirmButton->GetComponent<Image>().SetPosition({ 0.7f,-0.7f,0 });
}

void P_MP_PotionManagerUI_PotionStockUI::Start()
{
}

void P_MP_PotionManagerUI_PotionStockUI::Update()
{
}

void P_MP_PotionManagerUI_PotionStockUI::InputPotionData()
{
	//セーブデータを取り出す
	PlayerData* data = InterSceneData::GetData<PlayerData>("Data01");
	//int i = 0;
	XMFLOAT2 diff = { 0,0 };
	//セーブデータにあるデータを元にポーションの画像を並べていく
	for (int i=0;i<30;i++)
	{
		GameObject* stock;
		if (i < data->potionDataList_.size())
		{
			stock = Instantiate<PotionStock>(this);
			stock->GetComponent<Image>().SetPosition({ potionImageBasePos_.x + diff.x,potionImageBasePos_.y + diff.y,0 });

			//ポーションの各データを入れる
			((PotionStock*)stock)->SetPotionStatus_(i,
				data->potionDataList_[i].potionName_,
				data->potionDataList_[i].isSale_,
				data->potionDataList_[i].topStatus_,
				data->potionDataList_[i].price_,
				data->potionDataList_[i].potionColor_,
				data->potionDataList_[i].potionStatus_[0],
				data->potionDataList_[i].potionStatus_[1],
				data->potionDataList_[i].potionStatus_[2],
				data->potionDataList_[i].potionStatus_[3],
				data->potionDataList_[i].potionStatus_[4]);
			potionList_.push_back(stock);
		}
		//ポーションのデータが無くなった時のダミー
		else
		{
			stock = Instantiate<PotionStockDummy>(this);
			stock->GetComponent<Image>().SetPosition({ potionImageBasePos_.x + diff.x,potionImageBasePos_.y + diff.y,0 });
		}
		diff.x += 0.15f;
		if ((i + 1) % 6 == 0)
		{
			diff.x = 0;
			diff.y -= 0.28f;
		}
	}
}

void P_MP_PotionManagerUI_PotionStockUI::CreateBase()
{
	XMFLOAT3 windowSize;
	XMFLOAT3 imageRatio;
	Image uiBaseImage(this);
	uiBaseImage.Load("Assets/Image/UIBaseImage2.png");
	uiBaseImage.SetPosition({ uiPos_.x,uiPos_.y,0 });
	uiBaseImage.SetSize({ 16 * 0.9f,16 * 0.8f,0 });
	windowSize = uiBaseImage.GetSizeAtPixel();
	imageRatio = uiBaseImage.GetSize();
	AddComponent<Image>(uiBaseImage);

	windowSize = { windowSize.x / (Direct3D::GetScreenWidth()),
				   windowSize.y / (Direct3D::GetScreenHeight()),0 };
	
	Image uiWidthEdgeImage1(this);
	uiWidthEdgeImage1.Load("Assets/Image/UIEdge_Width.png");
	uiWidthEdgeImage1.SetPosition({ uiPos_.x,uiPos_.y + windowSize.y * 0.95f,0 });
	uiWidthEdgeImage1.SetSize({ imageRatio.x * 0.95f,0.3f,0 });
	AddComponent<Image>(uiWidthEdgeImage1);
	Image uiWidthEdgeImage2(this);
	uiWidthEdgeImage2.Load("Assets/Image/UIEdge_Width.png");
	uiWidthEdgeImage2.SetPosition({ uiPos_.x,uiPos_.y - windowSize.y * 0.95f,0 });
	uiWidthEdgeImage2.SetSize({ imageRatio.x * 0.95f,0.3f,0 });
	AddComponent<Image>(uiWidthEdgeImage2);

	Image uiHeightEdgeImage1(this);
	uiHeightEdgeImage1.Load("Assets/Image/UIEdge_Height.png");
	uiHeightEdgeImage1.SetPosition({ uiPos_.x + windowSize.x * 0.95f,uiPos_.y,0 });
	uiHeightEdgeImage1.SetSize({ 0.3f,imageRatio.y * 0.95f,0 });
	AddComponent<Image>(uiHeightEdgeImage1);
	Image uiHeightEdgeImage2(this);
	uiHeightEdgeImage2.Load("Assets/Image/UIEdge_Height.png");
	uiHeightEdgeImage2.SetPosition({ uiPos_.x - windowSize.x * 0.95f,uiPos_.y,0 });
	uiHeightEdgeImage2.SetSize({ 0.3f,imageRatio.y * 0.95f,0 });
	AddComponent<Image>(uiHeightEdgeImage2);

	Image uiCornerImage1(this);
	uiCornerImage1.Load("Assets/Image/UIEdge_Corner.png");
	uiCornerImage1.SetPosition({ uiPos_.x + windowSize.x * 0.95f,uiPos_.y + windowSize.y * 0.951f,0 });
	uiCornerImage1.SetSize({ 0.3f,0.3f,0 });
	AddComponent<Image>(uiCornerImage1);

	Image uiCornerImage2(this);
	uiCornerImage2.Load("Assets/Image/UIEdge_Corner.png");
	uiCornerImage2.SetPosition({ uiPos_.x + windowSize.x * 0.9495f,uiPos_.y - windowSize.y * 0.951f,0 });
	uiCornerImage2.SetSize({ 0.3f,0.3f,0 });
	uiCornerImage2.SetRotation({ 0,0,-90 });
	AddComponent<Image>(uiCornerImage2);

	Image uiCornerImage3(this);
	uiCornerImage3.Load("Assets/Image/UIEdge_Corner.png");
	uiCornerImage3.SetPosition({ uiPos_.x - windowSize.x * 0.9505f,uiPos_.y - windowSize.y * 0.951f,0 });
	uiCornerImage3.SetSize({ 0.3f,0.3f,0 });
	uiCornerImage3.SetRotation({ 0,0,180 });
	AddComponent<Image>(uiCornerImage3);

	Image uiCornerImage4(this);
	uiCornerImage4.Load("Assets/Image/UIEdge_Corner.png");
	uiCornerImage4.SetPosition({ uiPos_.x - windowSize.x * 0.95f,uiPos_.y + windowSize.y * 0.95f,0 });
	uiCornerImage4.SetSize({ 0.3f,0.3f,0 });
	uiCornerImage4.SetRotation({ 0,0,90 });
	AddComponent<Image>(uiCornerImage4);
}

void P_MP_PotionManagerUI_PotionStockUI::CreatePotionMenu(int potionNum, const std::string& name, const XMFLOAT3& color)
{
	//GameObject* potionMenu = Instantiate<PotionMenu>(this);
	//potionMenu->GetComponent<Image>().SetPosition({ 0.5f,0,0 });
	//((PotionMenu*)potionMenu)->CreateMenu(potionNum, name, color);
}

void P_MP_PotionManagerUI_PotionStockUI::ConfirmPotionManagement()
{
	//ポーションリストのデータを更新
	std::vector<PlayerData::PotionData> newPotionDataList;
	for (int i = 0; i < potionList_.size(); i++)
	{
		if (((PotionStock*)potionList_[i])->GetPotionNumber() != -1 && ((PotionStock*)potionList_[i])->GetSelectedSlot() != PotionStock::SelectSlot::Dispose)
		{
			PlayerData::PotionData pData;
			pData.potionName_ = ((PotionStock*)potionList_[i])->GetPotionName();
			pData.potionColor_ = ((PotionStock*)potionList_[i])->GetPotionColor();
			pData.topStatus_ = ((PotionStock*)potionList_[i])->GetTopStatus();
			pData.price_ = ((PotionStock*)potionList_[i])->GetPrice();
			pData.potionStatus_ = ((PotionStock*)potionList_[i])->GetPotionStatus();
			if (((PotionStock*)potionList_[i])->GetSelectedSlot() == PotionStock::SelectSlot::Sell)
				pData.isSale_ = true;
			newPotionDataList.push_back(pData);
		}
	}
	
	//セーブデータを更新
	PlayerData* data = InterSceneData::GetData<PlayerData>("Data01");
	data->potionDataList_ = newPotionDataList;
	pParent_->KillMe();
}

void P_MP_PotionManagerUI_PotionStockUI::SetEnablePotionStock(bool isEnable)
{
	//ポーションを選べるかどうかを設定
	for (auto potion : potionList_)
	{
			((PotionStock*)potion)->isSelect_ = isEnable;
	}
}

void P_MP_PotionManagerUI_PotionStockUI::Release()
{
	potionList_.clear();
}
