#include "SettlementUI_EarningTransition.h"
#include "../../Engine/Systems/ImageSystem.h"
#include "../../Engine/Systems/TextSystem.h"

SettlementUI_EarningTransition::SettlementUI_EarningTransition(Object* parent)
	:GameObject(parent,"SettlementUI_EarningTransition"),
	uiPos_({ 0.2f,-0.4f,0 }),
	firstGaugeNum_(-1),
	gaugeSize_(2.0f)
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
	CreateUITitle({ uiPos_.x - 0.18f,uiPos_.y + 0.526f }, { 10,20 }, "îÑè„ÇÃêÑà⁄");
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
	uiBaseImage.SetSize({ 12,7,0 });
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
	//îÑÇËè„Ç∞ÇÃç≈ëÂílÇãÅÇﬂÇÈ
	int maxGain = 0;
	for (int gain : gainList)
	{
		if (gain > maxGain)
			maxGain = gain;
	}
	//îÑè„êÑà⁄ÇÃê›íË
	gainList_ = gainList;
	for (int i = 0; i < gainList_.size(); i++)
	{
		GetComponent<Image>(firstGaugeNum_ + i).SetSize({ 0.5f,Clamp(gaugeSize_*((float)gainList_[i]/maxGain),0.05f,gaugeSize_),0});
	}

}

void SettlementUI_EarningTransition::CreateUITitle(XMFLOAT2 pos, XMFLOAT2 diff, const std::string& str)
{
	XMINT3 color = { 102,100,82 };
	Text craftUIText(this);
	craftUIText.SetText(str);
	craftUIText.SetTextSize(55.0f);
	float rectSize = craftUIText.GetTextSize() * str.size() * 0.5f;
	TEXT_RECT rect = { 0,0,rectSize + diff.x,(float)craftUIText.GetTextSize() + diff.y };
	XMFLOAT2 ratio = { 0.5f + (pos.x * 0.5f), 0.5f - (pos.y * 0.5f) };
	ratio.x -= (rect.right / Direct3D::GetScreenWidth()) * 0.5f;
	craftUIText.SetRect(rect);
	craftUIText.SetAlignmentType(ALIGNMENT_TYPE::CENTER_CENTER);
	craftUIText.SetRatio(ratio.x, ratio.y);
	AddComponent<Text>(craftUIText);

	XMFLOAT2 imagePos = { pos.x ,pos.y - rect.bottom / Direct3D::GetScreenHeight() };
	Image base(this);
	base.Load("Assets/Image/UIBaseImage3.png");
	base.SetSize({ 0.015625f * rect.right,0.015625f * rect.bottom,0 });
	base.SetPosition({ imagePos.x,imagePos.y,0 });
	base.SetColorInt(color);
	XMFLOAT3 size = base.GetSizeAtPixel();
	//XMFLOAT2 distance = { size.x / Direct3D::GetScreenWidth(),size.y / Direct3D::GetScreenHeight() };

	float distance = rect.right / Direct3D::GetScreenWidth();
	Image start(this);
	start.Load("Assets/Image/UILong04_Start.png");
	start.SetSize({ size.y / 256,size.y / 256,0.0f });
	start.SetColorInt(color);
	//start.SetRotation({ 0,0,180 });
	start.SetPosition({ imagePos.x - distance - 0.03f,imagePos.y,0 });
	AddComponent<Image>(start);

	Image end(this);
	end.Load("Assets/Image/UILong04_End.png");
	end.SetSize({ size.y / 256,size.y / 256,0.0f });
	end.SetColorInt(color);
	end.SetPosition({ imagePos.x + distance + 0.03f,imagePos.y,0 });
	AddComponent<Image>(end);

	AddComponent<Image>(base);
}

void SettlementUI_EarningTransition::Release()
{
}
