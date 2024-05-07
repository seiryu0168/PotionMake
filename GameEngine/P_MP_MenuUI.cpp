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
#include"Engine/ResourceManager/Audio.h"

P_MP_MenuUI::P_MP_MenuUI(Object* parent)
	:GameObject(parent,"P_MP_MenuUI")
{
}

P_MP_MenuUI::~P_MP_MenuUI()
{
}

void P_MP_MenuUI::Initialize()
{
	Image returnHome(this);
	returnHome.Load("Assets/Image/SelectImage3.png");
	returnHome.SetPosition({ -1.2f,0.5f,0 });
	returnHome.SetRotation({ 0,0,180 });
	//returnHome.SetSize({ 5,2,0 });
	returnImageNum_ = AddComponent<Image>(returnHome);
	XMFLOAT3 textPos = returnHome.GetPositionAtPixel();
	Text commandText(this);
	commandText.SetText("セーブ");
	commandText.SetPosition({ textPos.x + 200,textPos.y - 50 });
	AddComponent<Text>(commandText);

	//Image saveImage(this);
	//saveImage.Load("Assets/Image/SelectImage3.png");
	//saveImage.SetPosition({ -1.2f,0.3f,0 });
	//saveImage.SetRotation({ 0,0,180 });
	//saveImageNum_ = AddComponent<Image>(saveImage);
	//textPos = saveImage.GetPositionAtPixel();
	//Text saveText(this);
	//saveText.SetText("セーブ");
	//saveText.SetPosition({ textPos.x + 200,textPos.y - 50 });
	//AddComponent<Text>(saveText);

	Instantiate<P_MP_NewsPaper>(this);
	

	GameObject* button = Instantiate<CloseButton>(this);
	button->GetComponent<Image>().SetPosition({ -0.9,0.9,0 });

	hAudio_Confirm_ = Audio::Load("Assets/Audio/Confirm51.wav");
}

void P_MP_MenuUI::Start()
{
}

void P_MP_MenuUI::Update()
{
	if (GetComponent<Image>(returnImageNum_).IsHitCursor())
	{
		GetComponent<Image>(returnImageNum_).SetPosition({ -1.1,0.5,0 });

		if (Input::IsMouseButtonUp(0))
		{
			Audio::Play(hAudio_Confirm_);
			DataSave();
		}

	}
	else
		GetComponent<Image>(returnImageNum_).SetPosition({ -1.2f,0.5f,0 });
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
