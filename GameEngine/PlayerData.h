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
		int tier_;
		bool isSale_;
		int topStatus_;
		int price_;
		std::vector<float> potionStatus_;
		XMFLOAT3 potionColor_;
		PotionData()
		{
			potionName_ = "";
			isSale_ = false;
			topStatus_ = 0;
			price_ = 0;
			potionStatus_ = { 0,0,0,0,0 };
			potionColor_ = { 0,0,0 };
		}
	};
	PlayerData();
	~PlayerData();
	void SortResourceList();
	void AddResourceItemData(const ResourceData_& resource);
	int maxItemLimit_;
	std::string name_;
	int money_;
	int newsPaperNumber_;
	std::string resourceFileName_;
	std::string potionDataFileName_;
	std::vector<ResourceData_> itemDataList_;
	std::vector<PotionData> potionDataList_;
	std::vector<int> gainList_;
};

