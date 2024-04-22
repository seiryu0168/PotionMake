#include "P_MP_SettiementUI_Potion.h"
#include"Engine/Systems/ImageSystem.h"
#include"Engine/Systems/TextSystem.h"
P_MP_SettiementUI_Potion::P_MP_SettiementUI_Potion(Object* parent)
	:GameObject(parent,"P_MP_SettiementUI_Potion")
{
}

P_MP_SettiementUI_Potion::~P_MP_SettiementUI_Potion()
{
}

void P_MP_SettiementUI_Potion::Initialize()
{
	Image backImage(this);
	backImage.Load("Assets/Image/ItemBaseImage.png");
	backImage.SetPosition({ 0,0,0 });
}

void P_MP_SettiementUI_Potion::Start()
{
}

void P_MP_SettiementUI_Potion::Update()
{
}

void P_MP_SettiementUI_Potion::SetPotionData(int potionTier, const std::string& name, const XMFLOAT3& color, int price)
{
	potionTier_ = potionTier;
	potionName_ = name;
	price_ = price;

}

void P_MP_SettiementUI_Potion::SetPosition(const XMFLOAT3& pos)
{
	GetComponent<Image>().SetPosition(pos);
}

void P_MP_SettiementUI_Potion::Release()
{
}
