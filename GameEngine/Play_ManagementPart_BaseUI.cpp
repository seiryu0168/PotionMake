#include "Play_ManagementPart_BaseUI.h"
#include"Engine/Systems/TextSystem.h"
#include"Play_ManagementPart_OutingUI.h"
Play_ManagementPart_BaseUI::Play_ManagementPart_BaseUI(Object* parent)
	:GameObject(parent,"Play_ManagementPart_BaseUI"),
	UINum_(0)
{
}

Play_ManagementPart_BaseUI::~Play_ManagementPart_BaseUI()
{
}

void Play_ManagementPart_BaseUI::Initialize()
{
	Text text(this);
	//text.SetAlignmentType(ALIGNMENT_TYPE::RIGHT_CENTER);
	text.SetText("Text");
	text.SetRect({ 0,0,1000,500 });
	text.SetPosition({ 1420,500 });
	AddComponent<Text>(text);
}

void Play_ManagementPart_BaseUI::Start()
{

}

void Play_ManagementPart_BaseUI::Update()
{
}

void Play_ManagementPart_BaseUI::Release()
{
}

void Play_ManagementPart_BaseUI::AccessUI(int uiNum)
{
	switch (uiNum)
	{
	case 0:
		Instantiate<Play_ManagementPart_OutingUI>(this);
	default:
		break;
	}
}
