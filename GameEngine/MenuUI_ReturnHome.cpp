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
	:UIBase(parent,"MenuUI_ReturnHome"),
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
	//�ƂɋA��{�^��
	Image returnHome(this);
	returnHome.Load("Assets/Image/SelectImage3.png");
	returnHome.SetPosition({ -1.2f,0.5f,0 });
	returnHome.SetRotation({ 0,0,180 });
	//returnHome.SetSize({ 5,2,0 });
	AddComponent<Image>(returnHome);
	XMFLOAT3 textPos = GetComponent<Image>().GetPositionAtPixel();

	//�ƂɋA��e�L�X�g
	Text commandText(this);
	commandText.SetText("�Ƃɖ߂�");
	commandText.SetPosition({ textPos.x + 200,textPos.y - 50 });
	AddComponent<Text>(commandText);
	//hAudio_ReturnHome_=AudioManager::Load()


	////�m�F�̉摜
	//Image confirmation(this);
	//confirmation.Load("Assets/Image/UIBaseImage1.png");
	//confirmation.SetDraw(false);
	//AddComponent<Image>(confirmation);
	//
	//XMFLOAT3 imagePos = confirmation.GetPositionAtPixel();
	//Text messageText(this);
	//messageText.SetText("�Z�[�u���܂�");
	//messageText.SetPosition({ imagePos.x - 20,imagePos.y - 20 });
	//messageText.isDraw_ = false;
	//AddComponent<Text>(messageText);
	//
	//
	//Image ok(this);
	//ok.Load("Assets/Image/ButtonImage02.png");
	//ok.SetPosition(0.1f, -0.2f);
	//ok.SetDraw(false);
	//confirmImageNum_ = AddComponent<Image>(ok);	
	//imagePos = ok.GetPositionAtPixel();
	//{
	//	Text commandText(this);
	//	commandText.SetText("OK");
	//	commandText.SetPosition({ imagePos.x - 20,imagePos.y - 20 });
	//	commandText.isDraw_ = false;
	//	AddComponent<Text>(commandText);
	//}
	//Image cancel(this);
	//cancel.Load("Assets/Image/ButtonImage02.png");
	//cancel.SetPosition(-0.1f, -0.2f);
	//cancel.SetDraw(false);
	//cancelImageNum_ = AddComponent<Image>(cancel);
	//
	//{
	//	imagePos = cancel.GetPositionAtPixel();
	//	Text commandText(this);
	//	commandText.SetText("�L�����Z��");
	//	commandText.SetPosition({ imagePos.x - 20,imagePos.y - 20 });
	//	commandText.isDraw_ = false;
	//	AddComponent<Text>(commandText);
	//}
}

void MenuUI_ReturnHome::Start()
{
}

void MenuUI_ReturnHome::Update()
{
	//if (isClickedButton_)
	//{
	//	if (Input::IsMouseButtonUp(0))
	//	{
	//		if (GetComponent<Image>(confirmImageNum_).IsHitCursor())
	//		{
	//			((P_CP_MenuUI*)pParent_)->ReturnHome();
	//
	//		}
	//		else if (GetComponent<Image>(cancelImageNum_).IsHitCursor())
	//		{
	//			((UIBase*)pParent_)->SetCurrentOpenUINumber(-1);
	//			isClickedButton_ = false;
	//			SetDrawFlag(false);
	//		}
	//	}
	//}

	if (!isClickedButton_)
	{
		//����UI���J���Ă�ꍇ
		if (((UIBase*)pParent_)->GetCurrentOpenUINumber() != -1)
			return;
		if (!GetComponent<Image>().IsHitCursor())
		{
			GetComponent<Image>().SetPosition({ -1.2f,0.5f,0 });
			return;
		}
		GetComponent<Image>().SetPosition({ -1.1,0.5,0 });
		if (Input::IsMouseButtonUp(0) && GetComponent<Image>().IsHitCursor() && !isClickedButton_)
		{
			isClickedButton_ = true;
			pParent_->GetComponent<Audio>().Play();
			ConfirmationUI& cfmUI = *Instantiate<ConfirmationUI>(this);
			cfmUI.SetConfitmentText("�Z�[�u���܂����H");
			cfmUI.GetConfirmFunction() = [&]() {return ClickOKButton(); };
			cfmUI.GetCancelFunction() = [&]() {return ClickCancelButton(); };
			((UIBase*)pParent_)->SetCurrentOpenUINumber(GetUINumber());
			//SetDrawFlag(true);
			GetComponent<Image>().SetPosition({ -1.2f,0.5f,0 });
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
	isClickedButton_ = false;
}

void MenuUI_ReturnHome::Release()
{
}