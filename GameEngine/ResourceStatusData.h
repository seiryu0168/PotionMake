#pragma once
#include"StandData.h"
#include<unordered_map>
class ResourceStatusData : public StandData
{
public:
	struct ResourceStatus
	{
		int resourceNumber_;
		float status00_;
		float status01_;
		float status02_;
		float status03_;
		float status04_;
	};
	std::unordered_map<int, ResourceStatus> resourceDataMap_;
	//void AddResourceStatus()
};

