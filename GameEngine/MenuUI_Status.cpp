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
	:MenuUI(parent,"MenuUI_Status"),
	isClickedButton_(false)
{
}

MenuUI_Status::~MenuUI_Status()
{
}

void MenuUI_Status::Initialize()
{
}

void MenuUI_Status::Start()
{
}

void MenuUI_Status::Update()
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
			status_ = Instantiate<Status>(this);
			CloseButton& clsBtn = *Instantiate<CloseButton>(status_);
			clsBtn.GetComponent<Image>().SetPosition({ -0.37f,0.62f,0 });
			clsBtn.GetFunction() = [&]() {return CloseStatusUI(); };
			//CreateStatus();
			((UIBase*)pParent_)->SetCurrentOpenUINumber(GetUINumber());
			GetComponent<Image>().SetPosition(buttonPos_);
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
	SetClickFlag(false);
}

void MenuUI_Status::Release()
{
}
