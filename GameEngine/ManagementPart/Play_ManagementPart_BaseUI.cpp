#include "Play_ManagementPart_BaseUI.h"
#include"Outing/Play_ManagementPart_OutingUI.h"
#include"Craft/Play_ManagementPart_CraftUI.h"
#include"PotionManagement/Play_ManagementPart_PotionManagerUI.h"
#include"../Engine/Systems/TextSystem.h"
#include"../Engine/Systems/ImageSystem.h"
#include"../Engine/DirectX_11/Input.h"
#include"../P_MP_MenuUI.h"
#include"../Engine/ResourceManager/AudioManager.h"

Play_ManagementPart_BaseUI::Play_ManagementPart_BaseUI(Object* parent)
	:GameObject(parent,"Play_ManagementPart_BaseUI"),
	UINum_(0),
	isAccessUI_(false),
	hAudio_UIOpen_(-1)
{
}

Play_ManagementPart_BaseUI::~Play_ManagementPart_BaseUI()
{
}

void Play_ManagementPart_BaseUI::Initialize()
{
	Direct3D::ShowMouseCursor(false);
	Image actionImage(this);
	actionImage.Load("Assets/Image/SelectImage3.png");
	actionImage.SetPosition({ 0.7f,-0.015f,0 });
	actionImage.SetSize({0.7,0.7f,0});
	AddComponent<Image>(actionImage);
	Text text(this);
	text.SetText("Text");
	text.SetRect({ 0,0,500,500 });
	text.SetPosition({ 1320,520 });
	AddComponent<Text>(text);

	hAudio_UIOpen_ = AudioManager::Load("Assets/Audio/Confirm29.wav");
}

void Play_ManagementPart_BaseUI::Start()
{

}

void Play_ManagementPart_BaseUI::Update()
{
	if (Input::IsKeyDown(DIK_ESCAPE)&&!isAccessUI_)
	{
		Direct3D::ShowMouseCursor(true);
		Direct3D::SetClipCursor();
		isAccessUI_ = true;

		AudioManager::Play(hAudio_UIOpen_);
		Instantiate<P_MP_MenuUI>(this);
	}
}

void Play_ManagementPart_BaseUI::Release()
{
}

void Play_ManagementPart_BaseUI::AccessUI(int uiNum)
{
	Direct3D::ShowMouseCursor(true);
	Direct3D::SetClipCursor();
	AudioManager::Play(hAudio_UIOpen_);
	switch (uiNum)
	{
	case 0:
		if (!FindChild("Play_ManagementPart_OutingUI"))
		{
			DisplayAction("", false);
			isAccessUI_ = true;
			Instantiate<Play_ManagementPart_OutingUI>(this);
		}
		break;
	case 1:
		if (!FindChild("Play_ManagementPart_PotionManagerUI"))
		{
			DisplayAction("", false);
			isAccessUI_ = true;
			Instantiate<Play_ManagementPart_PotionManagerUI>(this);
		}
		break;
	case 2:
		if (!FindChild("Play_ManagementPart_CraftUI"))
		{
			isAccessUI_ = true;
			DisplayAction("", false);
			Instantiate<Play_ManagementPart_CraftUI>(this);
		}
		break;

	default:
		break;
	}
}

void Play_ManagementPart_BaseUI::DisplayAction(std::string action, bool isDisplay)
{
	//éqãüÇ™Ç¢ÇΩÇÁ(UIÇ™äJÇ©ÇÍÇƒÇ¢ÇÈèÛãµÇæÇ¡ÇΩÇÁ)
	if (!childList_.empty())
		return;
	GetComponent<Text>().SetText(action);
	GetComponent<Image>().SetAlpha(isDisplay);
}
