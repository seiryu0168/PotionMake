#include "Play_ManagementPart_PotionManagerUI.h"
#include "P_MP_PotionManagerUI_PotionStockUI.h"
#include "P_MP_PotionManagerUI_SellStockUI.h"
#include "P_MP_PotionManagerUI_DisposeStockUI.h"
#include "../Play_ManagementPart_BaseUI.h"
#include "../../Engine/Systems/TextSystem.h"
#include "../../Engine/Systems/ImageSystem.h"
#include "../../CloseButton.h"

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
	uiTitleText.SetText("ポーション管理");
	uiTitleText.SetPosition({ 600,30 });
	AddComponent<Text>(uiTitleText);

	//販売/破棄するポーションのUI
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
	Direct3D::ShowMouseCursor(false);
	XMINT2 rectPos = { (int)(Direct3D::GetScreenWidth() * 0.5f),(int)(Direct3D::GetScreenHeight() * 0.5f) };
	Direct3D::SetClipCursor({ rectPos.x,rectPos.y,rectPos.x + 1,rectPos.y + 1 });
	((Play_ManagementPart_BaseUI*)pParent_)->SetAccessUIFlag(false);
}
