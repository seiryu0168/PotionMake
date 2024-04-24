#pragma once
#include"Engine/ResourceManager/json.hpp"
#include"PlayerData.h"
#include"ResourceStatusData.h"
namespace PlayerData_Test
{
	struct SaveData
	{
		std::string name_;
		std::string resourceFileName_;
		std::string potionDataFileName_;
		std::vector<std::pair<std::string, int>> itemData_;
	};
}

class SaveDataManager
{
	//nlohmann::json jsonFile_;

	std::string utf8_to_SJis(std::string const& str);
	std::u8string SJis_to_utf8(std::string const& str);

public:
	SaveDataManager();
	~SaveDataManager();
	void Init();
	void Load(std::string fileName,PlayerData& data);
	void Save(const std::string& fileName,PlayerData& data);
	void ResourceDataLoad(std::string fileName,ResourceStatusData& data);
};

