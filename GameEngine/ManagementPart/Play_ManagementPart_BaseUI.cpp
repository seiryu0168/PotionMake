#include "Play_ManagementPart_BaseUI.h"
#include"Outing/Play_ManagementPart_OutingUI.h"
#include"../Player_ManagementPart.h"
#include"Craft/Play_ManagementPart_CraftUI.h"
#include"PotionManagement/Play_ManagementPart_PotionManagerUI.h"
#include"../Engine/Systems/TextSystem.h"
#include"../Engine/Systems/ImageSystem.h"
#include"../Engine/DirectX_11/Input.h"
#include"../P_MP_MenuUI.h"
#include"../InterSceneData.h"
#include"../PlayerData.h"
#include"../ResourceStatusData.h"
#include"../TutorialButton.h"
#include"../Tutorial.h"
#include"../CloseButton.h"
#include"../Engine/ResourceManager/AudioManager.h"
namespace
{
	RECT clipRange;
}
Play_ManagementPart_BaseUI::Play_ManagementPart_BaseUI(Object* parent)
	:GameObject(parent,"Play_ManagementPart_BaseUI"),
	UINum_(0),
	isAccessUI_(false),
	hAudio_UIOpen_(-1),
	isTutorial_(false)
{
}

Play_ManagementPart_BaseUI::~Play_ManagementPart_BaseUI()
{
}

void Play_ManagementPart_BaseUI::Initialize()
{
	XMINT2 range = { (int)(Direct3D::GetScreenWidth() * 0.5f),(int)(Direct3D::GetScreenHeight() * 0.5f) };
	clipRange = { range.x,range.y,range.x + 1,range.y + 1 };
	Direct3D::SetClipCursor(clipRange);
	Direct3D::ShowMouseCursor(false);

	//ボタンUIの画像
	Image actionImage(this);
	actionImage.Load("Assets/Image/SelectImage3.png");
	actionImage.SetPosition({ 0.7f,-0.015f,0 });
	actionImage.SetSize({0.7,0.7f,0});
	AddComponent<Image>(actionImage);

	Text text(this, "Rounded M+ 1c");
	text.SetText("Text");
	text.SetTextSize(55);
	text.SetRect({ 0,0,500,500 });
	text.SetPosition({ 1350,505 });
	AddComponent<Text>(text);

	//押すキーの画像
	Image buttonImage(this);
	buttonImage.Load("Assets/Image/Circle.png");
	buttonImage.SetPosition({ 0.37f,-0.015f,0 });
	buttonImage.SetSize({ 0.5f,0.5f,0 });
	AddComponent<Image>(buttonImage);

	XMFLOAT3 buttonTextPos = buttonImage.GetPositionAtPixel();
	Text buttonText(this, "Rounded M+ 1c");
	buttonText.SetText("F");
	buttonText.SetColor({ 0,0,0,1 });
	buttonText.SetTextSize(40);
	buttonText.SetRect({ 0,0,40,40 });
	buttonText.SetPosition({ buttonTextPos.x-10,buttonTextPos.y-30 });
	AddComponent<Text>(buttonText);

	player_ = (Player_ManagementPart*)FindObject("Player_ManagementPart");
	hAudio_UIOpen_ = AudioManager::Load("Assets/Audio/Confirm29.wav");
	
	PlayerData* pData = InterSceneData::GetData<PlayerData>("Data01");
	if (pData->isFirstPlay_)
	{
		Tutorial* tutorial = Instantiate<Tutorial>(this);
		for (auto& data : InterSceneData::GetData<ResourceStatusData>("ResourceData")->tutorialData_[0])
		{
			tutorial->SetTutorialData(data.first, data.second);
		}
		tutorial->CreatePageCount();
		EnableTutorialUI();
		((CloseButton*)tutorial->FindChild("CloseButton"))->GetFunction() = [&]() {return CloseFirstTutorialButton(); };
		pData->isFirstPlay_ = false;

	}
	//else
	//{
	//	TutorialButton* tutorialBtn = Instantiate<TutorialButton>(this);
	//
	//	for (auto& data : InterSceneData::GetData<ResourceStatusData>("ResourceData")->tutorialData_[0])
	//	{
	//		tutorialBtn->SetTutorialData(data.first, data.second);
	//	}
	//	//tutorialBtn->SetTutorialData("Assets/Image/Ico_Foot.png","foot");
	//	//tutorialBtn->SetTutorialData("Assets/Image/Icon_Luck.png","luck");
	//	//tutorialBtn->SetTutorialData("Assets/Image/Icon_Magic.png","magic");
	//	tutorialBtn->GetEnableFunction() = [&]() {return EnableTutorialUI(); };
	//	tutorialBtn->GetInvalidFunction() = [&]() {return InvalidTutorialUI(); };
	//	tutorialBtn->SetActive(false);
	//}
}

