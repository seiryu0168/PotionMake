#include "SaveDataManager.h"
#include<Windows.h>
#include<fstream>
#include"Engine/ResourceManager/CsvReader.h"
std::string SaveDataManager::utf8_to_SJis(std::string const& str)
{
	//ワイド文字列に変換(utf8->unicode)
	int unicodeLength = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.size() + 1, NULL, 0);
	wchar_t* buffUnicode = new wchar_t[unicodeLength];
	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.size() + 1, buffUnicode, unicodeLength);

	//マルチバイト文字列に変換(unicode->ShiftJIS)
	int sjisLength = WideCharToMultiByte(CP_THREAD_ACP, 0, buffUnicode, -1, NULL, 0, NULL, NULL);
	char* buffSjis = new char[sjisLength];
	WideCharToMultiByte(CP_THREAD_ACP, 0, buffUnicode, unicodeLength + 1, buffSjis, sjisLength, NULL, NULL);
	std::string strJis(buffSjis);
	delete[] buffUnicode;
	delete[] buffSjis;
	return strJis;

}

std::u8string SaveDataManager::SJis_to_utf8(std::string const& str)
{
	//ワイド文字列に変換(ShiftJIS->unicode)
	int unicodeLength = MultiByteToWideChar(CP_THREAD_ACP, 0, str.c_str(), str.size() + 1, NULL, 0);
	wchar_t* buffUnicode = new wchar_t[unicodeLength];
	MultiByteToWideChar(CP_THREAD_ACP, 0, str.c_str(), str.size() + 1, buffUnicode, unicodeLength);

	//マルチバイト文字列に変換(unicode->utf8)
	int utf8Length = WideCharToMultiByte(CP_UTF8, 0, buffUnicode, -1, NULL, 0, NULL, NULL);
	char8_t* buffutf8 = new char8_t[utf8Length];
	WideCharToMultiByte(CP_UTF8, 0, buffUnicode, unicodeLength + 1, (LPSTR)buffutf8, utf8Length, NULL, NULL);
	std::u8string strJis(buffutf8);
	delete[] buffUnicode;
	delete[] buffutf8;
	return strJis;
}

SaveDataManager::SaveDataManager()
{
}

SaveDataManager::~SaveDataManager()
{
}

void SaveDataManager::Init()
{
	nlohmann::json playerFile;
	playerFile["Name"] = "player01";
	playerFile["NewsPaperNumber"] = 0;
	playerFile["ResourceFileName"] = "Assets/SaveData/ResourceFile01";
	playerFile["PotionDataFileName"] = "Assets/SaveData/PotionDataFile01";
	
	playerFile["ItemList"] = { {0,u8"パワーフラワー","ResourceImage01.png",999},
							   {1,u8"魔力草","ResourceImage02.png",999},
							   {2,u8"ラッキーキノコ","ResourceImage04.png",999},
							   {3,u8"ハーヤ草","ResourceImage03.png",999} };
	
	playerFile["PotionList"] = { {u8"筋・運・魔のポーション Lv.2",
								  2,	
								  true,
								  17,
								  300,
								  2.3f,1.1f,1.5f,0.6f,2.1f,
								  0.3f,0.3f,0.3f},
								 {u8"防のポーション Lv.2",
								  2,
								  true,
								  2,
								  300,
								  1.6f,2.1f,1.2f,1.6f,1.3f,
								  0.3f,0.3f,0.3f},
								 {u8"万能ポーション Lv.2\n筋・防・魔・運",
								  2,
								  true,
								  23,
								  300,
								  2.1f,2.9f,2.5f,1.3f,2.0f,
								  0.3f,0.3f,0.3f} };

	playerFile["GainList"] = { 100,300,500,200,600 };
	
	std::ofstream of("Assets/SaveData/PlayerData01.json",std::ios::out);
	of << playerFile << std::endl;
	//
	//nlohmann::json resourceStatusFile;
	//resourceStatusFile["StatusColor"] = { {238.0f / 255.0f,131.0f / 255.0f,111.0f / 255.0f},//柔らかい赤系の色
	//									  {193.0f / 255.0f,237.0f / 255.0f,111.0f / 255.0f},//柔らかい黄緑系の色
	//									  {111.0f / 255.0f,237.0f / 255.0f,181.0f / 255.0f},//柔らかい緑系の色
	//									  {111.0f / 255.0f,143.0f / 255.0f,237.0f / 255.0f},//柔らかい青紫系の色
	//									  {231.0f / 255.0f,111.0f / 255.0f,237.0f / 255.0f}//柔らかい紫系の色 
	//									};
	//resourceStatusFile["StatusList"] ={ {0,"Item01","ResourceImage01.png",0.2f,0.1f,0.3f,0.2f,0.4f},
	//								    {1,"Item02","ResourceImage02.png",0.5f,0.2f,0.1f,0.1f,0.3f},
	//								    {2,"Item02","ResourceImage03.png",0.1f,0.6f,0.1f,0.1f,0.1f} };
	//resourceStatusFile["ProcessList"] = { {0,u8"切り刻む","ProcessImage_Chop.png",1.1f,1.2f,0.7f,0.8f,1.3f},
	//									  {1,u8"茹でる","ProcessImage_Boil.png",0.7f,1.7f,1.0f,1.1f,1.2f},
	//									  {2,u8"すりつぶす","ProcessImage_Grind.png",1.3f,0.5f,1.4f,1.2f,0.8f}};
	//
	//std::ofstream rof("Assets/SaveData/ResourceData.json", std::ios::out);
	//rof << resourceStatusFile << std::endl;

}

