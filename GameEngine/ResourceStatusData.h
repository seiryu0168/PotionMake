#pragma once
#include"StandData.h"
#include<unordered_map>
#include"Engine/DirectX_11/Math.h"
class ResourceStatusData : public StandData
{
public:
	struct ResourceStatus
	{
		int resourceNumber_;
		std::string resourceName_;
		std::string resourceImageName_;
		std::string resourceModelName_;
		float status00_;
		float status01_;
		float status02_;
		float status03_;
		float status04_;
		std::string explanation_;

		ResourceStatus()
		{
			resourceNumber_ = -1;
			resourceName_ = "";
			resourceImageName_ = "";
			status00_=0;
			status01_=0;
			status02_=0;
			status03_=0;
			status04_=0;
			explanation_ = "";
		}
	};
	std::unordered_map<int, ResourceStatus> resourceDataMap_;
	std::unordered_map<int, ResourceStatus> processDataMap_;
	std::vector<ResourceStatus> newsPaperList_;
	std::vector<XMFLOAT3> statusColor_;
	//void AddResourceStatus()
};

