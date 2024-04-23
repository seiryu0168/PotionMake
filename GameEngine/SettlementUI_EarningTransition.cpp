#include "SettlementUI_EarningTransition.h"
#include"Engine/Systems/ImageSystem.h"
#include"Engine/Systems/TextSystem.h"

SettlementUI_EarningTransition::SettlementUI_EarningTransition(Object* parent)
	:GameObject(parent,"SettlementUI_EarningTransition")
{
}

SettlementUI_EarningTransition::~SettlementUI_EarningTransition()
{
}

void SettlementUI_EarningTransition::Initialize()
{
	Image back(this);
	back.Load("Assets/Image/UIBaseImage2.png");
	back.SetSize({ 10,7,0 });
	back.SetPosition({ 0.5f,-0.4f,0 });
	AddComponent<Image>(back);
}

void SettlementUI_EarningTransition::Start()
{
}

void SettlementUI_EarningTransition::Update()
{
}

void SettlementUI_EarningTransition::Release()
{
}