void SaveDataManager::Load(std::string fileName, PlayerData& data)
{
	nlohmann::json playerFile;
	std::ifstream ifs(fileName+".json", std::ios::in);
	if (!ifs.good()) return;

	playerFile = nlohmann::json::parse(ifs);
	//PlayerData::SaveData data;
	data.name_ = playerFile["Name"];
	data.newsPaperNumber_ = playerFile["NewsPaperNumber"];
	data.potionDataFileName_ = playerFile["PotionDataFileName"];
	data.resourceFileName_ = playerFile["ResourceFileName"];

	for (auto itr = playerFile["ItemList"].begin(); itr != playerFile["ItemList"].end(); itr++)
	{
		std::u8string str = itr.value().at(1);
		std::string processNameUtf8 = (const char*)str.c_str();
		//std::string itemImageName = itr.value().at(2);
		//int itemCount             = itr.value().at(3).get<int>();
		
		PlayerData::ResourceData_ rData;
		rData.itemNum_		 = itr.value().at(0);
		rData.itemName_      = utf8_to_SJis(processNameUtf8);
		rData.itemImageName_ = itr.value().at(2);
		rData.itemCount_	 = itr.value().at(3).get<int>();

		data.itemDataList_.push_back(rData);
	}
	for (auto itr = playerFile["PotionList"].begin();itr!=playerFile["PotionList"].end();itr++)
	{
		PlayerData::PotionData pData;
		std::u8string str = itr.value().at(0);
		std::string processNameUtf8 = (const char*)str.c_str();
		pData.potionName_	   = utf8_to_SJis(processNameUtf8);
		pData.tier_			   = itr.value().at(1);
		pData.isSale_		   = itr.value().at(2);
		pData.topStatus_	   = itr.value().at(3);
		pData.price_		   = itr.value().at(4);
		pData.potionStatus_[0] = itr.value().at(5);
		pData.potionStatus_[1] = itr.value().at(6);
		pData.potionStatus_[2] = itr.value().at(7);
		pData.potionStatus_[3] = itr.value().at(8);
		pData.potionStatus_[4] = itr.value().at(9);
		pData.potionColor_.x   = itr.value().at(10);
		pData.potionColor_.y   = itr.value().at(11);
		pData.potionColor_.z   = itr.value().at(12);

		data.potionDataList_.push_back(pData);
	}

	for (auto itr = playerFile["GainList"].begin(); itr != playerFile["GainList"].end(); itr++)
	{
		data.gainList_.push_back(itr.value());
	}
}

