#include "SnowCone_ToppingSelect.h"
#include"SnowCone_ToppingUI.h"
#include"SnowCone_ToppingSumple.h"
#include"../Engine/Systems/ImageSystem.h"
#include"../Engine/Systems/TextSystem.h"
#include"../Engine/DirectX_11/Input.h"
#include"../Engine/ResourceManager/Audio.h"
namespace
{
	const XMFLOAT3 IMAGEPOS[] = { {1400,500,0},{1400,0,0},{1400,-500,0} };
	const std::string TOPPING_NAME[] = {"����","�u���[�x���[","���Y�x���["};
	const int SYRUP_LIMIT = 3;
	const int CAMERANUM = 2;
	const float INTERVAL_TIME = 0.15f;
}

SnowCone_ToppingSelect::SnowCone_ToppingSelect(Object* parent)
	:SnowCone_ToppingMenu(parent,"SnowCone_ToppingSelect"),
	selectFrame_(0),
	toppingText_(0)
{
}

SnowCone_ToppingSelect::~SnowCone_ToppingSelect()
{
}

void SnowCone_ToppingSelect::Initialize()
{
	//�g�b�s���O�̃e�L�X�g
	Text selectText("�g�b�s���O", "�肢�Ă����M", { 0,0,200,50 }, CAMERANUM);
	selectText.SetPosition({ 730,10 });
	selectText.SetTextSize(40);
	AddComponent<Text>(selectText);
	
	//���I��ł�g�b�s���O�̖��O
	Text currentToppingText(TOPPING_NAME[selectNum_], "�肢�Ă����M", {0,0,250,50}, CAMERANUM);
	currentToppingText.SetPosition({ 355,480 });
	currentToppingText.SetTextSize(40);
	toppingText_ = AddComponent<Text>(currentToppingText);
	
	//�g�b�s���O3��Ɣw�i�̉摜
	{
		Image backImage(CAMERANUM);
		backImage.Load("Assets/Image/SnowCone_Select_BuckGroundImage.png");
		backImage.SetPositionAtPixel(IMAGEPOS[0]);
		AddComponent<Image>(backImage);

		Image image(CAMERANUM);
		image.Load("Assets/Image/SnowCone_Topping_Adzuki.png");
		image.SetPositionAtPixel(IMAGEPOS[0]);
		AddComponent<Image>(image);
	}
	{
		Image backImage(CAMERANUM);
		backImage.Load("Assets/Image/SnowCone_Select_BuckGroundImage.png");
		backImage.SetPositionAtPixel(IMAGEPOS[1]);
		AddComponent<Image>(backImage);

		Image image(CAMERANUM);
		image.Load("Assets/Image/SnowCone_Topping_Blueberry.png");
		image.SetPositionAtPixel(IMAGEPOS[1]);
		AddComponent<Image>(image);
	}
	{
		Image backImage(CAMERANUM);
		backImage.Load("Assets/Image/SnowCone_Select_BuckGroundImage.png");
		backImage.SetPositionAtPixel(IMAGEPOS[2]);
		AddComponent<Image>(backImage);

		Image image(CAMERANUM);
		image.Load("Assets/Image/SnowCone_Topping_Raspberry.png");
		image.SetPositionAtPixel(IMAGEPOS[2]);
		AddComponent<Image>(image);
	}

	//�I��p�̘g�̉摜
	{
		Image image(CAMERANUM);
		image.Load("Assets/Image/SnowCone_SelectImage.png");
		image.SetPositionAtPixel(IMAGEPOS[0]);
		image.SetAlpha(0.4f);
		selectFrame_ = (int)AddComponent<Image>(image);
	}
	state_ = SELECT_STATE::STAY;
}

void SnowCone_ToppingSelect::Update()
{
	//���̏�Ԃɂ���ċ�����ς���
	//INPUT : ����
	//MOVE  : �J�[�\���ړ�
	switch (state_)
	{
	case SELECT_STATE::INPUT:
		Input();
		break;
	case SELECT_STATE::MOVE:
		Move();
		break;
	case SELECT_STATE::STAY:
		break;
	default:
		break;
	}
}
void SnowCone_ToppingSelect::Move()
{
	//�J�[�\���𓮂���
	GetComponent<Image>(selectFrame_).SetPositionAtPixel(IMAGEPOS[selectNum_]);
	if (time_->GetSeconds<float>() >= INTERVAL_TIME)
	{
		time_->Lock();
		time_->Reset();
		state_ = SELECT_STATE::INPUT;
	}
}

void SnowCone_ToppingSelect::Input()
{
	//�g�b�s���O��I��
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_DOWN, 1))
	{

		selectNum_++;
		selectNum_ = selectNum_ % SYRUP_LIMIT;
		state_ = SELECT_STATE::MOVE;
		time_->UnLock();
		Audio::Play(hAudio_CursorMove_);
		GetComponent<Text>(toppingText_).SetText(TOPPING_NAME[selectNum_]);
		((SnowCone_ToppingSumple*)FindObject("SnowCone_ToppingSumple"))->ChangeSumple(selectNum_);
	}
	else if (Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_UP, 1))
	{
		selectNum_--;
		if (selectNum_ < 0)
			selectNum_ = 2;

		selectNum_ = selectNum_ % SYRUP_LIMIT;
		state_ = SELECT_STATE::MOVE;
		time_->UnLock();
		Audio::Play(hAudio_CursorMove_);

		GetComponent<Text>(toppingText_).SetText(TOPPING_NAME[selectNum_]);
		((SnowCone_ToppingSumple*)FindObject("SnowCone_ToppingSumple"))->ChangeSumple(selectNum_);
	}
	//�{�^���������ꂽ��
	else if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A,1))
	{
		Audio::Play(hAudio_PushButton_);
		state_ = SELECT_STATE::STAY;
		GetComponent<Image>(selectFrame_).SetAlpha(1);
		((SnowCone_ToppingUI*)GetParent())->ModeChange(SELECT_MODE::MODE_COMPLETE);
	}
}

void SnowCone_ToppingSelect::UIReset()
{
	//�e�p�����[�^�Ɖ摜���ŏ��̏�Ԃɏ�����
	selectNum_ = 0;
	GetComponent<Image>(selectFrame_).SetPositionAtPixel(IMAGEPOS[selectNum_]);
	GetComponent<Image>(selectFrame_).SetAlpha(0.4f);
	GetComponent<Text>(toppingText_).SetText(TOPPING_NAME[selectNum_]);
	state_ = SELECT_STATE::INPUT;
}

void SnowCone_ToppingSelect::Release()
{
}
