#include "ResourceItem.h"
#include"Engine/DirectX_11/Input.h"
#include"Engine/Systems/ImageSystem.h"
#include"Engine/Systems/TextSystem.h"
#include"P_MP_CraftUI_CraftPot.h"
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
	//potObject_ = (GameObject*)FindObject("P_MP_CraftUI_CraftPot");
}

void ResourceItem::Update()
{
	//if (Input::IsMouseButtonDown(0) && GetComponent<Image>().IsHitCursor())
	//{
	//	((P_MP_CraftUI_CraftPot*)potObject_)->
	//}
	//if (Input::IsMouseButtonDown(0)&&GetComponent<Image>().IsHitCursor())
	//{
	//	GetComponent<Image>().SetColor({ 0.3f,0.3f,0.3f });
	//}
}

void ResourceItem::Release()
{
}
