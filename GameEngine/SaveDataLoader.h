#pragma once
#include"Engine/ResourceManager/json.hpp"
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
public:
	SaveDataLoader();
	~SaveDataLoader();
	void Init();
	void Load(std::string fileName,PlayerData_Test::SaveData& data);
};

