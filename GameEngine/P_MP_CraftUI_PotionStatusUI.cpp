#include "P_MP_CraftUI_PotionStatusUI.h"
#include"Engine/Systems/ImageSystem.h"
#include"Engine/Systems/TextSystem.h"
P_MP_CraftUI_PotionStatusUI::P_MP_CraftUI_PotionStatusUI(Object* parent)
	:GameObject(parent,"P_MP_CraftUI_PotionStatusUI")
{
}

P_MP_CraftUI_PotionStatusUI::~P_MP_CraftUI_PotionStatusUI()
{
}

void P_MP_CraftUI_PotionStatusUI::Initialize()
{
	Image uiBaseImage(this);
	uiBaseImage.Load("Assets/Image/PotionManagerUIBase1.png");
	uiBaseImage.SetPosition({ -0.6,-0.67f,0 });
	uiBaseImage.SetSize({ 0.7f,0.3f,0 });
	AddComponent<Image>(uiBaseImage);
}

void P_MP_CraftUI_PotionStatusUI::Start()
{
}

void P_MP_CraftUI_PotionStatusUI::Update()
{
}

void P_MP_CraftUI_PotionStatusUI::Release()
{
}
