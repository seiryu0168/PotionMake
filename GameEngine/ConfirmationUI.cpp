#include "ConfirmationUI.h"
#include "Engine/Systems/ImageSystem.h"
#include "Engine/Systems/TextSystem.h"
#include "Engine/DirectX_11/Input.h"
#include "Engine/ResourceManager/AudioManager.h"
#include"Engine/Systems/AudioSystem.h"

ConfirmationUI::ConfirmationUI(Object* parent)
	:GameObject(parent,"ConfirmationUI")
	
{
}

ConfirmationUI::~ConfirmationUI()
{
}

void ConfirmationUI::Initialize()
{
	Image confirmation(this);
	confirmation.Load("Assets/Image/UIBaseImage1.png");
	AddComponent<Image>(confirmation);

	XMFLOAT3 imagePos = confirmation.GetPositionAtPixel();
	XMFLOAT3 imageSize = confirmation.GetSizeAtPixel();
	Text messageText(this);
	messageText.SetText("確認");
	messageText.SetAlignmentType(ALIGNMENT_TYPE::CENTER_TOP);
	messageText.SetPosition({ imagePos.x - imageSize.x*0.5f,imagePos.y - imageSize.y*0.4f });
	AddComponent<Text>(messageText);


	Image ok(this);
	ok.Load("Assets/Image/ButtonImage02.png");
	ok.SetPosition(0.1f, -0.2f);
	ok.SetSize({ 0.7f,0.7f,0 });
	confirmImageNum_ = AddComponent<Image>(ok);
	imageSize = ok.GetSizeAtPixel();
	TEXT_RECT rect = { 0,0,imageSize.x,imageSize.y };
	{
		imagePos = ok.GetPositionAtPixel();
		Text commandText(this);
		commandText.SetRect(rect);
		commandText.SetAlignmentType(ALIGNMENT_TYPE::CENTER_CENTER);
		commandText.SetText("OK");
		commandText.SetPosition({ imagePos.x-imageSize.x*0.5f,imagePos.y - imageSize.y * 0.5f });
		AddComponent<Text>(commandText);
	}
	Image cancel(this);
	cancel.Load("Assets/Image/ButtonImage02.png");
	cancel.SetPosition(-0.1f, -0.2f);
	cancel.SetSize({ 0.7f,0.7f,0 });
	cancelImageNum_ = AddComponent<Image>(cancel);

	{
		imagePos = cancel.GetPositionAtPixel();
		Text commandText(this);
		commandText.SetRect(rect);
		commandText.SetAlignmentType(ALIGNMENT_TYPE::CENTER_CENTER);
		commandText.SetTextSize(45);
		commandText.SetText("キャンセル");
		commandText.SetPosition({ imagePos.x - imageSize.x * 0.5f,imagePos.y - imageSize.y * 0.5f });
		AddComponent<Text>(commandText);
	}
	Audio confirmAudio(this);
	confirmAudio.Load("Assets/Audio/Confirm51.wav");
	AddComponent<Audio>(confirmAudio);

	Audio cancelAudio(this);
	cancelAudio.Load("Assets/Audio/Cancel09.wav");
	AddComponent<Audio>(cancelAudio);
}

void ConfirmationUI::Start()
{
}

void ConfirmationUI::Update()
{
	//ボタンにカーソルが触れてた場合、少し大きくなる
	if (GetComponent<Image>(confirmImageNum_).IsHitCursor())
	{
		GetComponent<Image>(confirmImageNum_).SetSize({ 0.75f,0.75f,0 });
		if (Input::IsMouseButtonUp(0))
		{
			if (isSetConfirmFunction_)
				confirmFunction_();
			GetComponent<Audio>(0).Play();
			KillMe();
		}
	}
	else
		GetComponent<Image>(confirmImageNum_).SetSize({ 0.7f,0.7f,0 });
	if (GetComponent<Image>(cancelImageNum_).IsHitCursor())
	{
		GetComponent<Image>(cancelImageNum_).SetSize({ 0.75f,0.75f,0 });
		if (Input::IsMouseButtonUp(0))
		{
			if (isSetCancelFunction_)
				cancelFunction_();
			GetComponent<Audio>(1).Play();
			KillMe();
		}
	}
	else
		GetComponent<Image>(cancelImageNum_).SetSize({ 0.7f,0.7f,0 });
}

void ConfirmationUI::SetConfitmentText(const std::string& str)
{
	GetComponent<Text>().SetText(str);
}

std::function<void()>& ConfirmationUI::GetConfirmFunction()
{	
	isSetConfirmFunction_ = true;
	return confirmFunction_;
}

std::function<void()>& ConfirmationUI::GetCancelFunction()
{
	isSetCancelFunction_ = true;
	return cancelFunction_;
}

void ConfirmationUI::Release()
{
}
