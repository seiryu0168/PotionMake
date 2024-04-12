#include "P_MP_PotionManagerUI_DisposeStockUI.h"
#include"Engine/Systems/ImageSystem.h"
#include"Engine/Systems/TextSystem.h"
#include"PotionSlot.h"
P_MP_PotionManagerUI_DisposeStockUI::P_MP_PotionManagerUI_DisposeStockUI(Object* parent)
	:GameObject(parent,"P_MP_PotionManagerUI_DisposeStockUI"),
	standPosition_({-0.88f,-0.3f}),
	uiPos_({ -0.58,-0.3,0 })
{
}

P_MP_PotionManagerUI_DisposeStockUI::~P_MP_PotionManagerUI_DisposeStockUI()
{
}

void P_MP_PotionManagerUI_DisposeStockUI::Initialize()
{
	//Image stockBaseImage(this);
	//stockBaseImage.Load("Assets/Image/PotionManagerUIBase1.png");
	//stockBaseImage.SetPosition(uiPos_);
	//stockBaseImage.SetSize({ 0.7f,0.3f,0 });
	//AddComponent<Image>(stockBaseImage);
	CreateBase();

	Text uiTitleText(this);
	uiTitleText.SetText("éÃÇƒÇÈÉ|Å[ÉVÉáÉì");
	uiTitleText.SetTextSize(55.0f);
	uiTitleText.SetPosition({ 30,520 });
	AddComponent<Text>(uiTitleText);

	XMFLOAT2 diff = { 0,0 };
	for (int i = 0; i < 5; i++)
	{
		PotionSlot* potion = Instantiate<PotionSlot>(this);
		potion->GetComponent<Image>().SetPosition({ standPosition_.x + diff.x,standPosition_.y + diff.y,0 });
		diff.x += 0.15;
		objects_.push_back(potion);
	}
}

void P_MP_PotionManagerUI_DisposeStockUI::Start()
{
}

void P_MP_PotionManagerUI_DisposeStockUI::Update()
{
}

void P_MP_PotionManagerUI_DisposeStockUI::CreateBase()
{
	XMFLOAT3 windowSize;
	XMFLOAT3 imageRatio;
	Image uiBaseImage(this);
	uiBaseImage.Load("Assets/Image/UIBaseImage2.png");
	uiBaseImage.SetPosition({ uiPos_.x,uiPos_.y,0 });
	uiBaseImage.SetSize({ 16 * 0.75f,16 * 0.2f,0 });
	windowSize = uiBaseImage.GetSizeAtPixel();
	imageRatio = uiBaseImage.GetSize();
	AddComponent<Image>(uiBaseImage);

	windowSize = { windowSize.x / (Direct3D::GetScreenWidth()),
				   windowSize.y / (Direct3D::GetScreenHeight()),0 };

	Image uiWidthEdgeImage1(this);
	uiWidthEdgeImage1.Load("Assets/Image/UIEdge_Width.png");
	uiWidthEdgeImage1.SetPosition({ uiPos_.x,uiPos_.y + windowSize.y * 0.89f,0 });
	uiWidthEdgeImage1.SetSize({ imageRatio.x * 0.97f,0.3f,0 });
	AddComponent<Image>(uiWidthEdgeImage1);
	Image uiWidthEdgeImage2(this);
	uiWidthEdgeImage2.Load("Assets/Image/UIEdge_Width.png");
	uiWidthEdgeImage2.SetPosition({ uiPos_.x,uiPos_.y - windowSize.y * 0.89f,0 });
	uiWidthEdgeImage2.SetSize({ imageRatio.x * 0.97f,0.3f,0 });
	AddComponent<Image>(uiWidthEdgeImage2);

	Image uiHeightEdgeImage1(this);
	uiHeightEdgeImage1.Load("Assets/Image/UIEdge_Height.png");
	uiHeightEdgeImage1.SetPosition({ uiPos_.x + windowSize.x * 0.97f,uiPos_.y,0 });
	uiHeightEdgeImage1.SetSize({ 0.3f,imageRatio.y * 0.9f,0 });
	AddComponent<Image>(uiHeightEdgeImage1);
	Image uiHeightEdgeImage2(this);
	uiHeightEdgeImage2.Load("Assets/Image/UIEdge_Height.png");
	uiHeightEdgeImage2.SetPosition({ uiPos_.x - windowSize.x * 0.97f,uiPos_.y,0 });
	uiHeightEdgeImage2.SetSize({ 0.3f,imageRatio.y * 0.9f,0 });
	AddComponent<Image>(uiHeightEdgeImage2);

	Image uiCornerImage1(this);
	uiCornerImage1.Load("Assets/Image/UIEdge_Corner.png");
	uiCornerImage1.SetPosition({ uiPos_.x + windowSize.x * 0.97f,uiPos_.y + windowSize.y * 0.89f,0 });
	uiCornerImage1.SetSize({ 0.3f,0.3f,0 });
	AddComponent<Image>(uiCornerImage1);

	Image uiCornerImage2(this);
	uiCornerImage2.Load("Assets/Image/UIEdge_Corner.png");
	uiCornerImage2.SetPosition({ uiPos_.x + windowSize.x * 0.97f,uiPos_.y - windowSize.y * 0.89f,0 });
	uiCornerImage2.SetSize({ 0.3f,0.3f,0 });
	uiCornerImage2.SetRotation({ 0,0,-90 });
	AddComponent<Image>(uiCornerImage2);

	Image uiCornerImage3(this);
	uiCornerImage3.Load("Assets/Image/UIEdge_Corner.png");
	uiCornerImage3.SetPosition({ uiPos_.x - windowSize.x * 0.97f,uiPos_.y - windowSize.y * 0.901f,0 });
	uiCornerImage3.SetSize({ 0.3f,0.3f,0 });
	uiCornerImage3.SetRotation({ 0,0,180 });
	AddComponent<Image>(uiCornerImage3);

	Image uiCornerImage4(this);
	uiCornerImage4.Load("Assets/Image/UIEdge_Corner.png");
	uiCornerImage4.SetPosition({ uiPos_.x - windowSize.x * 0.97f,uiPos_.y + windowSize.y * 0.9f,0 });
	uiCornerImage4.SetSize({ 0.3f,0.3f,0 });
	uiCornerImage4.SetRotation({ 0,0,90 });
	AddComponent<Image>(uiCornerImage4);
}

void P_MP_PotionManagerUI_DisposeStockUI::AddDisposePotion(int potionNum, const std::string& name, const XMFLOAT3& potionColor)
{
	for (GameObject* potion : objects_)
	{
		if (((PotionSlot*)potion)->GetPotionNumber() == -1)
		{
			((PotionSlot*)potion)->SetPotion(potionNum,name, potionColor);
			return;	
		}
	}
}

void P_MP_PotionManagerUI_DisposeStockUI::SubDisposePotion(int potionNum)
{
	for (GameObject* potion : objects_)
	{
		if (((PotionSlot*)potion)->GetPotionNumber() == potionNum)
		{
			((PotionSlot*)potion)->RemovePotion();
			return;
		}
	}
}

void P_MP_PotionManagerUI_DisposeStockUI::Release()
{
}
