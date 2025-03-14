#include "MenuUI_NewsPaper.h"
#include"Engine/Systems/ImageSystem.h"
#include"Engine/Systems/TextSystem.h"
#include"Engine/DirectX_11/Input.h"
#include"InterSceneData.h"
#include"PlayerData.h"
#include"ResourceStatusData.h"
#include"P_MP_NewsPaper.h"
#include"CloseButton.h"
#include"Engine/Components/Audio.h"
MenuUI_NewsPaper::MenuUI_NewsPaper(Object* parent)
	:MenuUI(parent,"MenuUI_NewsPaper"),
	isClickedButton_(false),
	closeButtonNum_(-1)
{
}

MenuUI_NewsPaper::~MenuUI_NewsPaper()
{
}

void MenuUI_NewsPaper::Initialize()
{
	//Image buttonImage(this);
	//buttonImage.Load("Assets/Image/SelectImage3.png");
	//buttonImage.SetPosition({ -1.2f,0.2f,0 });
	//buttonImage.SetRotation({ 0,0,180 });
	//AddComponent<Image>(buttonImage);
	//
	//XMFLOAT3 textPos = buttonImage.GetPositionAtPixel();
	//Text buttonText(this);
	//buttonText.SetText("新聞");
	//buttonText.SetPosition({ textPos.x + 200,textPos.y - 50 });
	//AddComponent<Text>(buttonText);
	//
	//int num = InterSceneData::GetData<PlayerData>("Data01")->newsPaperNumber_;
	//std::string imageName = InterSceneData::GetData<ResourceStatusData>("ResourceData")->newsPaperList_[num].resourceImageName_;
	//Image newsPaperImage(this);
	//newsPaperImage.Load("Assets/Image/" + imageName);
	//newsPaperImage.SetPosition({ 0.4f,0,0 });
	//newsPaperImage.SetDraw(false);
	//AddComponent<Image>(newsPaperImage);

	//Image closeImage(this);
	//closeImage.Load("Assets/Image/CloseButtonImage.png");
	//closeImage.SetPosition({ 0,0.5f,0 });
	//closeImage.SetSize({ 0.6f,0.6f,0 });
	//closeImage.SetDraw(false);
	//closeButtonNum_ = AddComponent<Image>(closeImage);
}

void MenuUI_NewsPaper::Start()
{
}

void MenuUI_NewsPaper::Update()
{
	if (!IsClickButton())
	{
		//他のUIを開いてる場合
		if (((UIBase*)pParent_)->GetCurrentOpenUINumber() != -1)
			return;

		if (!GetComponent<Image>().IsHitCursor())
		{
			GetComponent<Image>().SetPosition(buttonPos_);
			return;
		}
		GetComponent<Image>().SetPosition({ buttonPos_.x + 0.1f,buttonPos_.y,0 });
		if (Input::IsMouseButtonUp(0) && GetComponent<Image>().IsHitCursor() && !isClickedButton_)
		{
			SetClickFlag(true);
			pParent_->GetComponent<Audio>().Play();
			GameObject* paper = Instantiate<P_MP_NewsPaper>(this);
			CloseButton& clsBtn = *Instantiate<CloseButton>(paper);
			clsBtn.GetComponent<Image>().SetPosition({ -0.1,0.9f,0 });
			clsBtn.GetFunction() = [&]() {return ClickCloseButton(); };
			((UIBase*)pParent_)->SetCurrentOpenUINumber(GetUINumber());
			//SetDrawFlag(true);
			GetComponent<Image>().SetPosition(buttonPos_);
		}

	}
}

void MenuUI_NewsPaper::SetDrawFlag(bool flag)
{
	GetComponent<Image>(1).SetDraw(flag);
	GetComponent<Image>(closeButtonNum_).SetDraw(flag);
}

void MenuUI_NewsPaper::ChangeText()
{
	GetComponent<Text>().SetText("AAAA");
}

void MenuUI_NewsPaper::ClickCloseButton()
{
	((UIBase*)pParent_)->SetCurrentOpenUINumber(-1);
	SetClickFlag(false);
}

void MenuUI_NewsPaper::Release()
{
}
