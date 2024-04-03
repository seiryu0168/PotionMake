#pragma once
#include"StandData.h"
class PlayerData : public StandData
{
public:
	struct ResourceData_
	{
		std::string itemName_;
		std::string itemImageName_;
		int itemCount_;
		ResourceData_()
		{
			itemName_ = "";
			itemImageName_ = "";
			itemCount_ = 0;
		}
	};
	std::string name_;
	std::string resourceFileName_;
	std::string potionDataFileName_;
	std::vector<ResourceData_> itemDataList_;
};

