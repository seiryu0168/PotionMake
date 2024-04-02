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
		XMFLOAT3 textBasePos = item->GetComponent<Image>().GetPositionAtPixel();
		item->GetComponent<Text>().SetPosition({ textBasePos.x + 10,textBasePos.y+15 });
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

void P_MP_CraftUI_CraftPot::AddResourceData(int itemNum,std::string resourceName, std::string imageName)
{
	if (dataMap_.find(itemNum) == dataMap_.end())
	{
		ResourceData data{ resourceName,imageName,1 };
		dataMap_.insert({ itemNum, data });
		DisplayResource(itemNum);
		return;
	}
	dataMap_[itemNum].resourceCount_++;

	for (GameObject* obj : objects_)
	{
		if (((ResourceItemSlot*)obj)->GetItemNumber() == itemNum)
		{
			((ResourceItemSlot*)obj)->AddCount(1);
			break;
		}
	}
}

bool P_MP_CraftUI_CraftPot::SubResourceData(int itemNum)
{
	if (dataMap_.find(itemNum) == dataMap_.end())
		return false;

		dataMap_.find(itemNum)->second.resourceCount_--;
		if (dataMap_.find(itemNum)->second.resourceCount_ <= 0)
		{
			HiddenResource(itemNum);
			dataMap_.erase(itemNum);
			return true;
		}
		for (GameObject* obj : objects_)
		{
			if (((ResourceItemSlot*)obj)->GetItemNumber() == itemNum)
			{
				((ResourceItemSlot*)obj)->SubCount(1);
				break;
			}
		}
		return true;
}

void P_MP_CraftUI_CraftPot::DisplayResource(int itemNum)
{
	for (int i = 0; i < objects_.size(); i++)
	{
		if (!((ResourceItemSlot*)objects_[i])->HaveItem())
		{
			((ResourceItemSlot*)objects_[i])->SetItem(dataMap_[itemNum].imageName_,itemNum);
			return;
		}
	}
}

void P_MP_CraftUI_CraftPot::HiddenResource(int itemNum)
{
	for (int i = 0; i < objects_.size(); i++)
	{
		if (((ResourceItemSlot*)objects_[i])->GetItemNumber()==itemNum)
		{
			((ResourceItemSlot*)objects_[i])->ItemEmpty();
			return;
		}
	}
}


void P_MP_CraftUI_CraftPot::Release()
{
}
