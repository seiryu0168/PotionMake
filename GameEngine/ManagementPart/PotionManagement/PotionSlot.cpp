#include "PotionSlot.h"
#include"../../Engine/Systems/ImageSystem.h"
PotionSlot::PotionSlot(Object* parent)
	:GameObject(parent,"PotionSlot"),
	potionNum_(-1)
{
}

PotionSlot::~PotionSlot()
{
}

void PotionSlot::Initialize()
{
	Image image(this);
	image.Load("Assets/Image/ItemSlotImage.png");
	AddComponent<Image>(image);
}

void PotionSlot::Start()
{
	XMFLOAT3 pos = GetComponent<Image>().GetPosition();
	Image potionBaseImage(this);
	potionBaseImage.Load("Assets/Image/Potion_BaseImage.png");
	potionBaseImage.SetLayer(0);
	potionBaseImage.SetPosition(pos);
	potionBaseImage.SetSize({ 0.25f,0.25,0 });
	potionBaseImage.SetColor({ 1,1,1,0.4f });
	potionImageNum_ = AddComponent<Image>(potionBaseImage);

	Image potionEdgeImage(this);
	potionEdgeImage.Load("Assets/Image/Potion_EdgeImage.png");
	potionEdgeImage.SetLayer(1);
	potionEdgeImage.SetPosition(pos);
	potionEdgeImage.SetSize({ 0.25f,0.25,0 });
	AddComponent<Image>(potionEdgeImage);
}

void PotionSlot::Update()
{
}

void PotionSlot::SetPotion(int potionNum, const std::string& name, const XMFLOAT3& color)
{
	//ポーションデータを設定
	potionNum_ = potionNum;
	GetComponent<Image>(potionImageNum_).SetColor({ color.x,color.y,color.z,1 });
}

void PotionSlot::RemovePotion()
{
	//ポーションを消す
	GetComponent<Image>(potionImageNum_).SetColor({ 1,1,1,0.4f });
	potionNum_ = -1;
}

void PotionSlot::Release()
{
}
