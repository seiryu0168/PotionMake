#include "Play_ManagementPart_OutingUI.h"
#include"Engine/Systems/TextSystem.h"
#include"Engine/DirectX_11/Input.h"
Play_ManagementPart_OutingUI::Play_ManagementPart_OutingUI(Object* parent)
	:UIBase(parent,"Play_ManagementPart_OutingUI")
{
}

Play_ManagementPart_OutingUI::~Play_ManagementPart_OutingUI()
{
}

void Play_ManagementPart_OutingUI::Initialize()
{
	Text collectionText(this);
	collectionText.SetText("çÃèWÇ…çsÇ≠");
	collectionText.SetPosition({ 0.5f,0.5f });
	AddComponent<Text>(collectionText);
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
