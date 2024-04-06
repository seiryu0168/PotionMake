#include "P_MP_PotionManagerUI_DisposeStockUI.h"
#include"Engine/Systems/ImageSystem.h"
#include"Engine/Systems/TextSystem.h"
#include"PotionSlot.h"
P_MP_PotionManagerUI_DisposeStockUI::P_MP_PotionManagerUI_DisposeStockUI(Object* parent)
	:GameObject(parent,"P_MP_PotionManagerUI_DisposeStockUI"),
	standPosition_({-0.9f,-0.52f})
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

	XMFLOAT2 diff = { 0,0 };
	for (int i = 0; i < 5; i++)
	{
		PotionSlot* potion = Instantiate<PotionSlot>(this);
		potion->GetComponent<Image>().SetPosition({ standPosition_.x + diff.x,standPosition_.y + diff.y,0 });
		diff.x += 0.15;
		objects_.push_back(potion);
	}
}

void P_MP_PotionManagerUI_DisposeStockUI::Start()
{
}

void P_MP_PotionManagerUI_DisposeStockUI::Update()
{
}

void P_MP_PotionManagerUI_DisposeStockUI::AddDisposePotion(int potionNum, const std::string& name, const XMFLOAT3& potionColor)
{
	for (GameObject* potion : objects_)
	{
		if (((PotionSlot*)potion)->GetPotionNumber() == -1)
		{
			((PotionSlot*)potion)->SetPotion(potionNum,name, potionColor);
			return;	
		}
	}
}

void P_MP_PotionManagerUI_DisposeStockUI::SubDisposePotion(int potionNum)
{
	for (GameObject* potion : objects_)
	{
		if (((PotionSlot*)potion)->GetPotionNumber() == potionNum)
		{
			((PotionSlot*)potion)->RemovePotion();
			return;
		}
	}
}

void P_MP_PotionManagerUI_DisposeStockUI::Release()
{
}
