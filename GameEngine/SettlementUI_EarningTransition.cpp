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
	Image back(this);
	back.Load("Assets/Image/UIBaseImage2.png");
	back.SetSize({ 15,7,0 });
	back.SetPosition(uiPos_);
	AddComponent<Image>(back);

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

void SettlementUI_EarningTransition::SetData(const std::vector<int>& gainList)
{
	gainList_ = gainList;

	for (int i = 0; i < 5; i++)
	{
		GetComponent<Image>(firstGaugeNum_ + i).SetSize({ 0.5f,gainList[i]*0.001f,0 });
	}

}

void SettlementUI_EarningTransition::Release()
{
}
