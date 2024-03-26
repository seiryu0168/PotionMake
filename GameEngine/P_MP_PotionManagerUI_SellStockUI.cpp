#include "P_MP_PotionManagerUI_SellStockUI.h"
#include"Engine/Systems/ImageSystem.h"
#include"Engine/Systems/TextSystem.h"
P_MP_PotionManagerUI_SellStockUI::P_MP_PotionManagerUI_SellStockUI(Object* parent)
	:GameObject(parent,"P_MP_PotionManagerUI_SellStockUI")
{
}

P_MP_PotionManagerUI_SellStockUI::~P_MP_PotionManagerUI_SellStockUI()
{
}

void P_MP_PotionManagerUI_SellStockUI::Initialize()
{
	Image stockBaseImage(this);
	stockBaseImage.Load("Assets/Image/PotionManagerUIBase1.png");
	stockBaseImage.SetPosition({ -0.6,0.17,0 });
	stockBaseImage.SetSize({ 0.7f,0.3f,0 });
	AddComponent<Image>(stockBaseImage);

	Text uiTitleText(this);
	uiTitleText.SetText("îÑÇÈÉ|Å[ÉVÉáÉì");
	uiTitleText.SetTextSize(55.0f);
	uiTitleText.SetPosition({ 30,210 });	
	AddComponent<Text>(uiTitleText);
}

void P_MP_PotionManagerUI_SellStockUI::Start()
{
}

void P_MP_PotionManagerUI_SellStockUI::Update()
{
}

void P_MP_PotionManagerUI_SellStockUI::Release()
{
}
