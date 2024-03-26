#include "Play_ManagementPart_BaseUI.h"
#include"Engine/Systems/TextSystem.h"
#include"Engine/Systems/ImageSystem.h"
#include"Play_ManagementPart_OutingUI.h"
#include"Play_ManagementPart_CraftUI.h"
#include"Play_ManagementPart_PotionManagerUI.h"
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
	Image actionImage(this);
	actionImage.Load("Assets/Image/SelectImage3.png");
	actionImage.SetPosition({ 0.7f,-0.015f,0 });
	actionImage.SetSize({0.7,0.7f,0});
	AddComponent<Image>(actionImage);
	Text text(this);
	//text.SetAlignmentType(ALIGNMENT_TYPE::RIGHT_CENTER);
	text.SetText("Text");
	text.SetRect({ 0,0,500,500 });
	//text.SetAlignmentType(ALIGNMENT_TYPE::RIGHT_TOP);
	text.SetPosition({ 1320,500 });
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
		if (!FindChild("Play_ManagementPart_OutingUI"))
		{
			DisplayAction("", false);
			Instantiate<Play_ManagementPart_OutingUI>(this);
		}
		break;
	case 1:
		if (!FindChild("Play_ManagementPart_PotionManagerUI"))
		{
			DisplayAction("", false);
			Instantiate<Play_ManagementPart_PotionManagerUI>(this);
		}
		break;
	case 2:
		if (!FindChild("Play_ManagementPart_CraftUI"))
		{
			DisplayAction("", false);
			Instantiate<Play_ManagementPart_CraftUI>(this);
		}
		break;

	default:
		break;
	}
}

void Play_ManagementPart_BaseUI::DisplayAction(std::string action,bool isDisplay)
{
	//éqãüÇ™Ç¢ÇΩÇÁ(UIÇ™äJÇ©ÇÍÇƒÇ¢ÇÈèÛãµÇæÇ¡ÇΩÇÁ)
	if (!childList_.empty())
		return;
	GetComponent<Text>().SetText(action);
	GetComponent<Image>().SetAlpha(isDisplay);
}
