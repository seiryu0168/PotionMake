#include "RootObject_Title.h"
#include"../../Engine/Components/Transform.h"
#include"../../StaticResource.h"
#include"../../Title.h"
#include"../../SaveDataManager.h"
#include"../../InterSceneData.h"
#include"../../PlayerData.h"
//#include"../../TestObject.h"
//#include"../../SelectUI.h"
//#include"../../Title.h"
RootObject_Title::RootObject_Title()
{
	//Transform transform;
	//AddComponent<Transform>(transform);
}

RootObject_Title::~RootObject_Title()
{
}

void RootObject_Title::Initialize()
{
	SaveDataManager loader;
	PlayerData* data = new PlayerData;
	loader.Init();
	loader.Load("Assets/SaveData/PlayerData01",*data);

	ResourceStatusData* rData = new ResourceStatusData;
	loader.ResourceDataLoad("Assets/SaveData/GameData/ResourceData",*rData);
	rData->dataName_ = "ResourceData";
	data->dataName_ = "Data01";
	InterSceneData::AddData_NonOverWrite(rData);
	InterSceneData::AddData_NonOverWrite(data);


	//PlayerData& playerData = *InterSceneData::GetData<PlayerData>("Data01");
	//loader.Save("", playerData);

	Instantiate<Title>(this);
}

void RootObject_Title::Release()
{
}
