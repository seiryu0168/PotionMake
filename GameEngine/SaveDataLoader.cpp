#include "SaveDataLoader.h"
#include<fstream>

SaveDataLoader::SaveDataLoader()
{
}

SaveDataLoader::~SaveDataLoader()
{
}

void SaveDataLoader::Init()
{
	nlohmann::json playerFile;
	playerFile["Name"] = "player01";
	playerFile["ResourceFileName"] = "Assets/SaveData/ResourceFile01";
	playerFile["PotionDataFileName"] = "Assets/SaveData/PotionDataFile01";
	playerFile["ItemList"] = { {"Item01",10},{"Item02",5},{"Item03",7} };

	std::ofstream of("Assets/SaveData/PlayerData01.json",std::ios::out);
	of << playerFile << std::endl;

}

void SaveDataLoader::Load(std::string fileName, PlayerData_Test::SaveData& data)
{
	nlohmann::json playerFile;
	std::ifstream ifs(fileName+".json", std::ios::in);
	if (!ifs.good()) return;

	playerFile = nlohmann::json::parse(ifs);
	//PlayerData::SaveData data;
	data.name_ = playerFile["Name"];
	data.potionDataFileName_ = playerFile["PotionDataFileName"];
	data.resourceFileName_ = playerFile["ResourceFileName"];

	for (auto itr = playerFile["ItemList"].begin(); itr != playerFile["ItemList"].end(); itr++)
	{
		std::string itemName = itr.key();
		int itemCount = itr.value().get<int>();
		data.itemData_.push_back({itemName,itemCount});
	}
}
