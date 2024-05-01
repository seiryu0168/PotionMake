#include "PotionManagementConfirmButton.h"
#include"../../Engine/Systems/ImageSystem.h"
#include"../../Engine/DirectX_11/Input.h"
#include"P_MP_PotionManagerUI_PotionStockUI.h"
#include"../../Engine/ResourceManager/Audio.h"
PotionManagementConfirmButton::PotionManagementConfirmButton(Object* parent)
	:GameObject(parent,"PotionManagementConfirmButton")
{
}

PotionManagementConfirmButton::~PotionManagementConfirmButton()
{
}

void PotionManagementConfirmButton::Initialize()
{
	//確定ボタンの画像
	Image confirmImage(this);
	confirmImage.Load("Assets/Image/ConfirmButtonImage01.png");
	confirmImage.SetPosition({ -0.7f,-0.7f,0 });
	confirmImage.SetSize({ 0.7f,0.7f,0 });
	AddComponent<Image>(confirmImage);
	hAudio_Confirm_ = Audio::Load("Assets/Audio/Confirm51.wav");
}

void PotionManagementConfirmButton::Start()
{
}

void PotionManagementConfirmButton::Update()
{
	if (Input::IsMouseButtonDown(0) && GetComponent<Image>().IsHitCursor())
	{
		Audio::Play(hAudio_Confirm_);
		//ポーションのデータ管理を始める
		((P_MP_PotionManagerUI_PotionStockUI*)pParent_)->ConfirmPotionManagement();
	}
}

void PotionManagementConfirmButton::Release()
{
}
