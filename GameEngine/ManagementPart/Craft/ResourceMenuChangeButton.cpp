#include "ResourceMenuChangeButton.h"
#include "P_MP_CraftUI_ResourceStockUI.h"
#include "../../Engine/DirectX_11/Input.h"
#include "../../Engine/Systems/ImageSystem.h"
#include "../../Engine/ResourceManager/Audio.h"
ResourceMenuChangeButton::ResourceMenuChangeButton(Object* parent)
	:GameObject(parent,"ResourceMenuChangeButton"),
	hAudio_Change_(-1)
{
}

ResourceMenuChangeButton::~ResourceMenuChangeButton()
{
}

void ResourceMenuChangeButton::Initialize()
{
	{

		Image buttonImage(this);
		buttonImage.Load("Assets/Image/Change_Resource.png");
		buttonImage.SetSize({ 0.2f,0.2f,0 });
		AddComponent<Image>(buttonImage);
	}
	{

		Image buttonImage(this);
		buttonImage.Load("Assets/Image/Change_Process.png");
		buttonImage.SetSize({ 0.2f,0.2f,0 });
		buttonImage.SetColor(0.8f);
		AddComponent<Image>(buttonImage);
	}

	hAudio_Change_ = Audio::Load("Assets/Audio/Confirm34.wav",false,1.0f,6);
}

void ResourceMenuChangeButton::Update()
{
	//画像をクリックしたら
	if (Input::IsMouseButtonDown(0))
	{
		//カーソルが画像に当たっていたら
		if (GetComponent<Image>(0).IsHitCursor())
		{
			GetComponent<Image>(0).SetColor(1);
			GetComponent<Image>(1).SetColor(0.8f);
			Audio::Play(hAudio_Change_);
			((P_MP_CraftUI_ResourceStockUI*)pParent_)->ModeChange(ResourceMenuMode::ResourceSelect);
		}
		else if (GetComponent<Image>(1).IsHitCursor())
		{
			GetComponent<Image>(1).SetColor(1);
			GetComponent<Image>(0).SetColor(0.8f);
			Audio::Play(hAudio_Change_);
			((P_MP_CraftUI_ResourceStockUI*)pParent_)->ModeChange(ResourceMenuMode::ProcessSelect);
		}
	}
}

void ResourceMenuChangeButton::Release()
{
}
