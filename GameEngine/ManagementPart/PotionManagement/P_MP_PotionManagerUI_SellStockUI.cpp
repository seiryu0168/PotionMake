#include "P_MP_PotionManagerUI_SellStockUI.h"
#include "PotionSlot.h"
#include "../../Engine/Systems/ImageSystem.h"
#include "../../Engine/Systems/TextSystem.h"
P_MP_PotionManagerUI_SellStockUI::P_MP_PotionManagerUI_SellStockUI(Object* parent)
	:Window_Base(parent,"P_MP_PotionManagerUI_SellStockUI"),
	standPosition_({-0.88f,0.27f}),
	uiPos_({ -0.58,0.27,0 })
{
}

P_MP_PotionManagerUI_SellStockUI::~P_MP_PotionManagerUI_SellStockUI()
{
}

void P_MP_PotionManagerUI_SellStockUI::Initialize()
{
	CreateBase("Assets/Image/UIBaseImage2.png", uiPos_, {0.75f,0.2f},0.3f);
	CreateUITitle({ uiPos_.x - 0.1f,uiPos_.y + 0.31f }, { 10,20 }, "売るポーション", 55, {60,60,60});
	//Text uiTitleText(this);
	//uiTitleText.SetText("売るポーション");
	//uiTitleText.SetTextSize(55.0f);
	//uiTitleText.SetPosition({ 30,210 });	
	//AddComponent<Text>(uiTitleText);

	XMFLOAT2 diff = { 0,0 };
	//ポーションの位置設定
	for (int i = 0; i < 5; i++)
	{
		GameObject* potion = Instantiate<PotionSlot>(this);
		potion->GetComponent<Image>().SetPosition({ standPosition_.x + diff.x,standPosition_.y + diff.y,0 });
		diff.x += 0.15;
		objects_.push_back(potion);
	}
}

void P_MP_PotionManagerUI_SellStockUI::Start()
{
}

void P_MP_PotionManagerUI_SellStockUI::Update()
{
}

