#include "FinishCraftUI.h"
#include"Engine/Systems/ImageSystem.h"
FinishCraftUI::FinishCraftUI(Object* parent)
	:GameObject(parent,"FinishCraftUI")
{
}

FinishCraftUI::~FinishCraftUI()
{
}

void FinishCraftUI::Initialize()
{
	Image backImage(this);
	backImage.Load("Assets/Image/PotionManagerUIBase1.png");
	backImage.SetSize({ 2,2,0 });
	backImage.SetLayer(2);
	AddComponent<Image>(backImage);
}

void FinishCraftUI::Start()
{
}

void FinishCraftUI::Update()
{
}

void FinishCraftUI::Release()
{
}
