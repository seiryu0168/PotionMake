#include "Play_ManagementPart_PotionManagerUI.h"
#include"../../Engine/Systems/TextSystem.h"
#include"../../Engine/Systems/ImageSystem.h"
#include"../../CloseButton.h"
#include"P_MP_PotionManagerUI_PotionStockUI.h"
#include"P_MP_PotionManagerUI_SellStockUI.h"
#include"P_MP_PotionManagerUI_DisposeStockUI.h"
#include"../../Play_ManagementPart_BaseUI.h"

Play_ManagementPart_PotionManagerUI::Play_ManagementPart_PotionManagerUI(Object* parent)
	:GameObject(parent,"Play_ManagementPart_PotionManagerUI")
{
}

Play_ManagementPart_PotionManagerUI::~Play_ManagementPart_PotionManagerUI()
{
}

void Play_ManagementPart_PotionManagerUI::Initialize()
{
	Text uiTitleText(this);
	uiTitleText.SetText("É|Å[ÉVÉáÉìä«óù");
	uiTitleText.SetPosition({ 600,30 });
	AddComponent<Text>(uiTitleText);

	Instantiate<P_MP_PotionManagerUI_SellStockUI>(this);
	Instantiate<P_MP_PotionManagerUI_DisposeStockUI>(this);
	Instantiate<P_MP_PotionManagerUI_PotionStockUI>(this);
	Instantiate<CloseButton>(this);
}

void Play_ManagementPart_PotionManagerUI::Update()
{
}

void Play_ManagementPart_PotionManagerUI::Release()
{
	((Play_ManagementPart_BaseUI*)pParent_)->SetAccessUIFlag(false);
}
