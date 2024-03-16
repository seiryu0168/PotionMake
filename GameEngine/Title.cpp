#include "Title.h"
#include"Engine/DirectX_11/Input.h"
#include"Engine/Systems/ImageSystem.h"
#include"Engine/newSceneManager.h"
#include"Engine/Systems/TextSystem.h"
#include "Engine/ResourceManager/Audio.h"

namespace
{
	const static int TO_SCENE_CHANGE = 30;	//������Ă����ʑJ�ڂ܂ł̃t���[����
	const static int TO_TEXT_CHANGE = 10;	//������_�ł�����X�p��
}

Title::Title(Object* parent)
	:GameObject(parent, "Title"), State_(STATE::WAIT), time_(nullptr), Frame_(0), hAudio_(0)
{
}

Title::~Title()
{
}

void Title::Initialize()
{
	Image image;
	image.Load("Assets/Image/Ennichi_TitleImage.jpg");
	AddComponent<Image>(image);
	
	Text messageText("�{�^���������Ă�������\nPush Any Button", "�肢�Ă����M", {0,0,1100,200});
	messageText.SetAlignmentType(ALIGNMENT_TYPE::CENTER_TOP);
	messageText.SetRatio(0.23f, 0.72f);
	messageText.SetTextSize(100);
	AddComponent<Text>(messageText);

	time_ = std::make_unique<Time::Watch>();
	time_->UnLock();

	hAudio_ = Audio::Load("Assets\\Audio\\festival.wav");
}

void Title::Update()
{
	switch (State_)
	{
	case Title::STATE::WAIT:
		Waiting();
		break;
	case Title::STATE::PUSHED:
		Pushed();
		break;
	default:
		break;
	}

	Audio::Play(hAudio_);
}

void Title::Release()
{
}

void Title::Waiting()
{
	//�����{�^���������ꂽ��
	if (Input::IsPadAnyButtonDown())
	{
		//PUSHED��Ԃɂ��ăV�[���J��
		State_ = STATE::PUSHED;
		newSceneManager::ChangeScene(SCENE_ID::MENU, TO_SCENE_CHANGE);
	}
	GetComponent<Text>().SetColor({ 0,0,0,(sinf(time_->GetSeconds<float>() * 2) * 0.5f) + 0.5f });
}

void Title::Pushed()
{
	GetComponent<Text>().SetColor({ 0,0,0, (float)((++Frame_ % TO_TEXT_CHANGE + 5) / TO_TEXT_CHANGE) });
}