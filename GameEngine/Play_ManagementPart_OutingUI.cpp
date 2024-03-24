#include "Play_ManagementPart_OutingUI.h"
#include"Engine/Systems/TextSystem.h"
#include"Engine/Systems/ImageSystem.h"
#include"Engine/DirectX_11/Input.h"
#include"P_MP_OutingUI_ActionText.h"
Play_ManagementPart_OutingUI::Play_ManagementPart_OutingUI(Object* parent)
	:UIBase(parent,"Play_ManagementPart_OutingUI")
{
}

Play_ManagementPart_OutingUI::~Play_ManagementPart_OutingUI()
{
}

void Play_ManagementPart_OutingUI::Initialize()
{
	Image uiBaseImage(this);
	uiBaseImage.Load("Assets/Image/UIBaseImage1.png");
	AddComponent<Image>(uiBaseImage);

	Text collectionText(this);
	collectionText.SetText("äOèo");
	collectionText.SetPosition({ 880,300 });
	AddComponent<Text>(collectionText);

	Instantiate<P_MP_OutingUI_ActionText>(this);
}

void Play_ManagementPart_OutingUI::Update()
{
	if (Input::IsMouseButtonDown(0))
	{
		KillMe();
	}
}

void Play_ManagementPart_OutingUI::Release()
{
}
