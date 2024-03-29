#include "P_MP_CraftUI_CraftPot.h"
#include"Engine/Systems/ImageSystem.h"
#include"Engine/Systems/TextSystem.h"
#include"ResourceItem.h"
#include"ResourceItemSlot.h"


P_MP_CraftUI_CraftPot::P_MP_CraftUI_CraftPot(Object* parent)
	:GameObject(parent,"P_MP_CraftUI_CraftPot"),
	standPosition_({-0.8f,0.6f})
{
}

P_MP_CraftUI_CraftPot::~P_MP_CraftUI_CraftPot()
{
}

void P_MP_CraftUI_CraftPot::Initialize()
{
	//GameObject* item = Instantiate<ResourceItem>(this);
	//item->GetComponent<Image>().SetPosition({ standPosition_.x,standPosition_.y,0 });
	XMFLOAT2 itemPos = { 0,0 };
	for (int i = 0; i < 12; i++)
	{
		GameObject* item = Instantiate<ResourceItemSlot>(this);
		item->GetComponent<Image>().SetPosition({ standPosition_.x+itemPos.x,standPosition_.y+itemPos.y,0 });
		itemPos.x += 0.15f;
		if ((i + 1) % 4 == 0)
		{
			itemPos.x = 0;
			itemPos.y -= 0.27f;
		}
		//((ResourceItemSlot*)item)->SetItem(true);
		objects_.push_back(item);
	}
}

void P_MP_CraftUI_CraftPot::Start()
{
}

void P_MP_CraftUI_CraftPot::Update()
{
}

void P_MP_CraftUI_CraftPot::AddResourceData(int itemNum)
{
	if (dataMap_.find(itemNum) == dataMap_.end())
	{
		dataMap_.insert({ itemNum, 1 });
		DisplayResource(itemNum);
		return;
	}
	dataMap_[itemNum]++;
}

void P_MP_CraftUI_CraftPot::DisplayResource(int itemNum)
{
	for (int i = 0; i < objects_.size(); i++)
	{
		if (!((ResourceItemSlot*)objects_[i])->HaveItem())
		{
			((ResourceItemSlot*)objects_[i])->SetItem(itemNum);
			return;

		}

	}
}

void P_MP_CraftUI_CraftPot::Release()
{
}
