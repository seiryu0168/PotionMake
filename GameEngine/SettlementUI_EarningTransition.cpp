#include "SettlementUI_EarningTransition.h"
#include"Engine/Systems/ImageSystem.h"
#include"Engine/Systems/TextSystem.h"

SettlementUI_EarningTransition::SettlementUI_EarningTransition(Object* parent)
	:GameObject(parent,"SettlementUI_EarningTransition"),
	uiPos_({ 0.4f,-0.4f,0 }),
	firstGaugeNum_(-1)
{
}

SettlementUI_EarningTransition::~SettlementUI_EarningTransition()
{
}

void SettlementUI_EarningTransition::Initialize()
{
	//Image back(this);
	//back.Load("Assets/Image/UIBaseImage2.png");
	//back.SetSize({ 15,7,0 });
	//back.SetPosition(uiPos_);
	//AddComponent<Image>(back);

	CreateBase();
	
	//âﬂãé5âÒï™ÇÃîÑè„Çï\é¶Ç∑ÇÈà◊ÇÃâÊëú
	XMFLOAT2 diffPos = { -0.3f, -0.2f};
	for (int i = 0; i < 5; i++)
	{
		Image statusImage(this);
		statusImage.Load("Assets/Image/GaugeImage01.png");
		statusImage.SetSize({ 0.5f,0,0 });
		statusImage.SetPosition({ uiPos_.x + diffPos.x,uiPos_.y + diffPos.y,0 });
		if (firstGaugeNum_ < 0)
			firstGaugeNum_ = AddComponent<Image>(statusImage);
		else
			AddComponent<Image>(statusImage);

		diffPos.x += 0.15f;
	}

}

void SettlementUI_EarningTransition::Start()
{
}

void SettlementUI_EarningTransition::Update()
{
}

void SettlementUI_EarningTransition::CreateBase()
{
	XMFLOAT3 windowSize;
	XMFLOAT3 imageRatio;
	Image uiBaseImage(this);
	uiBaseImage.Load("Assets/Image/UIBaseImage4.png");
	uiBaseImage.SetPosition({ uiPos_.x,uiPos_.y,0 });
	uiBaseImage.SetSize({ 15,7,0 });
	windowSize = uiBaseImage.GetSizeAtPixel();
	imageRatio = uiBaseImage.GetSize();
	AddComponent<Image>(uiBaseImage);

	windowSize = { windowSize.x / (Direct3D::GetScreenWidth()),
				   windowSize.y / (Direct3D::GetScreenHeight()),0 };
	Image uiWidthEdgeImage1(this);
	uiWidthEdgeImage1.Load("Assets/Image/UIEdge_Width.png");
	uiWidthEdgeImage1.SetPosition({ uiPos_.x,uiPos_.y + windowSize.y,0 });
	uiWidthEdgeImage1.SetSize({ imageRatio.x,0.3f,0 });
	AddComponent<Image>(uiWidthEdgeImage1);
	Image uiWidthEdgeImage2(this);
	uiWidthEdgeImage2.Load("Assets/Image/UIEdge_Width.png");
	uiWidthEdgeImage2.SetPosition({ uiPos_.x,uiPos_.y - windowSize.y,0 });
	uiWidthEdgeImage2.SetSize({ imageRatio.x,0.3f,0 });
	AddComponent<Image>(uiWidthEdgeImage2);

	Image uiHeightEdgeImage1(this);
	uiHeightEdgeImage1.Load("Assets/Image/UIEdge_Height.png");
	uiHeightEdgeImage1.SetPosition({ uiPos_.x + windowSize.x,uiPos_.y,0 });
	uiHeightEdgeImage1.SetSize({ 0.3f,imageRatio.y,0 });
	AddComponent<Image>(uiHeightEdgeImage1);
	Image uiHeightEdgeImage2(this);
	uiHeightEdgeImage2.Load("Assets/Image/UIEdge_Height.png");
	uiHeightEdgeImage2.SetPosition({ uiPos_.x - windowSize.x,uiPos_.y,0 });
	uiHeightEdgeImage2.SetSize({ 0.3f,imageRatio.y,0 });
	AddComponent<Image>(uiHeightEdgeImage2);

	Image uiCornerImage1(this);
	uiCornerImage1.Load("Assets/Image/UIEdge_Corner.png");
	uiCornerImage1.SetPosition({ uiPos_.x + windowSize.x,uiPos_.y + windowSize.y,0 });
	uiCornerImage1.SetSize({ 0.3f,0.3f,0 });
	AddComponent<Image>(uiCornerImage1);

	Image uiCornerImage2(this);
	uiCornerImage2.Load("Assets/Image/UIEdge_Corner.png");
	uiCornerImage2.SetPosition({ uiPos_.x + windowSize.x,uiPos_.y - windowSize.y,0 });
	uiCornerImage2.SetSize({ 0.3f,0.3f,0 });
	uiCornerImage2.SetRotation({ 0,0,-90 });
	AddComponent<Image>(uiCornerImage2);

	Image uiCornerImage3(this);
	uiCornerImage3.Load("Assets/Image/UIEdge_Corner.png");
	uiCornerImage3.SetPosition({ uiPos_.x - windowSize.x,uiPos_.y - windowSize.y,0 });
	uiCornerImage3.SetSize({ 0.3f,0.3f,0 });
	uiCornerImage3.SetRotation({ 0,0,180 });
	AddComponent<Image>(uiCornerImage3);

	Image uiCornerImage4(this);
	uiCornerImage4.Load("Assets/Image/UIEdge_Corner.png");
	uiCornerImage4.SetPosition({ uiPos_.x - windowSize.x,uiPos_.y + windowSize.y,0 });
	uiCornerImage4.SetSize({ 0.3f,0.3f,0 });
	uiCornerImage4.SetRotation({ 0,0,90 });
	AddComponent<Image>(uiCornerImage4);
}

void SettlementUI_EarningTransition::SetData(const std::vector<int>& gainList)
{
	//îÑè„êÑà⁄ÇÃê›íË
	gainList_ = gainList;
	for (int i = 0; i < 5; i++)
	{
		GetComponent<Image>(firstGaugeNum_ + i).SetSize({ 0.5f,gainList[i]*0.001f,0 });
	}

}

void SettlementUI_EarningTransition::Release()
{
}
