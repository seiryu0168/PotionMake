#include "P_MP_PotionManagerUI_PotionStockUI.h"
#include"Engine/Systems/ImageSystem.h"
#include"Engine/Systems/TextSystem.h"
P_MP_PotionManagerUI_PotionStockUI::P_MP_PotionManagerUI_PotionStockUI(Object* parent)
	:GameObject(parent,"P_MP_PotionManagerUI_PotionStockUI")
{
}

P_MP_PotionManagerUI_PotionStockUI::~P_MP_PotionManagerUI_PotionStockUI()
{
}

void P_MP_PotionManagerUI_PotionStockUI::Initialize()
{
	Image uiBaseImage(this);
	uiBaseImage.Load("Assets/Image/PotionManagerUIBase1.png");
	uiBaseImage.SetPosition({ 0.45f,-0.1f,0 });
	uiBaseImage.SetSize({ 1,0.8f,0 });
	AddComponent<Image>(uiBaseImage);
}

void P_MP_PotionManagerUI_PotionStockUI::Start()
{
}

void P_MP_PotionManagerUI_PotionStockUI::Update()
{
}

void P_MP_PotionManagerUI_PotionStockUI::Release()
{
}
