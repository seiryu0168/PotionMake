#include "P_MP_CraftUI_PotionStatusUI.h"
#include"Engine/Systems/ImageSystem.h"
#include"Engine/Systems/TextSystem.h"
#include"PotionStatusGauge.h"
P_MP_CraftUI_PotionStatusUI::P_MP_CraftUI_PotionStatusUI(Object* parent)
	:GameObject(parent,"P_MP_CraftUI_PotionStatusUI"),
	uiPos_({ -0.6,-0.67f })
{
}

P_MP_CraftUI_PotionStatusUI::~P_MP_CraftUI_PotionStatusUI()
{
}

void P_MP_CraftUI_PotionStatusUI::Initialize()
{
	//Image uiBaseImage(this);
	//uiBaseImage.Load("Assets/Image/UIBaseImage2.png");
	//uiBaseImage.SetPosition({ uiPos_.x,uiPos_.y,0 });
	//uiBaseImage.SetSize({ 16*0.7f,16*0.3f,0 });
	//AddComponent<Image>(uiBaseImage);

	CreateBase();

	XMFLOAT2 diff = { -0.3f,-0.1f };
	XMFLOAT3 color = { 0.2f,0.3f,0.1f };
	//ポーションの各パラメータを表示
	for (int i = 0; i < 5; i++)
	{
		GameObject* gauge = Instantiate<PotionStatusGauge>(this);
		gauge->GetComponent<Image>().SetPosition({ uiPos_.x + diff.x,uiPos_.y + diff.y,0 });
		gauge->GetComponent<Image>().SetColor(color);
		color.x += 0.12f;
		color.y += 0.11f;
		color.z += 0.18f;
		diff.x += 0.1f;

		statusObjectList_.push_back(gauge);
	}


}

void P_MP_CraftUI_PotionStatusUI::Start()
{
}

void P_MP_CraftUI_PotionStatusUI::Update()
{
}

void P_MP_CraftUI_PotionStatusUI::CreateBase()
{
	XMFLOAT3 windowSize;
	XMFLOAT3 imageRatio;
	Image uiBaseImage(this);
	uiBaseImage.Load("Assets/Image/UIBaseImage2.png");
	uiBaseImage.SetPosition({ uiPos_.x,uiPos_.y,0 });
	uiBaseImage.SetSize({ 16 * 0.7f,16 * 0.3f,0 });
	windowSize = uiBaseImage.GetSizeAtPixel();
	imageRatio = uiBaseImage.GetSize();
	AddComponent<Image>(uiBaseImage);

	windowSize = { windowSize.x / (Direct3D::GetScreenWidth()),
				   windowSize.y / (Direct3D::GetScreenHeight()),0 };
	Image uiWidthEdgeImage1(this);
	uiWidthEdgeImage1.Load("Assets/Image/UIEdge_Width.png");
	uiWidthEdgeImage1.SetPosition({ uiPos_.x,uiPos_.y + windowSize.y * 0.9f,0 });
	uiWidthEdgeImage1.SetSize({ imageRatio.x * 0.95f,0.3f,0 });
	AddComponent<Image>(uiWidthEdgeImage1);
	Image uiWidthEdgeImage2(this);
	uiWidthEdgeImage2.Load("Assets/Image/UIEdge_Width.png");
	uiWidthEdgeImage2.SetPosition({ uiPos_.x,uiPos_.y - windowSize.y * 0.9f,0 });
	uiWidthEdgeImage2.SetSize({ imageRatio.x * 0.95f,0.3f,0 });
	AddComponent<Image>(uiWidthEdgeImage2);

	Image uiHeightEdgeImage1(this);
	uiHeightEdgeImage1.Load("Assets/Image/UIEdge_Height.png");
	uiHeightEdgeImage1.SetPosition({ uiPos_.x + windowSize.x * 0.95f,uiPos_.y,0 });
	uiHeightEdgeImage1.SetSize({ 0.3f,imageRatio.y * 0.9f,0 });
	AddComponent<Image>(uiHeightEdgeImage1);
	Image uiHeightEdgeImage2(this);
	uiHeightEdgeImage2.Load("Assets/Image/UIEdge_Height.png");
	uiHeightEdgeImage2.SetPosition({ uiPos_.x - windowSize.x * 0.95f,uiPos_.y,0 });
	uiHeightEdgeImage2.SetSize({ 0.3f,imageRatio.y * 0.9f,0 });
	AddComponent<Image>(uiHeightEdgeImage2);

	Image uiCornerImage1(this);
	uiCornerImage1.Load("Assets/Image/UIEdge_Corner.png");
	uiCornerImage1.SetPosition({ uiPos_.x + windowSize.x * 0.95f,uiPos_.y + windowSize.y * 0.901f,0 });
	uiCornerImage1.SetSize({ 0.3f,0.3f,0 });
	AddComponent<Image>(uiCornerImage1);

	Image uiCornerImage2(this);
	uiCornerImage2.Load("Assets/Image/UIEdge_Corner.png");
	uiCornerImage2.SetPosition({ uiPos_.x + windowSize.x * 0.9495f,uiPos_.y - windowSize.y * 0.901f,0 });
	uiCornerImage2.SetSize({ 0.3f,0.3f,0 });
	uiCornerImage2.SetRotation({ 0,0,-90 });
	AddComponent<Image>(uiCornerImage2);

	Image uiCornerImage3(this);
	uiCornerImage3.Load("Assets/Image/UIEdge_Corner.png");
	uiCornerImage3.SetPosition({ uiPos_.x - windowSize.x * 0.9505f,uiPos_.y - windowSize.y * 0.901f,0 });
	uiCornerImage3.SetSize({ 0.3f,0.3f,0 });
	uiCornerImage3.SetRotation({ 0,0,180 });
	AddComponent<Image>(uiCornerImage3);

	Image uiCornerImage4(this);
	uiCornerImage4.Load("Assets/Image/UIEdge_Corner.png");
	uiCornerImage4.SetPosition({ uiPos_.x - windowSize.x * 0.95f,uiPos_.y + windowSize.y * 0.9f,0 });
	uiCornerImage4.SetSize({ 0.3f,0.3f,0 });
	uiCornerImage4.SetRotation({ 0,0,90 });
	AddComponent<Image>(uiCornerImage4);
}

void P_MP_CraftUI_PotionStatusUI::ApplicationStatusData(std::vector<float> status)
{
	for (int i = 0; i < statusObjectList_.size(); i++)
	{
		statusObjectList_[i]->GetComponent<Image>().SetSize({ 1.0f*0.3f,status[i]*0.3f,0});
	}
}

void P_MP_CraftUI_PotionStatusUI::Release()
{
}
