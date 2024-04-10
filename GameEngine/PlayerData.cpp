#include "PlayerData.h"

void PlayerData::SortResourceList()
{
	std::vector<ResourceData_> newItemDataList;
	int minIndex = 0;
	//�f�ޔԍ������ƂɃ\�[�g
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
	//�f�ނ̐���0�̗v�f������
	itemDataList_.erase(std::remove_if(itemDataList_.begin(),
									   itemDataList_.end(),
									   [&](ResourceData_ value)
									   {return value.itemCount_ <= 0; }),
									   itemDataList_.end());
}
