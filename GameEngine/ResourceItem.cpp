#include "ResourceItem.h"
#include"Engine/Systems/ImageSystem.h"
#include"Engine/Systems/TextSystem.h"
ResourceItem::ResourceItem(Object* parent)
	:ItemBase(parent,"ResourceItem")
{
}

ResourceItem::~ResourceItem()
{
}

void ResourceItem::Initialize()
{
	Image itemBaseImage(this);
	itemBaseImage.Load("Assets/Image/ItemBaseImage.png");
	AddComponent<Image>(itemBaseImage);
}

void ResourceItem::Start()
{
}

void ResourceItem::Update()
{
}

void ResourceItem::Release()
{
}
