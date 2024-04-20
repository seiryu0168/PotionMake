#include "PlayerData.h"

void PlayerData::SortResourceList()
{
	std::vector<ResourceData_> newItemDataList;
	int minIndex = 0;
	//‘fŞ”Ô†‚ğ‚à‚Æ‚Éƒ\[ƒg
	for (int i = 0; i < itemDataList_.size(); i++)
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
	//‘fŞ‚Ì”‚ª0‚Ì—v‘f‚ğÁ‚·
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
		rData->itemCount_ += resource.itemCount_;
}
