#pragma once
#include"StandData.h"
#include<vector>
#include"Engine/DirectX_11/Math.h"
class PlayerData : public StandData
{
public:
	struct ResourceData_
	{
		int itemNum_;
		std::string itemName_;
		std::string itemImageName_;
		int itemCount_;
		ResourceData_()
		{
			itemNum_;
			itemName_ = "";
			itemImageName_ = "";
			itemCount_ = 0;
		}
	};
	struct PotionData
	{
		std::string potionName_;
		bool isSale_;
		std::vector<float> potionStatus_;
		XMFLOAT3 potionColor_;
		PotionData()
		{
			potionName_ = "";
			isSale_ = false;
			potionStatus_ = { 0,0,0,0,0 };
			potionColor_ = { 0,0,0 };
		}
	};
	void SortResourceList();
	void AddResourceItemData(const ResourceData_& resource);
	std::string name_;
	std::string resourceFileName_;
	std::string potionDataFileName_;
	std::vector<ResourceData_> itemDataList_;
	std::vector<PotionData> potionDataList_;
};

