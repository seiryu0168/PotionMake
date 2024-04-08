#include "P_MP_PotionManagerUI_SellStockUI.h"
#include"Engine/Systems/ImageSystem.h"
#include"Engine/Systems/TextSystem.h"
#include"PotionSlot.h"
P_MP_PotionManagerUI_SellStockUI::P_MP_PotionManagerUI_SellStockUI(Object* parent)
	:GameObject(parent,"P_MP_PotionManagerUI_SellStockUI"),
	standPosition_({-0.9f,0.23f})
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
	uiTitleText.SetText("売るポーション");
	uiTitleText.SetTextSize(55.0f);
	uiTitleText.SetPosition({ 30,210 });	
	AddComponent<Text>(uiTitleText);

	XMFLOAT2 diff = { 0,0 };
	for (int i = 0; i < 5; i++)
	{
		GameObject* potion = Instantiate<PotionSlot>(this);
		potion->GetComponent<Image>().SetPosition({ standPosition_.x + diff.x,standPosition_.y + diff.y,0 });
		diff.x += 0.15;
		objects_.push_back(potion);
	}
}

void P_MP_PotionManagerUI_SellStockUI::Start()
{
}

void P_MP_PotionManagerUI_SellStockUI::Update()
{
}

void P_MP_PotionManagerUI_SellStockUI::AddSellPotion(int potionNum, const std::string& name, const XMFLOAT3& potionColor)
{
	//販売するポーション枠に追加する
	for (GameObject* potion : objects_)
	{
		if (((PotionSlot*)potion)->GetPotionNumber() == -1)
		{
			((PotionSlot*)potion)->SetPotion(potionNum, name, potionColor);
			return;
		}
	}
}

void P_MP_PotionManagerUI_SellStockUI::SubSellPotion(int potionNum)
{
	//販売するポーション枠から消す
	for (GameObject* potion : objects_)
	{
		if (((PotionSlot*)potion)->GetPotionNumber() == potionNum)
		{
			((PotionSlot*)potion)->RemovePotion();
			return;
		}
	}
}

void P_MP_PotionManagerUI_SellStockUI::Release()
{
}
