#include "P_MP_CraftUI_PrepareUI.h"
#include"Engine/Systems/ImageSystem.h"
#include"Engine/Systems/TextSystem.h"
#include"P_MP_CraftUI_CraftPot.h"
P_MP_CraftUI_PrepareUI::P_MP_CraftUI_PrepareUI(Object* parent)
	:GameObject(parent,"P_MP_CraftUI_PrepareUI")
{
}

P_MP_CraftUI_PrepareUI::~P_MP_CraftUI_PrepareUI()
{
}

void P_MP_CraftUI_PrepareUI::Initialize()
{
	Image uiBaseImage(this);
	uiBaseImage.Load("Assets/Image/PotionManagerUIBase1.png");
	uiBaseImage.SetPosition({ -0.6,0.25f,0 });
	uiBaseImage.SetSize({ 0.7f,0.5f,0 });
	AddComponent<Image>(uiBaseImage);
	Instantiate<P_MP_CraftUI_CraftPot>(this);
}

void P_MP_CraftUI_PrepareUI::Start()
{
}

void P_MP_CraftUI_PrepareUI::Update()
{
}

void P_MP_CraftUI_PrepareUI::Release()
{
}
