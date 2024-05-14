#include "P_CP_MenuUI.h"
#include "P_CP_CollectedItemUI.h"
#include "PickupedItem.h"
#include "../Player_CollectionPart.h"
#include "Play_CollectionPart_BaseUI.h"
#include "../Engine/Systems/ImageSystem.h"
#include "../Engine/Systems/TextSystem.h"
#include "../CloseButton.h"
#include "../Engine/DirectX_11/Input.h"
#include "../InterSceneData.h"
#include "../Engine/newSceneManager.h"
#include "../PlayerData.h"
#include "../ResourceStatusData.h"
#include "../Engine/ResourceManager/AudioManager.h"
#include "../MenuUI_ReturnHome.h"
#include"../Engine/Systems/AudioSystem.h"

P_CP_MenuUI::P_CP_MenuUI(Object* parent)
	:UIBase(parent,"P_CP_MenuUI"),
	isReturnHome_(false),
	returnImageNum_(-1),
	hAudio_Select_(-1),
	time_(0)
{
}

P_CP_MenuUI::~P_CP_MenuUI()
{
}

void P_CP_MenuUI::Initialize()
{
	////家に帰るボタン
	//Image returnHome(this);
	//returnHome.Load("Assets/Image/SelectImage3.png");
	//returnHome.SetPosition({ -1.2f,0.5f,0 });
	//returnHome.SetRotation({ 0,0,180 });
	////returnHome.SetSize({ 5,2,0 });
	//returnImageNum_ = AddComponent<Image>(returnHome);
	//XMFLOAT3 textPos = GetComponent<Image>().GetPositionAtPixel();
	//
	////家に帰るテキスト
	//Text commandText(this);
	//commandText.SetText("家に戻る");
	//commandText.SetPosition({ textPos.x+200,textPos.y-50 });
	//AddComponent<Text>(commandText);

	//画面暗転用の画像
	Image fadeImage(this);
	fadeImage.Load("Assets/Image/PotionManagerUIBase1.png");
	fadeImage.SetColor({ 0,0,0,0 });
	fadeImage.SetLayer(3);
	fadeImage.SetSize({ 2,2,0 });
	AddComponent<Image>(fadeImage);

	Instantiate<MenuUI_ReturnHome>(this);

	//集めた素材のUI
	//P_CP_CollectedItemUI& collectedUI = *Instantiate<P_CP_CollectedItemUI>(this);
	//Player_CollectionPart* player = (Player_CollectionPart*)FindObject("Player_CollectionPart");
	//ResourceStatusData& rData = *InterSceneData::GetData<ResourceStatusData>("ResourceData");
	//
	//for (auto& itr : player->GetItem())
	//{
	//	collectedUI.SetItemData(itr.first,
	//		rData.resourceDataMap_[itr.first].resourceName_,
	//		itr.second,
	//		rData.resourceDataMap_[itr.first].resourceImageName_);
	//}
	//
	//collectedUI.SetDummy();
	//クローズボタン
	GameObject* button = Instantiate<CloseButton>(this);
	button->GetComponent<Image>().SetPosition({ -0.9,0.9,0 });

	Audio audio(this);
	audio.Load("Assets/Audio/Confirm51.wav", false, 1.0f, 1);
	AddComponent<Audio>(audio);
	//hAudio_Select_= AudioManager::Load("Assets/Audio/Confirm51.wav");

}

void P_CP_MenuUI::Start()
{
}

void P_CP_MenuUI::Update()
{

	if (isReturnHome_)
	{
		time_ += 0.016;
		GetComponent<Image>().SetAlpha(time_);
		if(time_>=3.0f)
			newSceneManager::ChangeScene(SCENE_ID::PLAY_MANAGEMENT);
		return;
	}
	////カーゾルが画像に当たってた場合
	//if (GetComponent<Image>(returnImageNum_).IsHitCursor())
	//{
	//	GetComponent<Image>(returnImageNum_).SetPosition({ -1.1,0.5,0 });
	//
	//	if (Input::IsMouseButtonUp(0))
	//	{
	//		AudioManager::Play(hAudio_Select_);
	//		SaveItemData();
	//		FindChild("CloseButton")->KillMe();
	//		isReturnHome_ = true;
	//		//newSceneManager::ChangeScene(SCENE_ID::PLAY_MANAGEMENT);
	//	}
	//
	//}
	//else
	//	GetComponent<Image>(returnImageNum_).SetPosition({ -1.2f,0.5f,0 });

}

void P_CP_MenuUI::SaveItemData()
{
	//保存に必要なデータ類用意
	Player_CollectionPart* player = (Player_CollectionPart*)FindObject("Player_CollectionPart");
	PlayerData* pData = InterSceneData::GetData<PlayerData>("Data01");
	ResourceStatusData* rData = InterSceneData::GetData<ResourceStatusData>("ResourceData");

	//取得したアイテムデータを保存
	for (auto itr = player->GetItem().begin(); itr != player->GetItem().end(); itr++)
	{
		PlayerData::ResourceData_ data;
		int num = itr->first;
		data.itemNum_ = num;
		data.itemName_ = rData->resourceDataMap_[num].resourceName_;
		data.itemImageName_ = rData->resourceDataMap_[num].resourceImageName_;
		data.itemCount_= itr->second;
		pData->AddResourceItemData(data);
	}

}

void P_CP_MenuUI::PlayAudio_Select()
{
	//AudioManager::Play(hAudio_Select_);
}

void P_CP_MenuUI::ReturnHome()
{
	SaveItemData();
	FindChild("CloseButton")->KillMe();
	isReturnHome_ = true;
}

void P_CP_MenuUI::Release()
{
	((Play_CollectionPart_BaseUI*)pParent_)->SetUIOpenFlag(false);
}
