#include "PotionSlot.h"
#include"Engine/Systems/ImageSystem.h"
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

void PotionSlot::Update()
{
}

void PotionSlot::Release()
{
}
