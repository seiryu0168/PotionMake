#include "P_MP_CraftUI_ResourceStockUI.h"
#include"ResourceItem.h"
#include"Engine/Systems/ImageSystem.h"
#include"Engine/Systems/TextSystem.h"
P_MP_CraftUI_ResourceStockUI::P_MP_CraftUI_ResourceStockUI(Object* parent)
	:GameObject(parent,"P_MP_CraftUI_ResourceStockUI"),
	uiPos_({0,0,0})
{
}

P_MP_CraftUI_ResourceStockUI::~P_MP_CraftUI_ResourceStockUI()
{
}

void P_MP_CraftUI_ResourceStockUI::Initialize()
{
	uiPos_ = { 0.6,-0.13f,0 };
	Image uiBaseImage(this);
	uiBaseImage.Load("Assets/Image/PotionManagerUIBase1.png");
	uiBaseImage.SetPosition(uiPos_);
	uiBaseImage.SetSize({ 0.7f,0.87f,0 });
	AddComponent<Image>(uiBaseImage);

	Text uiTitleText(this);
	uiTitleText.SetText("ëfçﬁ");
	uiTitleText.SetPosition({ 1200,30 });
	AddComponent<Text>(uiTitleText);
	XMFLOAT2 itemPos = { -0.3f,0.68f };
	for (int i = 0; i < 30; i++)
	{
		GameObject* item = Instantiate<ResourceItem>(this);
		item->GetComponent<Image>().SetPosition({ uiPos_.x + itemPos.x,uiPos_.y + itemPos.y,0 });
		item->GetComponent<Image>().SetSize({ 0.9f,0.9f,0 });
		itemPos.x += 0.15f;
		if((i+1)%5==0)
		{
			itemPos.x = -0.3f;
			itemPos.y -= 0.27f;
		}
	}
}

void P_MP_CraftUI_ResourceStockUI::Start()
{
}

void P_MP_CraftUI_ResourceStockUI::Update()
{
}

void P_MP_CraftUI_ResourceStockUI::Release()
{
}
