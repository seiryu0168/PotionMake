#include "MenuUI_ReturnHome.h"
#include"Engine/Systems/ImageSystem.h"
#include"Engine/Systems/TextSystem.h"
#include "Engine/DirectX_11/Input.h"
#include "InterSceneData.h"
#include"CollectionPart/P_CP_MenuUI.h"
//#include"Engine/ResourceManager/AudioManager.h"
#include"ConfirmationUI.h"
#include"Engine/Components/Audio.h"

MenuUI_ReturnHome::MenuUI_ReturnHome(Object* parent)
	:MenuUI(parent,"MenuUI_ReturnHome"),
	confirmImageNum_(-1),
	cancelImageNum_(-1),
	isClickedButton_(false)
{
}

MenuUI_ReturnHome::~MenuUI_ReturnHome()
{
}

void MenuUI_ReturnHome::Initialize()
{

}

void MenuUI_ReturnHome::Start()
{
}

void MenuUI_ReturnHome::Update()
{
	if (!IsClickButton())
	{
		//‘¼‚ÌUI‚ðŠJ‚¢‚Ä‚éê‡
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
			cfmUI.SetConfitmentText("‰Æ‚É‹A‚è‚Ü‚·‚©H");
			cfmUI.GetConfirmFunction() = [&]() {return ClickOKButton(); };
			cfmUI.GetCancelFunction() = [&]() {return ClickCancelButton(); };
			((UIBase*)pParent_)->SetCurrentOpenUINumber(GetUINumber());
			//SetDrawFlag(true);
			GetComponent<Image>().SetPosition(buttonPos_);
		}

	}
}

void MenuUI_ReturnHome::SetDrawFlag(bool flag)
{
	GetComponent<Image>(1).SetDraw(flag);
	GetComponent<Image>(confirmImageNum_).SetDraw(flag);
	GetComponent<Image>(cancelImageNum_).SetDraw(flag);

	GetComponent<Text>(1).isDraw_=flag;
	GetComponent<Text>(2).isDraw_=flag;
	GetComponent<Text>(3).isDraw_=flag;
}

void MenuUI_ReturnHome::ClickOKButton()
{
	((P_CP_MenuUI*)pParent_)->ReturnHome();
}

void MenuUI_ReturnHome::ClickCancelButton()
{
	((UIBase*)pParent_)->SetCurrentOpenUINumber(-1);
	pParent_->GetComponent<Audio>().Play();
	SetClickFlag(false);
}

void MenuUI_ReturnHome::Release()
{
}
