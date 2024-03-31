#pragma once
#include"InterSceneData.h"
class PlayerData : public StandData
{
public:
	std::string name_;
	std::string resourceFileName_;
	std::string potionDataFileName_;
	std::vector<std::pair<std::string, int>> itemDataList_;
};

