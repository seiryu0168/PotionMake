#include "P_MP_SettiementUI_Potion.h"
#include "../../Engine/Systems/ImageSystem.h"
#include "../../Engine/Systems/TextSystem.h"
P_MP_SettiementUI_Potion::P_MP_SettiementUI_Potion(Object* parent)
	:GameObject(parent,"P_MP_SettiementUI_Potion"),
	isSetFirstPosition_(false),
	potionTier_(0),
	potionName_(""),
	potionColor_({0,0,0}),
	price_(0),
	count_(0)
{
}

P_MP_SettiementUI_Potion::~P_MP_SettiementUI_Potion()
{
}

void P_MP_SettiementUI_Potion::Initialize()
{
	Image backImage(this);
	backImage.Load("Assets/Image/PotionListBackImage.png");
	backImage.SetPosition({ 0,0,0 });
	//backImage.SetSize({ 3.7f,1.5f,0 });
	AddComponent<Image>(backImage);

	XMFLOAT3 txtPos = backImage.GetPositionAtPixel();
	XMFLOAT3 size = backImage.GetSizeAtPixel();
	Text totalGainText(this, "Rounded M+ 1c");
	totalGainText.SetText("0");
	totalGainText.SetAlignmentType(ALIGNMENT_TYPE::RIGHT_BOTTOM);
	totalGainText.SetColorInt({ 60,60,60,255 });
	totalGainText.SetRect({ 0,0,size.x,size.y });
	totalGainText.SetPosition({ txtPos.x -size.x*0.5f-50,txtPos.y - size.y*0.5f-30 });
	AddComponent<Text>(totalGainText);
}

void P_MP_SettiementUI_Potion::Start()
{
}

void P_MP_SettiementUI_Potion::Update()
{
}

void P_MP_SettiementUI_Potion::SetPotionData(int potionTier, const std::string& name, const XMFLOAT3& color, int price,int count)
{
	XMFLOAT3 txtPos = GetComponent<Image>().GetPositionAtPixel();
	XMFLOAT3 size = GetComponent<Image>().GetSizeAtPixel();
	potionTier_ = potionTier;
	potionName_ = name;
	price_ = price;
	count_ = count;

	//ポーションのベース画像
	Image potionBase(this);
	potionBase.Load("Assets/Image/Potion_BaseImage.png");
	potionBase.SetSize({ 0.3f,0.3f,0 });
	potionBase.SetColor(color);
	AddComponent<Image>(potionBase);

	//ポーションの枠画像
	Image potionEdge(this);
	potionEdge.Load("Assets/Image/Potion_EdgeImage.png");
	potionEdge.SetSize({ 0.3f,0.3f,0 });
	AddComponent<Image>(potionEdge);

	//ポーション名
	Text nameText(this, "Rounded M+ 1c");
	nameText.SetText(name);
	nameText.SetTextSize(30);
	nameText.SetColorInt({ 60,60,60,255 });
	nameText.SetRect({ 0,0,size.x,size.y });
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
	XMFLOAT3 txtPos = GetComponent<Image>().GetPositionAtPixel();
	XMFLOAT3 size = GetComponent<Image>().GetSizeAtPixel();
	GetComponent<Text>(0).SetPosition({ txtPos.x - size.x * 0.5f-50,txtPos.y -size.y * 0.5f-30 });
	GetComponent<Text>(1).SetPosition({ txtPos.x - size.x * 0.5f,txtPos.y - size.y * 0.5f + 40 });
}

void P_MP_SettiementUI_Potion::AddPosition(float move)
{
	GetComponent<Image>(0).SetPosition({ firstPos_.x,firstPos_.y + move,0 });
	GetComponent<Image>(1).SetPosition({ firstPos_.x - 0.2f,firstPos_.y + move,0 });
	GetComponent<Image>(2).SetPosition({ firstPos_.x - 0.2f,firstPos_.y + move,0 });
	XMFLOAT3 txtPos = GetComponent<Image>().GetPositionAtPixel();
	XMFLOAT3 size = GetComponent<Image>().GetSizeAtPixel();
	GetComponent<Text>(0).SetPosition({ txtPos.x - size.x * 0.5f-50,txtPos.y - size.y * 0.5f-30 });
	GetComponent<Text>(1).SetPosition({ txtPos.x - size.x * 0.5f,txtPos.y - size.y * 0.5f + 40 });
}

void P_MP_SettiementUI_Potion::Release()
{
}
