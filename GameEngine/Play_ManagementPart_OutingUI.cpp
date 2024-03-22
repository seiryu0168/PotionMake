#include "Play_ManagementPart_OutingUI.h"
#include"Engine/Systems/TextSystem.h"
Play_ManagementPart_OutingUI::Play_ManagementPart_OutingUI(Object* parent)
	:GameObject(parent,"Play_ManagementPart_OutingUI")
{
}

Play_ManagementPart_OutingUI::~Play_ManagementPart_OutingUI()
{
}

void Play_ManagementPart_OutingUI::Initialize()
{
	Text collectionText;
	collectionText.SetText("çÃèWÇ…çsÇ≠");
	collectionText.SetPosition({ 0.5f,0.5f });
	AddComponent<Text>(collectionText);
}

void Play_ManagementPart_OutingUI::Update()
{
}

void Play_ManagementPart_OutingUI::Release()
{
}