void SaveDataManager::Save(const std::string& fileName, PlayerData& data)
{
	nlohmann::json playerFile;
	playerFile["Name"] = data.name_;
	playerFile["NewsPaperNumber"] = data.newsPaperNumber_;
	playerFile["ResourceFileName"] = data.resourceFileName_;	// "Assets/SaveData/ResourceFile01";
	playerFile["PotionDataFileName"] = data.potionDataFileName_;//"Assets/SaveData/PotionDataFile01";

	playerFile["ItemList"];

	for (int i = 0; i < data.itemDataList_.size(); i++)
	{

		playerFile["ItemList"] += {data.itemDataList_[i].itemNum_,
			SJis_to_utf8(data.itemDataList_[i].itemName_),
			data.itemDataList_[i].itemImageName_,
			data.itemDataList_[i].itemCount_};
	}

	playerFile["PotionList"];
	for (int i = 0; i < data.potionDataList_.size(); i++)
	{
		playerFile["PotionList"] += {SJis_to_utf8(data.potionDataList_[i].potionName_),
									 data.potionDataList_[i].tier_,
									 data.potionDataList_[i].isSale_,
									 data.potionDataList_[i].topStatus_,
									 data.potionDataList_[i].price_,
									 data.potionDataList_[i].potionStatus_[0],
									 data.potionDataList_[i].potionStatus_[1],
									 data.potionDataList_[i].potionStatus_[2],
									 data.potionDataList_[i].potionStatus_[3],
									 data.potionDataList_[i].potionStatus_[4],
									 data.potionDataList_[i].potionColor_.x,
									 data.potionDataList_[i].potionColor_.y,
									 data.potionDataList_[i].potionColor_.z, };
	}

	playerFile["GainList"] = data.gainList_;

	std::ofstream of("Assets/SaveData/PlayerData01.json", std::ios::out);
	of << playerFile << std::endl;
}

void SaveDataManager::ResourceDataLoad(std::string fileName, ResourceStatusData& data)
{
	nlohmann::json resourceStatusFile;
	std::ifstream ifs(fileName + ".json", std::ios::in);
	if (!ifs.good()) return;

	resourceStatusFile = nlohmann::json::parse(ifs);
	CsvReader reader("Assets/SaveData/GameData/ModelNameList.csv");
	for (auto itr = resourceStatusFile["StatusColor"].begin(); itr != resourceStatusFile["StatusColor"].end(); itr++)
	{
		data.statusColor_.push_back({ itr.value().at(0),itr.value().at(1),itr.value().at(2) });
	}
	for (int i=0;i<reader.GetLines();i++)
	{
		ResourceStatusData::ResourceStatus statusData;


		statusData.resourceNumber_		= reader.GetInt(i,0);
		statusData.resourceImageName_   = reader.GetString(i,1);
		statusData.resourceModelName_   = reader.GetString(i, 2);
		statusData.resourceName_		= utf8_to_SJis(reader.GetString(i,3));
		statusData.status00_			= reader.GetFloat(i,4);
		statusData.status01_			= reader.GetFloat(i,5);
		statusData.status02_			= reader.GetFloat(i,6);
		statusData.status03_			= reader.GetFloat(i,7);
		statusData.status04_			= reader.GetFloat(i,8);
		statusData.explanation_			= utf8_to_SJis(reader.GetString(i,9));
		data.resourceDataMap_.insert({ statusData.resourceNumber_,statusData });
	}

	for (auto itr = resourceStatusFile["ProcessList"].begin(); itr != resourceStatusFile["ProcessList"].end(); itr++)
	{
		ResourceStatusData::ResourceStatus statusData;

		std::u8string str=itr.value().at(1);
		std::string processNameUtf8= (const char*)str.c_str();

		statusData.resourceNumber_	  = itr.value().at(0);
		statusData.resourceName_	  = utf8_to_SJis(processNameUtf8);
		statusData.resourceImageName_ = itr.value().at(2);
		statusData.status00_		  = itr.value().at(3);
		statusData.status01_		  = itr.value().at(4);
		statusData.status02_		  = itr.value().at(5);
		statusData.status03_		  = itr.value().at(6);
		statusData.status04_		  = itr.value().at(7);
		data.processDataMap_.insert({ statusData.resourceNumber_,statusData });
	}

	reader.Load("Assets/SaveData/GameData/NewsPaperData.csv");

	for (int i = 0; i < reader.GetLines(); i++)
	{
		ResourceStatusData::ResourceStatus statusData;

		statusData.resourceNumber_ = reader.GetInt(i,0);
		statusData.resourceName_ = reader.GetString(i, 1);
		statusData.resourceImageName_ = reader.GetString(i, 2);
		statusData.status00_ = reader.GetFloat(i, 3);
		statusData.status01_ = reader.GetFloat(i, 4);
		statusData.status02_ = reader.GetFloat(i, 5);
		statusData.status03_ = reader.GetFloat(i, 6);
		statusData.status04_ = reader.GetFloat(i, 7);

		data.newsPaperList_.push_back(statusData);
	}

}
