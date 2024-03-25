#include "CloseButton.h"
#include"Engine/Systems/ImageSystem.h"
#include"Engine/DirectX_11/Input.h"
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
	closeImage.SetPosition({ -0.5f,0.8,0 });
	AddComponent<Image>(closeImage);
}

void CloseButton::Start()
{
}

void CloseButton::Update()
{
	if (Input::IsMouseButtonDown(0)&&GetComponent<Image>().IsHitCursor())
	{
		pParent_->KillMe();
	}
}

void CloseButton::Release()
{
}
