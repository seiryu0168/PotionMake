#include "CloseButton.h"
#include "Engine/Systems/ImageSystem.h"
#include "Engine/DirectX_11/Input.h"
#include "Engine/ResourceManager/Audio.h"
CloseButton::CloseButton(Object* parent)
	:GameObject(parent,"CloseButton")
{
}

CloseButton::~CloseButton()
{
}

void CloseButton::Initialize()
{
	Image closeImage(this);
	closeImage.Load("Assets/Image/CloseButtonImage.png");
	closeImage.SetPosition({ -0.95f,0.9f,0 });
	closeImage.SetSize({ 0.6f,0.6f,0 });
	AddComponent<Image>(closeImage);

	hAudio_Close_ = Audio::Load("Assets/Audio/Cancel09.wav");
}

void CloseButton::Start()
{
}

void CloseButton::Update()
{
	if (Input::IsMouseButtonDown(0)&&GetComponent<Image>().IsHitCursor())
	{
		Audio::Play(hAudio_Close_);
		pParent_->KillMe();
	}
}

void CloseButton::Release()
{
}
