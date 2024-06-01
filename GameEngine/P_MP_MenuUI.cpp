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

	GameObject* button = Instantiate<CloseButton>(this);
	button->GetComponent<Image>().SetPosition({ -0.9,0.9,0 });

	Audio audio(this);
	audio.Load("Assets/Audio/Confirm51.wav", false, 1.0f, 5);
	AddComponent<Audio>(audio);
	//hAudio_Confirm_ = AudioManager::Load("Assets/Audio/Confirm51.wav");
}

void P_MP_MenuUI::Start()
{
}

void P_MP_MenuUI::Update()
{
}

void P_MP_MenuUI::DataSave()
{
	SaveDataManager mng;

	mng.Save("", *InterSceneData::GetData<PlayerData>("Data01"));
}

void P_MP_MenuUI::Release()
{
	//Direct3D::ShowMouseCursor(false);
	//XMINT2 rectPos = { (int)(Direct3D::GetScreenWidth() * 0.5f),(int)(Direct3D::GetScreenHeight() * 0.5f) };
	//Direct3D::SetClipCursor({ rectPos.x,rectPos.y,rectPos.x + 1,rectPos.y + 1 });
	((Play_ManagementPart_BaseUI*)pParent_)->SetAccessUIFlag(false);
	((Play_ManagementPart_BaseUI*)pParent_)->SetUIOpenFlag(false);
}
