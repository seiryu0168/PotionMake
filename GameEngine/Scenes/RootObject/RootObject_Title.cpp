#include "RootObject_Title.h"
#include"../../Engine/Components/Transform.h"
#include"../../StaticResource.h"
#include"../../Title.h"
#include"../../SaveDataLoader.h"
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
	//{
	//
	//	Image image(0, 3);
	//	image.StaticLoad("Assets/Image/Filter.png");
	//	image.SetSize({ 1920,1080,0 });
	//	image.SetAlpha(0);
	//	image.SetDraw(false);
	//	StaticResource::AddImage("Filter", image);
	//}
	//{
	//	Image image(0, 3);
	//	image.StaticLoad("Assets/Image/Stripe_Red-White.jpg");
	//	image.SetPosition({ 0, 2, 0 });
	//	image.SetDraw(false);
	//	StaticResource::AddImage("GameFinishImage", image);
	//}
	//
	SaveDataLoader loader;
	PlayerData* data = new PlayerData;
	loader.Init();
	loader.Load("Assets/SaveData/PlayerData01",*data);
	PlayerData* pData = new PlayerData;
	//pData->dataName_ = "Data01";
	//pData->name_ = data.name_;
	//pData->potionDataFileName_ = data.potionDataFileName_;
	//pData->resourceFileName_ = data.resourceFileName_;
	//pData->itemDataList_ = data.itemData_;
	data->dataName_ = "Data01";
	InterSceneData::AddData_NonOverWrite(data);
	////PlayerData* pd = InterSceneData::GetData<PlayerData>("Data01");
	////InterSceneData::DeleteData("Data01");
	Instantiate<Title>(this);
}

void RootObject_Title::Release()
{
}
