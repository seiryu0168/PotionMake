#include "P_MP_CraftUI_CraftPot.h"
#include"Engine/Systems/ImageSystem.h"
#include"Engine/Systems/TextSystem.h"
#include"ResourceItem.h"


P_MP_CraftUI_CraftPot::P_MP_CraftUI_CraftPot(Object* parent)
	:GameObject(parent,"P_MP_CraftUI_CraftPot"),
	standPosition_({0.2f,0.2f})
{
}

P_MP_CraftUI_CraftPot::~P_MP_CraftUI_CraftPot()
{
}

void P_MP_CraftUI_CraftPot::Initialize()
{
	GameObject* item = Instantiate<ResourceItem>(this);
	item->GetComponent<Image>().SetPosition({ standPosition_.x,standPosition_.y,0 });
	//for (int i = 0; i < 12; i++)
	//{
	//
	//}
}

void P_MP_CraftUI_CraftPot::Start()
{
}

void P_MP_CraftUI_CraftPot::Update()
{
}

void P_MP_CraftUI_CraftPot::AddResourceData(int itemNum)
{
	//if (dataMap_.find(itemNum) == dataMap_.end())
	//{
	//	dataMap_.insert(itemNum, 1);
	//	return;
	//}
	//dataMap_[itemNum]++;

}

void P_MP_CraftUI_CraftPot::DisplayResource(int itemNum)
{

}

void P_MP_CraftUI_CraftPot::Release()
{
}
