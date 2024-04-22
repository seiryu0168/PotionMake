#include "Play_ManagementPart_CraftUI.h"
#include"../../Engine/Systems/TextSystem.h"
#include"../../Engine/Systems/ImageSystem.h"
#include"../../CloseButton.h"
#include"../../Engine/DirectX_11/Input.h"
#include"P_MP_CraftUI_ResourceStockUI.h"
#include"P_MP_CraftUI_PotionStatusUI.h"
#include"P_MP_CraftUI_PrepareUI.h"
#include"../../Play_ManagementPart_BaseUI.h"
#include"PotionCraftAnimation.h"
#include"FinishCraftUI.h"
Play_ManagementPart_CraftUI::Play_ManagementPart_CraftUI(Object* parent)
	:GameObject(parent,"Play_ManagementPart_CraftUI")
{
}

Play_ManagementPart_CraftUI::~Play_ManagementPart_CraftUI()
{
}

void Play_ManagementPart_CraftUI::Initialize()
{
	Text craftUIText(this);
	craftUIText.SetText("É|Å[ÉVÉáÉìÇçÏÇÈ");
	craftUIText.SetPosition({ 600,30 });
	AddComponent<Text>(craftUIText);
	Instantiate<P_MP_CraftUI_ResourceStockUI>(this);
	Instantiate<P_MP_CraftUI_PotionStatusUI>(this);
	Instantiate<P_MP_CraftUI_PrepareUI>(this);
	Instantiate<CloseButton>(this);
}

void Play_ManagementPart_CraftUI::Update()
{
}

void Play_ManagementPart_CraftUI::DisplayCraftProcess(const std::vector<int>& itemNumList)
{
	KillAllChildren();
	PotionCraftAnimation* potion = Instantiate<PotionCraftAnimation>(this);
	potion->InitAnimation(itemNumList);
}

void Play_ManagementPart_CraftUI::DisplayResult()
{
	FinishCraftUI* result = Instantiate<FinishCraftUI>(this);
}

void Play_ManagementPart_CraftUI::BeforeDeath()
{
}

void Play_ManagementPart_CraftUI::Release()
{
	Direct3D::ShowMouseCursor(false);
	XMINT2 rectPos = { (int)(Direct3D::GetScreenWidth() * 0.5f),(int)(Direct3D::GetScreenHeight() * 0.5f) };
	Direct3D::SetClipCursor({rectPos.x,rectPos.y,rectPos.x+1,rectPos.y+1});
	((Play_ManagementPart_BaseUI*)pParent_)->SetAccessUIFlag(false);
}
