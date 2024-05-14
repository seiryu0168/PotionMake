#include "MenuUI_Status.h"
#include"Engine/Systems/ImageSystem.h"
#include"Engine/Systems/TextSystem.h"
#include"Engine/DirectX_11/Input.h"
#include"InterSceneData.h"
#include"PlayerData.h"
#include"Status.h"
#include"CloseButton.h"
#include"Engine/Components/Audio.h"

MenuUI_Status::MenuUI_Status(Object* parent)
	:UIBase(parent,"MenuUI_Status"),
	isClickedButton_(false)
{
}

MenuUI_Status::~MenuUI_Status()
{
}

void MenuUI_Status::Initialize()
{
	//ステータスボタン
	Image returnHome(this);
	returnHome.Load("Assets/Image/SelectImage3.png");
	returnHome.SetPosition({ -1.2f,-0.1f,0 });
	returnHome.SetRotation({ 0,0,180 });
	//returnHome.SetSize({ 5,2,0 });
	AddComponent<Image>(returnHome);
	XMFLOAT3 textPos = GetComponent<Image>().GetPositionAtPixel();

	//ボタンテキスト
	Text commandText(this);
	commandText.SetText("ステータス");
	commandText.SetPosition({ textPos.x + 200,textPos.y - 50 });
	AddComponent<Text>(commandText);
}

void MenuUI_Status::Start()
{
}

void MenuUI_Status::Update()
{
	if (isClickedButton_)
	{
		//if (Input::IsMouseButtonUp(0))
		//{
		//	if (GetComponent<Image>(closeButtonNum_).IsHitCursor())
		//	{
		//		status_->KillMe();
		//		((UIBase*)pParent_)->SetCurrentOpenUINumber(-1);
		//		isClickedButton_ = false;
		//	}
		//}
	}

	if (!isClickedButton_)
	{
		//他のUIを開いてる場合
		if (((UIBase*)pParent_)->GetCurrentOpenUINumber() != -1)
			return;

		if (!GetComponent<Image>().IsHitCursor())
		{
			GetComponent<Image>().SetPosition({ -1.2f,-0.1f,0 });
			return;
		}
		GetComponent<Image>().SetPosition({ -1.1f,-0.1f,0 });
		if (Input::IsMouseButtonUp(0) && GetComponent<Image>().IsHitCursor() && !isClickedButton_)
		{
			isClickedButton_ = true;
			pParent_->GetComponent<Audio>().Play();
			status_ = Instantiate<Status>(this);
			CloseButton& clsBtn = *Instantiate<CloseButton>(status_);
			clsBtn.GetComponent<Image>().SetPosition({ -0.2f,0.5f,0 });
			clsBtn.GetFunction() = [&]() {return CloseStatusUI(); };
			//CreateStatus();
			((UIBase*)pParent_)->SetCurrentOpenUINumber(GetUINumber());
			GetComponent<Image>().SetPosition({ -1.2f,-0.1f,0 });
		}

	}
}

void MenuUI_Status::CreateStatus()
{
	Image confirmation(this);
	confirmation.Load("Assets/Image/UIBaseImage1.png");
	statusImageNum_ = AddComponent<Image>(confirmation);

	PlayerData& pData = *InterSceneData::GetData<PlayerData>("Data01");

	XMFLOAT3 pos = confirmation.GetPositionAtPixel();
	Text name(this);
	name.SetText(pData.name_);
	name.SetPosition({ pos.x-200,pos.y-200 });
	nameTextNum_ = AddComponent<Text>(name);

	Text  money(this);
	money.SetText(std::to_string(pData.money_));
	money.SetPosition({ pos.x - 200,pos.y - 100 });
	moneyTextNum_ = AddComponent<Text>(money);
}

void MenuUI_Status::RemoveStatus()
{
	//RemoveComponent<Image>(statusImageNum_);
	//RemoveComponent<Text>(nameTextNum_);
	//RemoveComponent<Text>(moneyTextNum_);
	
}

void MenuUI_Status::CloseStatusUI()
{
	((UIBase*)pParent_)->SetCurrentOpenUINumber(-1);
	isClickedButton_ = false;
}

void MenuUI_Status::Release()
{
}
