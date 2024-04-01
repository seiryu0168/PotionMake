#include "ResourceItemSlot.h"
#include"Engine/Systems/ImageSystem.h"
ResourceItemSlot::ResourceItemSlot(Object* parent)
	:ItemBase(parent,"ResourceItemSlot"),
	haveResource_(false)
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
	//haveResource_ = true;

}

void ResourceItemSlot::Start()
{
}

void ResourceItemSlot::Update()
{
}

void ResourceItemSlot::SetItem(std::string imageName,int itemNum)
{
	XMFLOAT3 pos = GetComponent<Image>().GetPosition();

	RemoveComponent<Image>();

	Image slotImage(this);
	slotImage.Load("Assets/Image/"+ imageName);
	XMFLOAT3 size = slotImage.GetSizeAtPixel();
	slotImage.SetSize({ 128.0f / size.x,128.0f / size.y,0 });
	slotImage.SetPosition(pos);
	AddComponent<Image>(slotImage);
	haveResource_ = true;
	itemNum_ = itemNum;
}

void ResourceItemSlot::ItemEmpty()
{
	XMFLOAT3 pos = GetComponent<Image>().GetPosition();

	RemoveComponent<Image>();

	Image slotImage(this);
	slotImage.Load("Assets/Image/ItemSlotImage.png");
	XMFLOAT3 size = slotImage.GetSizeAtPixel();
	slotImage.SetSize({ 128.0f / size.x,128.0f / size.y,0 });
	slotImage.SetPosition(pos);
	AddComponent<Image>(slotImage);
	haveResource_ = false;
	itemNum_ = -1;
}

void ResourceItemSlot::Release()
{
}
