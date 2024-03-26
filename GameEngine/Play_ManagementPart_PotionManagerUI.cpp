#include "Play_ManagementPart_PotionManagerUI.h"
#include"Engine/Systems/TextSystem.h"
#include"Engine/Systems/ImageSystem.h"
#include"CloseButton.h"
#include"P_MP_PotionManagerUI_PotionStockUI.h"
#include"P_MP_PotionManagerUI_SellStockUI.h"
Play_ManagementPart_PotionManagerUI::Play_ManagementPart_PotionManagerUI(Object* parent)
	:GameObject(parent,"Play_ManagementPart_PotionManagerUI")
{
}

Play_ManagementPart_PotionManagerUI::~Play_ManagementPart_PotionManagerUI()
{
}

void Play_ManagementPart_PotionManagerUI::Initialize()
{
	//Image baseUI(this);
	//baseUI.Load("Assets/Image/PotionManagerUIBase1.png");
	//AddComponent<Image>(baseUI);

	Text uiTitleText(this);
	uiTitleText.SetText("É|Å[ÉVÉáÉìä«óù");
	uiTitleText.SetPosition({ 1000.0f,500.0f });
	AddComponent<Text>(uiTitleText);

	Instantiate<P_MP_PotionManagerUI_PotionStockUI>(this);
	Instantiate<P_MP_PotionManagerUI_SellStockUI>(this);
	Instantiate<CloseButton>(this);
}

void Play_ManagementPart_PotionManagerUI::Update()
{
}

void Play_ManagementPart_PotionManagerUI::Release()
{
}
