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

class SaveDataLoader
{
	nlohmann::json jsonFile_;

	std::string utf8_to_SJis(std::string const& str);
	//std::u8string wide_to_utf8(std::wstring const& wstr);

public:
	SaveDataLoader();
	~SaveDataLoader();
	void Init();
	void Load(std::string fileName,PlayerData& data);
	void ResourceDataLoad(std::string fileName,ResourceStatusData& data);
};

