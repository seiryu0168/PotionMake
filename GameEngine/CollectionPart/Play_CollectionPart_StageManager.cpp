#include "Play_CollectionPart_StageManager.h"
#include "P_CP_ResourceItem.h"
#include <Windows.h>
#include "../Engine/ResourceManager/CsvReader.h"
#include "../ResourceStatusData.h"
#include "../InterSceneData.h"
#include "../Engine/Systems/ColliderSystem.h"
#include"../Engine/GameObject/CameraManager.h"
Play_CollectionPart_StageManager::Play_CollectionPart_StageManager(Object* parent)
	:GameObject(parent,"Play_CollectionPart_StageManager")
{
}

Play_CollectionPart_StageManager::~Play_CollectionPart_StageManager()
{
}

void Play_CollectionPart_StageManager::Initialize()
{
	CsvReader reader("Assets/SaveData/GameData/CollectionPartItemData04.csv");

	//CSVをもとに素材を生成
	for (int i = 0; i < reader.GetLines(); i++)
	{
		P_CP_ResourceItem* item = Instantiate<P_CP_ResourceItem>(this);
		item->SetNumber(reader.GetInt(i, 0));
		item->itemName_ = ConvertItemName(reader.GetString(i, 1));
		item->SetModel(reader.GetString(i, 2));
		item->GetTransform()->position_ = XMVectorSet(reader.GetFloat(i, 3), reader.GetFloat(i, 4), reader.GetFloat(i, 5), 0);
		item->GetTransform()->RotateEular(reader.GetFloat(i, 6), reader.GetFloat(i, 7), reader.GetFloat(i, 8));
		item->GetComponent<Collider>().GetCollisionShape<HitBox>().size_ = { reader.GetFloat(i,9),reader.GetFloat(i,10), reader.GetFloat(i,11) };
	}
}

void Play_CollectionPart_StageManager::Update()
{
}

std::vector<std::string> Play_CollectionPart_StageManager::GetItemNameList()
{
	std::vector <std::string> itemNameList;
	ResourceStatusData* rData = InterSceneData::GetData<ResourceStatusData>("ResourceData");
	//素材名の保存
	for (int i = 0; i < rData->resourceDataMap_.size(); i++)
	{
		itemNameList.push_back(rData->resourceDataMap_[i].resourceName_);
	}
	return itemNameList;
}

std::string Play_CollectionPart_StageManager::ConvertItemName(const std::string& str)
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

void Play_CollectionPart_StageManager::Release()
{
}
