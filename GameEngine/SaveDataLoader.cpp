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

	playerFile["ItemList"] = { {0,"Item01","ResourceImage01.png",10},
							   {1,"Item02","ResourceImage02.png",5},
							   {2,"Item03","ResourceImage03.png",7}};

	playerFile["PotionList"] = { {"Potion01",false,2.3f,1.1f,1.5f,0.6f,2.1f},
								 {"Potion02",false,1.6f,2.1f,1.2f,1.6f,1.3f},
								 {"Potion03",false,2.1f,2.9f,2.5f,1.3f,2.0f} };

	//playerFile["SellPotionList"] = { {"",0,0,0,0,0},
	//								 {"",0,0,0,0,0},
	//								 {"",0,0,0,0,0},
	//								 {"",0,0,0,0,0},
	//								 {"",0,0,0,0,0} };
	std::ofstream of("Assets/SaveData/PlayerData01.json",std::ios::out);
	of << playerFile << std::endl;

	nlohmann::json resourceStatusFile;
	resourceStatusFile["StatusColor"] = { {238.0f / 255.0f,131.0f / 255.0f,111.0f / 255.0f},//_‚ç‚©‚¢ÔŒn‚ÌF
										  {193.0f / 255.0f,237.0f / 255.0f,111.0f / 255.0f},//_‚ç‚©‚¢‰©—ÎŒn‚ÌF
										  {111.0f / 255.0f,237.0f / 255.0f,181.0f / 255.0f},//_‚ç‚©‚¢—ÎŒn‚ÌF
										  {111.0f / 255.0f,143.0f / 255.0f,237.0f / 255.0f},//_‚ç‚©‚¢ÂŽ‡Œn‚ÌF
										  {231.0f / 255.0f,111.0f / 255.0f,237.0f / 255.0f}//_‚ç‚©‚¢Ž‡Œn‚ÌF 
										};

	resourceStatusFile["StatusList"] ={ {0,"Item01","ResourceImage01.png",0.2f,0.1f,0.3f,0.2f,0.4f},
									    {1,"Item02","ResourceImage02.png",0.5f,0.2f,0.1f,0.1f,0.3f},
									    {2,"Item02","ResourceImage03.png",0.1f,0.6f,0.1f,0.1f,0.1f} };
	resourceStatusFile["ProcessList"] = { {0,1.1f,1.2f,0.7f,0.8f,1.3f},
										  {1,0.7f,1.7f,1.0f,1.1f,1.2f},
										  {2,1.3f,0.5f,1.4f,1.2f,0.8f} };

	std::ofstream rof("Assets/SaveData/ResourceData.json", std::ios::out);
	rof << resourceStatusFile << std::endl;

}

void SaveDataLoader::Load(std::string fileName, PlayerData& data)
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
		//std::string itemName      = itr.value().at(1);
		//std::string itemImageName = itr.value().at(2);
		//int itemCount             = itr.value().at(3).get<int>();
		
		PlayerData::ResourceData_ rData;
		rData.itemNum_		 = itr.value().at(0);
		rData.itemName_      = itr.value().at(1);
		rData.itemImageName_ = itr.value().at(2);
		rData.itemCount_	 = itr.value().at(3).get<int>();

		data.itemDataList_.push_back(rData);
	}
	for (auto itr = playerFile["PotionList"].begin();itr!=playerFile["PotionList"].end();itr++)
	{
		PlayerData::PotionData pData;
		pData.potionName_	   = itr.value().at(0);
		pData.isSale_		   = itr.value().at(1);
		pData.potionStatus_[0] = itr.value().at(2);
		pData.potionStatus_[1] = itr.value().at(3);
		pData.potionStatus_[2] = itr.value().at(4);
		pData.potionStatus_[3] = itr.value().at(5);
		pData.potionStatus_[4] = itr.value().at(6);
		data.potionDataList_.push_back(pData);
	}
}

void SaveDataLoader::ResourceDataLoad(std::string fileName, ResourceStatusData& data)
{
	nlohmann::json resourceStatusFile;
	std::ifstream ifs(fileName + ".json", std::ios::in);
	if (!ifs.good()) return;

	resourceStatusFile = nlohmann::json::parse(ifs);

	for (auto itr = resourceStatusFile["StatusColor"].begin(); itr != resourceStatusFile["StatusColor"].end(); itr++)
	{
		data.statusColor_.push_back({ itr.value().at(0),itr.value().at(1),itr.value().at(2) });
	}
	for (auto itr = resourceStatusFile["StatusList"].begin(); itr != resourceStatusFile["StatusList"].end(); itr++)
	{
		ResourceStatusData::ResourceStatus statusData;

		statusData.resourceNumber_		= itr.value().at(0);
		statusData.resourceName_		= itr.value().at(1);
		statusData.resourceImageName_   = itr.value().at(2);
		statusData.status00_			= itr.value().at(3);
		statusData.status01_			= itr.value().at(4);
		statusData.status02_			= itr.value().at(5);
		statusData.status03_			= itr.value().at(6);
		statusData.status04_			= itr.value().at(7);
		data.resourceDataMap_.insert({ statusData.resourceNumber_,statusData });
	}

	for (auto itr = resourceStatusFile["ProcessList"].begin(); itr != resourceStatusFile["ProcessList"].end(); itr++)
	{
		ResourceStatusData::ResourceStatus statusData;

		statusData.resourceNumber_ = itr.value().at(0);
		statusData.status00_	   = itr.value().at(1);
		statusData.status01_	   = itr.value().at(2);
		statusData.status02_	   = itr.value().at(3);
		statusData.status03_	   = itr.value().at(4);
		statusData.status04_	   = itr.value().at(5);
		data.processDataMap_.insert({ statusData.resourceNumber_,statusData });
	}

}
