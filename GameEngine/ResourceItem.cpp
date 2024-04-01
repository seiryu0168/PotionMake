#include "ResourceItem.h"
#include"Engine/DirectX_11/Input.h"
#include"Engine/Systems/ImageSystem.h"
#include"Engine/Systems/TextSystem.h"
#include"P_MP_CraftUI_CraftPot.h"


ResourceItem::ResourceItem(Object* parent)
	:ItemBase(parent,"ResourceItem"),
	isLoadedImage_(false),
	resourceCount_(0)
{
}

ResourceItem::~ResourceItem()
{
}

void ResourceItem::Initialize()
{
	//Image itemBaseImage(this);
	//itemBaseImage.Load("Assets/Image/ItemBaseImage.png");
	//AddComponent<Image>(itemBaseImage);
}

void ResourceItem::Start()
{
	potObject_ = (GameObject*)FindObject("P_MP_CraftUI_CraftPot");
}

void ResourceItem::Update()
{
	if (Input::IsMouseButtonDown(0) && GetComponent<Image>().IsHitCursor())
	{
		((P_MP_CraftUI_CraftPot*)potObject_)->AddResourceData(itemNum_);
	}
	//if (Input::IsMouseButtonDown(0)&&GetComponent<Image>().IsHitCursor())
	//{
	//	GetComponent<Image>().SetColor({ 0.3f,0.3f,0.3f });
	//}
}

void ResourceItem::LoadItem(std::string name,int resourceCount)
{
	if (isLoadedImage_ == true)
		return;
	resourceCount_ = resourceCount;
	if (resourceCount <= 0)
	{
		Image itemBaseImage(this);
		itemBaseImage.Load("Assets/Image/ItemSlotImage.png");
		AddComponent<Image>(itemBaseImage);
	}
	else
	{
		Image itemBaseImage(this);
		itemBaseImage.Load("Assets/Image/" + name);
		AddComponent<Image>(itemBaseImage);

	}
	isLoadedImage_ = true;
}

void ResourceItem::Release()
{
}
