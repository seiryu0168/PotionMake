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
	struct PotionData
	{
		std::string potionName_;
		std::vector<float> potionStatus_;
		PotionData()
		{
			potionName_ = "";
			potionStatus_ = { 0,0,0,0,0 };
		}
	};
	std::string name_;
	std::string resourceFileName_;
	std::string potionDataFileName_;
	std::vector<ResourceData_> itemDataList_;
	std::vector<PotionData> potionDataList_;
};

