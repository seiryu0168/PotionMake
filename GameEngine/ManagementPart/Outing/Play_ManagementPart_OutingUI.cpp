#include "Play_ManagementPart_OutingUI.h"
#include"../../Engine/Systems/TextSystem.h"
#include"../../Engine/Systems/ImageSystem.h"
#include"../../Engine/DirectX_11/Input.h"
#include"../../Play_ManagementPart_BaseUI.h"
#include"P_MP_OutingUI_ActionText.h"
#include"../../Engine/newSceneManager.h"
#include"../../P_MP_SettlementUI.h"
#include"../../Engine/ResourceManager/Audio.h"

Play_ManagementPart_OutingUI::Play_ManagementPart_OutingUI(Object* parent)
	:UIBase(parent,"Play_ManagementPart_OutingUI"),
	canCloseUI_(true),
	isOuting_(false),
	time_(0),
	countLimit_(2)
{
}

Play_ManagementPart_OutingUI::~Play_ManagementPart_OutingUI()
{
}

void Play_ManagementPart_OutingUI::Initialize()
{
	Image uiBaseImage(this);
	uiBaseImage.Load("Assets/Image/UIBaseImage1.png");
	AddComponent<Image>(uiBaseImage);

	Image fade(this);
	fade.Load("Assets/Image/PotionManagerUIBase1.png");
	fade.SetColor({ 0,0,0,0 });
	fade.SetSize({ 2,2,0 });
	AddComponent<Image>(fade);

	Text collectionText(this);
	collectionText.SetText("外出");
	collectionText.SetPosition({ 880,300 });
	AddComponent<Text>(collectionText);

	Instantiate<P_MP_OutingUI_ActionText>(this);

	hAudio_OpenDoor_ = Audio::Load("Assets/Audio/OpenDoor01.wav");
}

void Play_ManagementPart_OutingUI::Update()
{

	if (!canCloseUI_)
	{
		time_ += 0.016;
		GetComponent<Image>(1).SetAlpha(time_);
		if (time_ >= countLimit_ && !isOuting_)
		{
			isOuting_ = true;
			Outing(outingNumber_);
		}

		return;
	}
	//クリックしたら
	if (Input::IsMouseButtonDown(0)&& canCloseUI_)
	{
		XMFLOAT3 mousePos = StoreFloat3(Input::GetMousePosition());
		if (!(mousePos.x >= 700.0f && mousePos.x <= 1210.0f &&
			mousePos.y >= 270 && mousePos.y <= 790.0f))
		{
			KillMe();
		}
	}
}

void Play_ManagementPart_OutingUI::Outing(int num)
{
	if (num == 0)
	{
		newSceneManager::ChangeScene(SCENE_ID::PLAY_COLLECTION);
	}
	else if (num == 1)
	{
		Instantiate<P_MP_SettlementUI>(this);
	}
}

void Play_ManagementPart_OutingUI::SetOutNumber(int num)
{
	Audio::Play(hAudio_OpenDoor_);
	outingNumber_ = num;
	GetComponent<Text>().isDraw_ = false;
}

void Play_ManagementPart_OutingUI::Release()
{
	Direct3D::ShowMouseCursor(false);
	XMINT2 rectPos = { (int)(Direct3D::GetScreenWidth() * 0.5f),(int)(Direct3D::GetScreenHeight() * 0.5f) };
	Direct3D::SetClipCursor({ rectPos.x,rectPos.y,rectPos.x + 1,rectPos.y + 1 });
	((Play_ManagementPart_BaseUI*)pParent_)->SetAccessUIFlag(false);
}
