#include "PickupedItemDetailUI.h"
#include"Engine/Systems/ImageSystem.h"
#include"Engine/Systems/TextSystem.h"
#include"P_CP_CollectedItemUI.h"
#include"CloseButton.h"
#include"InterSceneData.h"
#include"ResourceStatusData.h"
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

void PickupedItemDetailUI::SetItemData(int itemNum)
{
	ResourceStatusData* rData = InterSceneData::GetData<ResourceStatusData>("ResourceData");
	Image itemImage(this);
	itemImage.Load("Assets/Image/"+rData->resourceDataMap_[itemNum].resourceImageName_);
	itemImage.SetSize({ 0.5f,0.5f,0 });
	AddComponent<Image>(itemImage);
	
}

void PickupedItemDetailUI::Release()
{
	((P_CP_CollectedItemUI*)pParent_->GetParent())->SetSelectFlag(true);
}
