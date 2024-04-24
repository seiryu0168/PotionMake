#include "P_MP_MenuUI.h"
#include"Engine/Systems/ImageSystem.h"
#include"Engine/Systems/TextSystem.h"
#include"Engine/DirectX_11/Input.h"
#include"InterSceneData.h"
#include"Engine/newSceneManager.h"
#include"Play_ManagementPart_BaseUI.h"
#include"PlayerData.h"
#include"CloseButton.h"

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
	XMFLOAT3 textPos = GetComponent<Image>().GetPositionAtPixel();
	Text commandText(this);
	commandText.SetText("‰Æ‚É–ß‚é");
	commandText.SetPosition({ textPos.x + 200,textPos.y - 50 });
	AddComponent<Text>(commandText);

	GameObject* button = Instantiate<CloseButton>(this);
	button->GetComponent<Image>().SetPosition({ -0.9,0.9,0 });
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
			//SaveItemData();
			//newSceneManager::ChangeScene(SCENE_ID::PLAY_MANAGEMENT);
		}

	}
	else
		GetComponent<Image>(returnImageNum_).SetPosition({ -1.2f,0.5f,0 });
}

void P_MP_MenuUI::Release()
{
	Direct3D::ShowMouseCursor(false);
	XMINT2 rectPos = { (int)(Direct3D::GetScreenWidth() * 0.5f),(int)(Direct3D::GetScreenHeight() * 0.5f) };
	Direct3D::SetClipCursor({ rectPos.x,rectPos.y,rectPos.x + 1,rectPos.y + 1 });
	((Play_ManagementPart_BaseUI*)pParent_)->SetAccessUIFlag(false);
}
