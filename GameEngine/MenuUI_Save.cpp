#include "MenuUI_Save.h"
#include"Engine/Systems/ImageSystem.h"
#include"Engine/Systems/TextSystem.h"
#include"Engine/DirectX_11/Input.h"
#include"InterSceneData.h"
#include"PlayerData.h"
#include"SaveDataManager.h"
#include"ConfirmationUI.h"
#include"Engine/Components/Audio.h"

MenuUI_Save::MenuUI_Save(Object* parent)
	:MenuUI(parent,"MenuUI_Save"),
	confirmImageNum_(-1),
	cancelImageNum_(-1),
	isClickedButton_(false)
{
}

MenuUI_Save::~MenuUI_Save()
{
}

void MenuUI_Save::Initialize()
{
}

void MenuUI_Save::Start()
{
}

void MenuUI_Save::Update()
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
			ConfirmationUI& cfmUI = *Instantiate<ConfirmationUI>(this);
			cfmUI.SetConfitmentText("セーブしますか？");
			cfmUI.GetConfirmFunction() = [&]() {return ClickOKButton(); };
			cfmUI.GetCancelFunction() = [&]() {return ClickCancelButton(); };
			((UIBase*)pParent_)->SetCurrentOpenUINumber(GetUINumber());
			//SetDrawFlag(true);
			GetComponent<Image>().SetPosition(buttonPos_);
		}

	}
}

void MenuUI_Save::DataSave()
{
	SaveDataManager mng;

	mng.Save("", *InterSceneData::GetData<PlayerData>("Data01"));
}

void MenuUI_Save::SetDrawFlag(bool flag)
{
	GetComponent<Image>(1).SetDraw(flag);
	GetComponent<Image>(confirmImageNum_).SetDraw(flag);
	GetComponent<Image>(cancelImageNum_).SetDraw(flag);
	GetComponent<Text>(1).isDraw_ = flag;
	GetComponent<Text>(2).isDraw_ = flag;
	GetComponent<Text>(3).isDraw_ = flag;
}

void MenuUI_Save::ClickOKButton()
{
	pParent_->GetComponent<Audio>().Play();
	DataSave();
	((UIBase*)pParent_)->SetCurrentOpenUINumber(-1);
	SetClickFlag(false);
}

void MenuUI_Save::ClickCancelButton()
{
	((UIBase*)pParent_)->SetCurrentOpenUINumber(-1);
	SetClickFlag(false);
}

void MenuUI_Save::Release()
{
}
