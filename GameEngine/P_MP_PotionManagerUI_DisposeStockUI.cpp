#include "P_MP_PotionManagerUI_DisposeStockUI.h"
#include"Engine/Systems/ImageSystem.h"
#include"Engine/Systems/TextSystem.h"
P_MP_PotionManagerUI_DisposeStockUI::P_MP_PotionManagerUI_DisposeStockUI(Object* parent)
	:GameObject(parent,"P_MP_PotionManagerUI_DisposeStockUI")
{
}

P_MP_PotionManagerUI_DisposeStockUI::~P_MP_PotionManagerUI_DisposeStockUI()
{
}

void P_MP_PotionManagerUI_DisposeStockUI::Initialize()
{
	Image stockBaseImage(this);
	stockBaseImage.Load("Assets/Image/PotionManagerUIBase1.png");
	stockBaseImage.SetPosition({ -0.6,-0.58,0 });
	stockBaseImage.SetSize({ 0.7f,0.3f,0 });
	AddComponent<Image>(stockBaseImage);
	Text uiTitleText(this);
	uiTitleText.SetText("éÃÇƒÇÈÉ|Å[ÉVÉáÉì");
	uiTitleText.SetTextSize(55.0f);
	uiTitleText.SetPosition({ 30,620 });
	AddComponent<Text>(uiTitleText);
}

void P_MP_PotionManagerUI_DisposeStockUI::Start()
{
}

void P_MP_PotionManagerUI_DisposeStockUI::Update()
{
}

void P_MP_PotionManagerUI_DisposeStockUI::Release()
{
}
