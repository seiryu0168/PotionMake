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
	backImage.SetSize({ 4.0f,2.0f,0 });
	AddComponent<Image>(backImage);

	XMFLOAT3 txtPos = backImage.GetPositionAtPixel();
	Text totalGainText(this);
	totalGainText.SetText("10000");
	totalGainText.SetPosition({ txtPos.x + 150,txtPos.y - 50 });
	AddComponent<Text>(totalGainText);
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

	Image potionBase(this);
	potionBase.Load("Assets/Image/Potion_BaseImage.png");
	potionBase.SetSize({ 0.5f,0.5f,0 });
	potionBase.SetColor(color);
	AddComponent<Image>(potionBase);

	Image potionEdge(this);
	potionEdge.Load("Assets/Image/Potion_EdgeImage.png");
	potionEdge.SetSize({ 0.5f,0.5f,0 });
	AddComponent<Image>(potionEdge);

	GetComponent<Text>().SetText(std::to_string(price));
}

void P_MP_SettiementUI_Potion::SetPosition(const XMFLOAT3& pos)
{
	GetComponent<Image>(0).SetPosition(pos);
	GetComponent<Image>(1).SetPosition({ pos.x - 0.2f,pos.y,0 });
	GetComponent<Image>(2).SetPosition({ pos.x - 0.2f,pos.y,0 });
	XMFLOAT3 txtPos = GetComponent<Image>(0).GetPositionAtPixel();
	GetComponent<Text>().SetPosition({ txtPos.x,txtPos.y + 40 });
}

void P_MP_SettiementUI_Potion::Release()
{
}