//void P_MP_PotionManagerUI_SellStockUI::CreateBase()
//{
//	XMFLOAT3 windowSize;
//	XMFLOAT3 imageRatio;
//	Image uiBaseImage(this);
//	uiBaseImage.Load("Assets/Image/UIBaseImage2.png");
//	uiBaseImage.SetPosition({ uiPos_.x,uiPos_.y,0 });
//	uiBaseImage.SetSize({ 16 * 0.75f,16 * 0.2f,0 });
//	windowSize = uiBaseImage.GetSizeAtPixel();
//	imageRatio = uiBaseImage.GetSize();
//	AddComponent<Image>(uiBaseImage);
//
//	windowSize = { windowSize.x / (Direct3D::GetScreenWidth()),
//				   windowSize.y / (Direct3D::GetScreenHeight()),0 };
//
//	Image uiWidthEdgeImage1(this);
//	uiWidthEdgeImage1.Load("Assets/Image/UIEdge_Width.png");
//	uiWidthEdgeImage1.SetPosition({ uiPos_.x,uiPos_.y + windowSize.y * 0.89f,0 });
//	uiWidthEdgeImage1.SetSize({ imageRatio.x * 0.97f,0.3f,0 });
//	AddComponent<Image>(uiWidthEdgeImage1);
//	Image uiWidthEdgeImage2(this);
//	uiWidthEdgeImage2.Load("Assets/Image/UIEdge_Width.png");
//	uiWidthEdgeImage2.SetPosition({ uiPos_.x,uiPos_.y - windowSize.y * 0.89f,0 });
//	uiWidthEdgeImage2.SetSize({ imageRatio.x * 0.97f,0.3f,0 });
//	AddComponent<Image>(uiWidthEdgeImage2);
//
//	Image uiHeightEdgeImage1(this);
//	uiHeightEdgeImage1.Load("Assets/Image/UIEdge_Height.png");
//	uiHeightEdgeImage1.SetPosition({ uiPos_.x + windowSize.x * 0.97f,uiPos_.y,0 });
//	uiHeightEdgeImage1.SetSize({ 0.3f,imageRatio.y * 0.9f,0 });
//	AddComponent<Image>(uiHeightEdgeImage1);
//	Image uiHeightEdgeImage2(this);
//	uiHeightEdgeImage2.Load("Assets/Image/UIEdge_Height.png");
//	uiHeightEdgeImage2.SetPosition({ uiPos_.x - windowSize.x * 0.97f,uiPos_.y,0 });
//	uiHeightEdgeImage2.SetSize({ 0.3f,imageRatio.y * 0.9f,0 });
//	AddComponent<Image>(uiHeightEdgeImage2);
//
//	Image uiCornerImage1(this);
//	uiCornerImage1.Load("Assets/Image/UIEdge_Corner.png");
//	uiCornerImage1.SetPosition({ uiPos_.x + windowSize.x * 0.97f,uiPos_.y + windowSize.y * 0.89f,0 });
//	uiCornerImage1.SetSize({ 0.3f,0.3f,0 });
//	AddComponent<Image>(uiCornerImage1);
//
//	Image uiCornerImage2(this);
//	uiCornerImage2.Load("Assets/Image/UIEdge_Corner.png");
//	uiCornerImage2.SetPosition({ uiPos_.x + windowSize.x * 0.97f,uiPos_.y - windowSize.y * 0.89f,0 });
//	uiCornerImage2.SetSize({ 0.3f,0.3f,0 });
//	uiCornerImage2.SetRotation({ 0,0,-90 });
//	AddComponent<Image>(uiCornerImage2);
//
//	Image uiCornerImage3(this);
//	uiCornerImage3.Load("Assets/Image/UIEdge_Corner.png");
//	uiCornerImage3.SetPosition({ uiPos_.x - windowSize.x * 0.97f,uiPos_.y - windowSize.y * 0.901f,0 });
//	uiCornerImage3.SetSize({ 0.3f,0.3f,0 });
//	uiCornerImage3.SetRotation({ 0,0,180 });
//	AddComponent<Image>(uiCornerImage3);
//
//	Image uiCornerImage4(this);
//	uiCornerImage4.Load("Assets/Image/UIEdge_Corner.png");
//	uiCornerImage4.SetPosition({ uiPos_.x - windowSize.x * 0.97f,uiPos_.y + windowSize.y * 0.9f,0 });
//	uiCornerImage4.SetSize({ 0.3f,0.3f,0 });
//	uiCornerImage4.SetRotation({ 0,0,90 });
//	AddComponent<Image>(uiCornerImage4);
//}
//
//void P_MP_PotionManagerUI_SellStockUI::CreateUITitle(XMFLOAT2 pos, XMFLOAT2 diff, const std::string& str)
//{
//	XMINT2 windowSize = Direct3D::GetWindwSize();
//	Text craftUIText(this);
//	craftUIText.SetText(str);
//	craftUIText.SetTextSize(55.0f);
//	float rectSize = craftUIText.GetTextSize() * str.size() * 0.5f;
//	TEXT_RECT rect = { 0,0,rectSize + diff.x,(float)craftUIText.GetTextSize() + diff.y };
//	XMFLOAT2 txtPos = { 0,0 };
//	txtPos.x = (pos.x * windowSize.x * 0.5f) + (windowSize.x * 0.5f);//= { 0.5f + (pos.x * 0.5f), 0.5f - (pos.y * 0.5f) };
//	txtPos.y = (-pos.y * windowSize.y * 0.5f) + (windowSize.y * 0.5f);
//	
//	txtPos.x -= (rect.right*0.5f);
//	craftUIText.SetRect(rect);
//	craftUIText.SetAlignmentType(ALIGNMENT_TYPE::CENTER_CENTER);
//	craftUIText.SetPosition({ txtPos.x, txtPos.y });
//	AddComponent<Text>(craftUIText);
//
//	XMFLOAT2 imagePos = { pos.x ,pos.y - rect.bottom / windowSize.y };
//	Image base(this);
//	base.Load("Assets/Image/UIBaseImage2.png");
//	base.SetSize({ 0.015625f * rect.right,0.015625f * rect.bottom,0 });
//	base.SetPosition({ imagePos.x,imagePos.y,0 });
//	XMFLOAT3 size = base.GetSizeAtPixel();
//	//XMFLOAT2 distance = { size.x / Direct3D::GetScreenWidth(),size.y / Direct3D::GetScreenHeight() };
//
//	float distance = rect.right / windowSize.x;
//	Image start(this);
//	start.Load("Assets/Image/UILong03_Start.png");
//	start.SetSize({ size.y / 256,size.y / 256,0.0f });
//	//start.SetRotation({ 0,0,180 });
//	start.SetPosition({ imagePos.x - distance - 0.03f,imagePos.y,0 });
//	AddComponent<Image>(start);
//
//	Image end(this);
//	end.Load("Assets/Image/UILong03_End.png");
//	end.SetSize({ size.y / 256,size.y / 256,0.0f });
//	end.SetPosition({ imagePos.x + distance + 0.03f,imagePos.y,0 });
//	AddComponent<Image>(end);
//
//	AddComponent<Image>(base);
//}

void P_MP_PotionManagerUI_SellStockUI::AddSellPotion(int potionNum, const std::string& name, const XMFLOAT3& potionColor)
{
	//販売するポーション枠に追加する
	for (GameObject* potion : objects_)
	{
		if (((PotionSlot*)potion)->GetPotionNumber() == -1)
		{
			((PotionSlot*)potion)->SetPotion(potionNum, name, potionColor);
			return;
		}
	}
}

void P_MP_PotionManagerUI_SellStockUI::SubSellPotion(int potionNum)
{
	//販売するポーション枠から消す
	for (GameObject* potion : objects_)
	{
		if (((PotionSlot*)potion)->GetPotionNumber() == potionNum)
		{
			((PotionSlot*)potion)->RemovePotion();
			return;
		}
	}
}

void P_MP_PotionManagerUI_SellStockUI::Release()
{
}
