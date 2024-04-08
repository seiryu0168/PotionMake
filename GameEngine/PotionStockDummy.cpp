#include "PotionStockDummy.h"
#include"Engine/Systems/ImageSystem.h"
PotionStockDummy::PotionStockDummy(Object* parent)
	:GameObject(parent,"PotionStockDummy")
{
}

PotionStockDummy::~PotionStockDummy()
{
}

void PotionStockDummy::Initialize()
{
	Image potionStockImage(this);
	potionStockImage.Load("Assets/Image/ItemSlotImage.png");
	potionStockImage.SetLayer(0);
	AddComponent<Image>(potionStockImage);
}

void PotionStockDummy::Start()
{
}

void PotionStockDummy::Update()
{
}

void PotionStockDummy::Release()
{
}
