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

	XMFLOAT3 txtPos = back.GetPositionAtPixel();
	Text sectionText(this);
	sectionText.SetText("îÑè„");
	sectionText.SetRect({ 0,0,220,70 });
	sectionText.SetPosition({ txtPos.x - 150,txtPos.y - 150 });
	AddComponent<Text>(sectionText);

	Text totalGain(this);
	totalGain.SetAlignmentType(ALIGNMENT_TYPE::RIGHT_TOP);
	totalGain.SetText("100000");
	totalGain.SetRect({ 0,0,630,80 });
	totalGain.SetPosition({ txtPos.x - 450,txtPos.y-100 });
	AddComponent<Text>(totalGain);

	Text evaluation(this);
	evaluation.SetText("ëÂê∑ãµ");
	evaluation.SetPosition({ txtPos.x - 150,txtPos.y});
	AddComponent<Text>(evaluation);
}

void P_MP_SettlementUI_TotalGain::Start()
{
}

void P_MP_SettlementUI_TotalGain::Update()
{
}

void P_MP_SettlementUI_TotalGain::SetData(int totalGain, const std::string& evaluation)
{
	GetComponent<Text>(1).SetText(std::to_string(totalGain));
	GetComponent<Text>(2).SetText(evaluation);
}

void P_MP_SettlementUI_TotalGain::Release()
{
}
