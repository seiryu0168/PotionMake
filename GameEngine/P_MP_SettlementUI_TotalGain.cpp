#include "P_MP_SettlementUI_TotalGain.h"
#include"Engine/Systems/ImageSystem.h"
#include"Engine/Systems/TextSystem.h"
P_MP_SettlementUI_TotalGain::P_MP_SettlementUI_TotalGain(Object* parent)
	:GameObject(parent,"P_MP_SettlementUI_TotalGain")
{
}

P_MP_SettlementUI_TotalGain::~P_MP_SettlementUI_TotalGain()
{
}

void P_MP_SettlementUI_TotalGain::Initialize()
{
	Image back(this);
	back.Load("Assets/Image/UIBaseImage2.png");
	back.SetSize({ 8,6,0 });
	back.SetPosition({ 0.5f,0.5f,0 });
	AddComponent<Image>(back);
}

void P_MP_SettlementUI_TotalGain::Start()
{
}

void P_MP_SettlementUI_TotalGain::Update()
{
}

void P_MP_SettlementUI_TotalGain::Release()
{
}
