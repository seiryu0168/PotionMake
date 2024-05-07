#include "P_MP_NewsPaper.h"
#include "Engine/Systems//ImageSystem.h"
#include "InterSceneData.h"
#include "PlayerData.h"
#include "ResourceStatusData.h"
#include "CloseButton.h"
P_MP_NewsPaper::P_MP_NewsPaper(Object* parent)
	:GameObject(parent,"P_MP_NewsPaper")
{
}

P_MP_NewsPaper::~P_MP_NewsPaper()
{
}

void P_MP_NewsPaper::Initialize()
{
	int num = InterSceneData::GetData<PlayerData>("Data01")->newsPaperNumber_;
	std::string imageName = InterSceneData::GetData<ResourceStatusData>("ResourceData")->newsPaperList_[num].resourceImageName_;
	Image newsPaperImage(this);
	newsPaperImage.Load("Assets/Image/" + imageName);
	newsPaperImage.SetPosition({ 0.4f,0,0 });
	AddComponent<Image>(newsPaperImage);

	//XMFLOAT3 imagePos = newsPaperImage.GetPosition();
	//Instantiate<CloseButton>(this)->GetComponent<Image>().SetPosition({ imagePos.x - 0.3f,imagePos.y + 0.6f,0 });
}

void P_MP_NewsPaper::Start()
{
}

void P_MP_NewsPaper::Update()
{
}

void P_MP_NewsPaper::Release()
{
}
