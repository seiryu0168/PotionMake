#include "PlayerData.h"

PlayerData::PlayerData()
	:maxItemLimit_(999),
	isFirstPlay_(true)

{
}

PlayerData::~PlayerData()
{
}

void PlayerData::SortResourceList()
{
	int minIndex = 0;
	//ëfçﬁî‘çÜÇÇ‡Ç∆Ç…É\Å[Ég
	int size= itemDataList_.size();
	for (int i = 0; i < size; i++)
	{
		minIndex = i;
		for (int j = i + 1; j < itemDataList_.size(); j++)
		{
			if ((itemDataList_[j].itemNum_ <= itemDataList_[minIndex].itemNum_))
			{
				minIndex = j;
			}
		}
		ResourceData_ buffData = itemDataList_[i];
		itemDataList_[i] = itemDataList_[minIndex];
		itemDataList_[minIndex] = buffData;
	}
	//ëfçﬁÇÃêîÇ™0ÇÃóvëfÇè¡Ç∑
	itemDataList_.erase(std::remove_if(itemDataList_.begin(),
									   itemDataList_.end(),
									   [&](ResourceData_ value)
									   {return value.itemCount_ <= 0; }),
									   itemDataList_.end());
}

void PlayerData::AddResourceItemData(const ResourceData_& resource)
{
	auto rData = std::find_if(itemDataList_.begin(), itemDataList_.end(), [&](PlayerData::ResourceData_ value) {return value.itemNum_ == resource.itemNum_; });
	if (rData == itemDataList_.end())
	{
		itemDataList_.push_back(resource);
	}
	else
	{
		rData->itemCount_ += resource.itemCount_;
		rData->itemCount_ = Clamp(rData->itemCount_, 0, maxItemLimit_);
	}
}
