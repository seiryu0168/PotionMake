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
	:UIBase(parent,"MenuUI_Save"),
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
	Image save(this);
	save.Load("Assets/Image/SelectImage3.png");
	save.SetPosition({ -1.2f,0.5f,0 });
	save.SetRotation({ 0,0,180 });
	//save.SetSize({ 5,2,0 });
	AddComponent<Image>(save);
	XMFLOAT3 textPos = save.GetPositionAtPixel();
	Text saveText(this);
	saveText.SetText("セーブ");
	saveText.SetPosition({ textPos.x + 200,textPos.y - 50 });
	AddComponent<Text>(saveText);
	

	//Image confirmation(this);
	//confirmation.Load("Assets/Image/UIBaseImage1.png");
	//confirmation.SetDraw(false);
	//AddComponent<Image>(confirmation);

	//XMFLOAT3 imagePos = confirmation.GetPositionAtPixel();
	//Text messageText(this);
	//messageText.SetText("セーブします");
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
	//	commandText.SetText("キャンセル");
	//	commandText.SetPosition({ imagePos.x - 20,imagePos.y - 20 });
	//	commandText.isDraw_ = false;
	//	AddComponent<Text>(commandText);
	//}


}

void MenuUI_Save::Start()
{
}

void MenuUI_Save::Update()
{
	
	//if (isClickedButton_)
	//{
	//	if (Input::IsMouseButtonUp(0))
	//	{
	//		if (GetComponent<Image>(confirmImageNum_).IsHitCursor())
	//			DataSave();
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
			//他のUIを開いてる場合
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
			cfmUI.SetConfitmentText("セーブしますか？");
			cfmUI.GetConfirmFunction() = [&]() {return DataSave(); };
			cfmUI.GetCancelFunction() = [&]() {return ClickCancelButton(); };
			((UIBase*)pParent_)->SetCurrentOpenUINumber(GetUINumber());
			//SetDrawFlag(true);
			GetComponent<Image>().SetPosition({ -1.2f,0.5f,0 });
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
}

void MenuUI_Save::ClickCancelButton()
{
	((UIBase*)pParent_)->SetCurrentOpenUINumber(-1);
	isClickedButton_ = false;
}

void MenuUI_Save::Release()
{
}
