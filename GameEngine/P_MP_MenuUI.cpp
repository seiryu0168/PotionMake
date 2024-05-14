#include "P_MP_MenuUI.h"
#include"Engine/Systems/ImageSystem.h"
#include"Engine/Systems/TextSystem.h"
#include"Engine/DirectX_11/Input.h"
#include"InterSceneData.h"
#include"Engine/newSceneManager.h"
#include"ManagementPart/Play_ManagementPart_BaseUI.h"
#include"PlayerData.h"
#include"P_MP_NewsPaper.h"
#include"CloseButton.h"
#include"SaveDataManager.h"
#include"CollectionPart/P_CP_CollectedItemUI.h"
#include"ResourceStatusData.h"
#include"Engine/ResourceManager/AudioManager.h"
#include"MenuUI_Save.h"
#include"MenuUI_NewsPaper.h"
#include"Engine/Systems/AudioSystem.h"
#include"MenuUI_Status.h"
#include"MenuUI_Item.h"
#include"MenuUI.h"

P_MP_MenuUI::P_MP_MenuUI(Object* parent)
	:UIBase(parent,"P_MP_MenuUI")
{
}

P_MP_MenuUI::~P_MP_MenuUI()
{
}

void P_MP_MenuUI::Initialize()
{
	//Image save(this);
	//save.Load("Assets/Image/SelectImage3.png");
	//save.SetPosition({ -1.2f,0.5f,0 });
	//save.SetRotation({ 0,0,180 });
	////save.SetSize({ 5,2,0 });
	//saveImageNum_ = AddComponent<Image>(save);
	//XMFLOAT3 textPos = save.GetPositionAtPixel();
	//Text commandText(this);
	//commandText.SetText("セーブ");
	//commandText.SetPosition({ textPos.x + 200,textPos.y - 50 });
	//AddComponent<Text>(commandText);
	MenuUI& status = *Instantiate<MenuUI_Status>(this);
	status.SetButton("Assets/Image/SelectImage3.png", "ステータス", { -1.2f,0.5f,0 });
	status.SetUINumber(0);

	MenuUI& item = *Instantiate<MenuUI_Item>(this);
	item.SetButton("Assets/Image/SelectImage3.png", "素材", { -1.2f,0.25f,0 });
	item.SetUINumber(1);

	MenuUI& newsPaper = *Instantiate<MenuUI_NewsPaper>(this);
	newsPaper.SetButton("Assets/Image/SelectImage3.png", "新聞", { -1.2f,0.0f,0 });
	newsPaper.SetUINumber(2);

	MenuUI& save = *Instantiate<MenuUI_Save>(this);
	save.SetButton("Assets/Image/SelectImage3.png", "セーブ", { -1.2f,-0.25f,0 });
	save.SetUINumber(3);
	//Image itemImage(this);
	//itemImage.Load("Assets/Image/SelectImage3.png");
	//itemImage.SetPosition({ -1.2f,0.2f,0 });
	//itemImage.SetRotation({ 0,0,180 });
	//returnImageNum_ = AddComponent<Image>(itemImage);
	//
	//XMFLOAT3 textPos = itemImage.GetPositionAtPixel();
	//
	//Text saveText(this);
	//saveText.SetText("素材");
	//saveText.SetPosition({ textPos.x + 200,textPos.y - 50 });
	//AddComponent<Text>(saveText);
	//
	//Instantiate<P_MP_NewsPaper>(this);
	//
	//
	GameObject* button = Instantiate<CloseButton>(this);
	button->GetComponent<Image>().SetPosition({ -0.9,0.9,0 });

	Audio audio(this);
	audio.Load("Assets/Audio/Confirm51.wav", false, 1.0f, 1);
	AddComponent<Audio>(audio);
	//hAudio_Confirm_ = AudioManager::Load("Assets/Audio/Confirm51.wav");
}

void P_MP_MenuUI::Start()
{
}

void P_MP_MenuUI::Update()
{
	//if (GetComponent<Image>(saveImageNum_).IsHitCursor())
	//{
	//	GetComponent<Image>(saveImageNum_).SetPosition({ -1.1,0.5,0 });
	//
	//	if (Input::IsMouseButtonUp(0))
	//	{
	//		AudioManager::Play(hAudio_Confirm_);
	//		DataSave();
	//	}
	//
	//}
	//else
	//	GetComponent<Image>(saveImageNum_).SetPosition({ -1.2f,0.5f,0 });

	//if (GetComponent<Image>(returnImageNum_).IsHitCursor())
	//{
	//	GetComponent<Image>(returnImageNum_).SetPosition({ -1.1f,0.2f,0 });
	//
	//	if (Input::IsMouseButtonUp(0) && !GetOpenUIFlag())
	//	{
	//		SetOpenUIFlag(true);
	//		AudioManager::Play(hAudio_Confirm_);
	//
	//		P_CP_CollectedItemUI& collectedUI = *Instantiate<P_CP_CollectedItemUI>(this);
	//		ResourceStatusData& rData = *InterSceneData::GetData<ResourceStatusData>("ResourceData");
	//		//PlayerData::ResourceData_ prData = InterSceneData::GetData<PlayerData>("Data01")->itemDataList_;
	//		for (auto& itr : InterSceneData::GetData<PlayerData>("Data01")->itemDataList_)
	//		{
	//			collectedUI.SetItemData(itr.itemNum_,
	//				rData.resourceDataMap_[itr.itemNum_].resourceName_,
	//				itr.itemCount_,
	//				rData.resourceDataMap_[itr.itemNum_].resourceImageName_);
	//		}
	//
	//		collectedUI.SetDummy();
	//	}
	//
	//}
	//else
	//	GetComponent<Image>(returnImageNum_).SetPosition({ -1.2f,0.2f,0 });
}

void P_MP_MenuUI::DataSave()
{
	SaveDataManager mng;

	mng.Save("", *InterSceneData::GetData<PlayerData>("Data01"));
}

void P_MP_MenuUI::Release()
{
	Direct3D::ShowMouseCursor(false);
	XMINT2 rectPos = { (int)(Direct3D::GetScreenWidth() * 0.5f),(int)(Direct3D::GetScreenHeight() * 0.5f) };
	Direct3D::SetClipCursor({ rectPos.x,rectPos.y,rectPos.x + 1,rectPos.y + 1 });
	((Play_ManagementPart_BaseUI*)pParent_)->SetAccessUIFlag(false);
}
