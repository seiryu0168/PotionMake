#include "MenuUI_ReturnHome.h"
#include"Engine/Systems/ImageSystem.h"
#include"Engine/Systems/TextSystem.h"
#include "../Engine/DirectX_11/Input.h"
#include "../InterSceneData.h"

MenuUI_ReturnHome::MenuUI_ReturnHome(Object* parent)
	:UIBase(parent,"MenuUI_ReturnHome")
{
}

MenuUI_ReturnHome::~MenuUI_ReturnHome()
{
}

void MenuUI_ReturnHome::Initialize()
{
	//家に帰るボタン
	Image returnHome(this);
	returnHome.Load("Assets/Image/SelectImage3.png");
	returnHome.SetPosition({ -1.2f,0.5f,0 });
	returnHome.SetRotation({ 0,0,180 });
	//returnHome.SetSize({ 5,2,0 });
	AddComponent<Image>(returnHome);
	XMFLOAT3 textPos = GetComponent<Image>().GetPositionAtPixel();

	//家に帰るテキスト
	Text commandText(this);
	commandText.SetText("家に戻る");
	commandText.SetPosition({ textPos.x + 200,textPos.y - 50 });
	AddComponent<Text>(commandText);
}

void MenuUI_ReturnHome::Start()
{
}

void MenuUI_ReturnHome::Update()
{
	if (GetComponent<Image>().IsHitCursor())
	{
		GetComponent<Image>().SetPosition({ -1.1,0.5,0 });

		if (Input::IsMouseButtonUp(0))
		{
			Audio::Play(hAudio_ReturnHome_);
			SaveItemData();
			FindChild("CloseButton")->KillMe();
			isReturnHome_ = true;
			//newSceneManager::ChangeScene(SCENE_ID::PLAY_MANAGEMENT);
		}

	}
	else
		GetComponent<Image>().SetPosition({ -1.2f,0.5f,0 });
}

void MenuUI_ReturnHome::Release()
{
}
