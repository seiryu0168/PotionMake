#include "P_MP_SettiementUI_Potion.h"
#include "../../Engine/Systems/ImageSystem.h"
#include "../../Engine/Systems/TextSystem.h"
P_MP_SettiementUI_Potion::P_MP_SettiementUI_Potion(Object* parent)
	:GameObject(parent,"P_MP_SettiementUI_Potion"),
	isSetFirstPosition_(false)
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
	backImage.SetSize({ 4.3f,2.0f,0 });
	AddComponent<Image>(backImage);

	XMFLOAT3 txtPos = backImage.GetPositionAtPixel();
	Text totalGainText(this);
	totalGainText.SetText("10000");
	totalGainText.SetAlignmentType(ALIGNMENT_TYPE::RIGHT_TOP);
	totalGainText.SetRect({ 0,0,256,128 });
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

	//ポーチションのベース画像
	Image potionBase(this);
	potionBase.Load("Assets/Image/Potion_BaseImage.png");
	potionBase.SetSize({ 0.5f,0.5f,0 });
	potionBase.SetColor(color);
	AddComponent<Image>(potionBase);

	//ポーチションの枠画像
	Image potionEdge(this);
	potionEdge.Load("Assets/Image/Potion_EdgeImage.png");
	potionEdge.SetSize({ 0.5f,0.5f,0 });
	AddComponent<Image>(potionEdge);

	//ポーチション名
	Text nameText(this);
	nameText.SetText(name);
	nameText.SetTextSize(40);
	nameText.SetRect({ 0,0,512,128 });
	nameText.SetAlignmentType(ALIGNMENT_TYPE::CENTER_TOP);
	AddComponent<Text>(nameText);
	GetComponent<Text>().SetText(std::to_string(price));
}

void P_MP_SettiementUI_Potion::SetFirstPosition(const XMFLOAT3& pos)
{
	firstPos_ = pos;
	GetComponent<Image>(0).SetPosition(pos);
	GetComponent<Image>(1).SetPosition({ pos.x - 0.2f,pos.y,0 });
	GetComponent<Image>(2).SetPosition({ pos.x - 0.2f,pos.y,0 });
	XMFLOAT3 txtPos = GetComponent<Image>(0).GetPositionAtPixel();
	GetComponent<Text>(0).SetPosition({ txtPos.x-10,txtPos.y + 20 });
	GetComponent<Text>(1).SetPosition({ txtPos.x - 190,txtPos.y - 100 });
}

void P_MP_SettiementUI_Potion::AddPosition(float move)
{
	GetComponent<Image>(0).SetPosition({ firstPos_.x,firstPos_.y + move,0 });
	GetComponent<Image>(1).SetPosition({ firstPos_.x - 0.2f,firstPos_.y + move,0 });
	GetComponent<Image>(2).SetPosition({ firstPos_.x - 0.2f,firstPos_.y + move,0 });
	XMFLOAT3 txtPos = GetComponent<Image>(0).GetPositionAtPixel();
	GetComponent<Text>(0).SetPosition({ txtPos.x-10,txtPos.y + 20 });
	GetComponent<Text>(1).SetPosition({ txtPos.x - 190,txtPos.y - 100 });
}

void P_MP_SettiementUI_Potion::Release()
{
}