void Play_ManagementPart_BaseUI::Start()
{

}

void Play_ManagementPart_BaseUI::Update()
{
	if (Input::IsKeyDown(DIK_ESCAPE)&&!isAccessUI_&& !isTutorial_)
	{
		Direct3D::ShowMouseCursor(true);
		Direct3D::SetClipCursor();
		isAccessUI_ = true;

		AudioManager::Play(hAudio_UIOpen_);
		Instantiate<P_MP_MenuUI>(this);
		SetUIOpenFlag(true);
		FindChild("TutorialButton")->SetActive(true);
	}
}

void Play_ManagementPart_BaseUI::CloseFirstTutorialButton()
{
	if (isAccessUI_)
		FindChild("P_MP_MenuUI")->SetUpdate(true);

	if (!isAccessUI_)
	{
		player_->SetControllFlag(true);
		Direct3D::SetClipCursor(clipRange);
		Direct3D::ShowMouseCursor(false);
		if (FindChild("TutorialButton"))
			FindChild("TutorialButton")->SetActive(false);
	}
	DisplayAction("", true);
	isTutorial_ = false;
	isTutorial_ = false;
}

void Play_ManagementPart_BaseUI::EnableTutorialUI()
{
	isTutorial_ = true;
	if(isAccessUI_)
	FindChild("P_MP_MenuUI")->SetUpdate(false);

	player_->SetControllFlag(false);
	Direct3D::SetClipCursor();
	Direct3D::ShowMouseCursor(true);
	DisplayAction("", false);
}

void Play_ManagementPart_BaseUI::InvalidTutorialUI()
{
	if(isAccessUI_)
	FindChild("P_MP_MenuUI")->SetUpdate(true);
	
	if (!isAccessUI_)
	{
		player_->SetControllFlag(true);
		Direct3D::SetClipCursor(clipRange);
		Direct3D::ShowMouseCursor(false);
		if(FindChild("TutorialButton"))
			FindChild("TutorialButton")->SetActive(false);
	}
	DisplayAction("", true);
	isTutorial_ = false;
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
			DisplayAction("", false);
			isAccessUI_ = true;
			Instantiate<Play_ManagementPart_CraftUI>(this);
		}
		break;

	default:
		break;
	}
}

void Play_ManagementPart_BaseUI::SetUIOpenFlag(bool flag)
{
	player_->SetControllFlag(!flag);
	//メニューUIを閉じる
	if (!flag)
	{
		Direct3D::SetClipCursor(clipRange);
		Direct3D::ShowMouseCursor(false);
	}
	//メニューUIを開く
	else
	{
		Direct3D::SetClipCursor();
		Direct3D::ShowMouseCursor(true);
	}
}

void Play_ManagementPart_BaseUI::DisplayAction(std::string action, bool isDisplay)
{
	//子供がいたら(UIが開かれている状況だったら)
	//if (!childList_.empty())
	//	return;
	GetComponent<Text>().SetText(action);
	GetComponent<Text>(1).isDraw_=isDisplay;

	GetComponent<Image>().SetDraw(isDisplay);
	GetComponent<Image>(1).SetDraw(isDisplay);
}
