#include "SnowConeMaker_Shave.h"
#include"../Engine/GameObject/CameraManager.h"
#include"../Engine/DirectX_11/Input.h"
#include"SnowCone_Cup.h"
#include"SnowConeMaking.h"
#include"../Engine/Systems/ImageSystem.h"
#include"../Engine/ResourceManager/Audio.h"
namespace
{
	const XMVECTOR DEFAULT_POS = XMVectorSet(-40, 8, -40, 0);
	const float SNOWCONE_SIZE_DELTA = 0.01f;
	const float SNOWCONE_SIZE_LIMIT = 4.0f;
	const float INPUT_INTERVAL = 0.3f;
}

SnowConeMaker_Shave::SnowConeMaker_Shave(Object* parent)
	:GameObject(parent, "SnowConeMaker_Shave"),
	snowConeSize_(0.0f),
	playerNum_(0),
	snowCone_(nullptr),
	hAudio_Shave_(-1)
{
}

SnowConeMaker_Shave::~SnowConeMaker_Shave()
{
}

void SnowConeMaker_Shave::Initialize()
{
	transform_->position_ = DEFAULT_POS;
	CameraManager::GetCamera(playerNum_+1).SetPosition(transform_->position_);
	snowCone_ = Instantiate<SnowCone_Cup>(GetParent());// = std::make_shared<SnowCone_Cup>(GetParent());
	CameraManager::GetCamera(playerNum_+1).SetTarget(XMVectorSet(-40,0,-30,0));

	{

		Image image(playerNum_+1);
		image.Load("Assets/Image/SnowCone_ShaveMeterImage.png");
		image.SetPositionAtPixel({ 1700,-512,0 });
		image.SetSize({ 0.5f,snowConeSize_,0 });
		AddComponent<Image>(image);
	}
	{

		Image image(playerNum_+1);
		image.Load("Assets/Image/SnowCone_ShaveMeterFrameImage.png");
		image.SetPositionAtPixel({ 1700,0,0 });
		image.SetSize({ 0.5f,1.0f,0 });
		AddComponent<Image>(image);
	}
	timer_ = std::make_shared<Time::Watch>();
	timer_->UnLock();
	hAudio_Shave_ = Audio::Load("Assets/Audio/kakigori_machine.wav");
	assert(hAudio_Shave_>=0);
}

void SnowConeMaker_Shave::Update()
{
	//V‚µ‚¢‚©‚«•X‚ðì¬(Œ³X‚ ‚Á‚½‚©‚«•X‚Í”jŠü)
	switch (Input::GetPadAnyDown(playerNum_))
	{
	case XINPUT_GAMEPAD_X:
		if (snowCone_)
		{
			snowCone_->RemoveIce();
			snowCone_->KillMe();
		}

		snowCone_ = Instantiate<SnowCone_Cup>(GetParent());
		snowConeSize_ = 0.0f;
		GetComponent<Image>().SetSize({ 0.5f,snowConeSize_,0 });
		break;
	case XINPUT_GAMEPAD_A:
		//‚©‚«•X‚ðƒXƒgƒbƒN‚ÉˆÚ“®
		if (timer_->GetSeconds<float>() >= INPUT_INTERVAL)
		{
			if (snowCone_)
			{
				//snowCone_->SetConeSize(snowConeSize_);
				snowCone_->StartEasing();
				//snowCone_->ChangeDrawTarget(2);
				((SnowConeMaking*)GetParent())->AddCup(snowCone_);
				snowCone_ = nullptr;
			}
			timer_->SetSecond(0);
		}
		break;

	default:
		if (Input::IsPadButton(XINPUT_GAMEPAD_B) && snowCone_ && snowConeSize_ < SNOWCONE_SIZE_LIMIT)
		{
			Shave();
			Audio::Play(hAudio_Shave_);
		}
		else
			Audio::Stop(hAudio_Shave_);
		break;
	}
}

void SnowConeMaker_Shave::Shave()
{
		snowCone_->SetConeSize(SNOWCONE_SIZE_DELTA* 0.3f);
		snowConeSize_ += SNOWCONE_SIZE_DELTA;
		GetComponent<Image>().SetSize({ 0.5f,snowConeSize_,0 });
}

void SnowConeMaker_Shave::Release()
{
}
