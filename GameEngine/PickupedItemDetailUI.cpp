#include "PickupedItemDetailUI.h"
#include"Engine/Systems/ImageSystem.h"
#include"Engine/Systems/TextSystem.h"
#include"CloseButton.h"
PickupedItemDetailUI::PickupedItemDetailUI(Object* parent)
	:GameObject(parent, "PickupedItemDetailUI")
{
}

PickupedItemDetailUI::~PickupedItemDetailUI()
{
}

void PickupedItemDetailUI::Initialize()
{
	GameObject* button = Instantiate<CloseButton>(this);
	button->GetComponent<Image>().SetPosition({ -0.4,0.5,0 });
}

void PickupedItemDetailUI::Start()
{
}

void PickupedItemDetailUI::Update()
{
}

void PickupedItemDetailUI::Release()
{
}
