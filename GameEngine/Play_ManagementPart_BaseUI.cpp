#include "Play_ManagementPart_BaseUI.h"
#include"Engine/Systems/TextSystem.h"
Play_ManagementPart_BaseUI::Play_ManagementPart_BaseUI(Object* parent)
	:GameObject(parent,"Play_ManagementPart_BaseUI")
{
}

Play_ManagementPart_BaseUI::~Play_ManagementPart_BaseUI()
{
}

void Play_ManagementPart_BaseUI::Initialize()
{
	Text text;
	text.SetText("Text");
	text.SetPosition({ 0.5f,0.5f });
	AddComponent<Text>(text);
}

void Play_ManagementPart_BaseUI::Update()
{
	//GetComponent<Text>();
}

void Play_ManagementPart_BaseUI::Release()
{
}
