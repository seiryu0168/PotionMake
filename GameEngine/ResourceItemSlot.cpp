#include "ResourceItemSlot.h"
#include"Engine/Systems/ImageSystem.h"
ResourceItemSlot::ResourceItemSlot(Object* parent)
	:GameObject(parent,"ResourceItemSlot"),
	haveItem_(false)
{
}

ResourceItemSlot::~ResourceItemSlot()
{
}

void ResourceItemSlot::Initialize()
{
	Image slotImage(this);
	slotImage.Load("Assets/Image/ItemSlotImage.png");
	AddComponent<Image>(slotImage);
	//haveItem_ = true;

}

void ResourceItemSlot::Start()
{
}

void ResourceItemSlot::Update()
{
}

void ResourceItemSlot::SetItem(int itemNum)
{
	XMFLOAT3 pos = GetComponent<Image>().GetPosition();

	RemoveComponent<Image>();

	Image slotImage(this);
	slotImage.Load("Assets/Image/ItemBaseImage.png");
	slotImage.SetPosition(pos);
	AddComponent<Image>(slotImage);
	haveItem_ = true;
}

void ResourceItemSlot::Release()
{
}
