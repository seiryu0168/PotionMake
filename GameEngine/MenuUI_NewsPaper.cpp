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
		//画像にカーソルが当っていない時
		if (!GetComponent<Image>().IsHitCursor())
		{
			GetComponent<Image>().SetPosition(buttonPos_);
			return;
		}
		GetComponent<Image>().SetPosition({ buttonPos_.x + 0.1f,buttonPos_.y,0 });
		if (Input::IsMouseButtonUp(0) && GetComponent<Image>().IsHitCursor() && !isClickedButton_)
		{
			//クリックフラグをtrueに設定
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
