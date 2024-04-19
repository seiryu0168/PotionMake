#include "Play_CollectionPart_StageManager.h"
#include"Engine/ResourceManager/CsvReader.h"
#include"P_CP_ResourceItem.h"
Play_CollectionPart_StageManager::Play_CollectionPart_StageManager(Object* parent)
	:GameObject(parent,"Play_CollectionPart_StageManager")
{
}

Play_CollectionPart_StageManager::~Play_CollectionPart_StageManager()
{
}

void Play_CollectionPart_StageManager::Initialize()
{
	CsvReader reader("Assets/SaveData/CollectionPartItemData.csv");

	for (int i = 0; i < reader.GetLines(); i++)
	{
		P_CP_ResourceItem* item = Instantiate<P_CP_ResourceItem>(this);
		item->SetNumber(reader.GetInt(i, 0));
		item->SetModel(reader.GetString(i, 1));
		item->GetTransform()->position_ = XMVectorSet(reader.GetFloat(i, 2), reader.GetFloat(i, 3), reader.GetFloat(i, 4), 0);
		item->GetTransform()->RotateEular(reader.GetFloat(i, 5), reader.GetFloat(i, 6), reader.GetFloat(i, 7));
	}
}

void Play_CollectionPart_StageManager::Update()
{
}

void Play_CollectionPart_StageManager::Release()
{
}
