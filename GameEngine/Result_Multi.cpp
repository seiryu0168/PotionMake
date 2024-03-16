#include "Result_Multi.h"
#include "Engine/Components/Text.h"
#include "Engine/Components/Image.h"
#include "Engine/DirectX_11/Input.h"
#include "Engine/newSceneManager.h"
#include"Scenes/RootObject/RootObject_Result.h"
#include "InterSceneData.h"
#include <format>

namespace
{
	static const int DRAW = -1;
}

void Result_Multi::Initialize()
{
	Winner_ = InterSceneData::GetData<int>("ResultData");
	Text text("", "りいてがき筆", { 0,0,500,50 });
	if (Winner_ != DRAW)
		text.SetText(std::format("プレイヤー{:d} Win!", Winner_ + 1));
	else
		text.SetText("DRAW");
	text.SetRatio(0.4f, 0.1f);
	text.SetTextSize(90);
	AddComponent<Text>(text);

	Text t("", "りいてがき筆", { 0,0,500,0 });
	t.SetText("もう一度");
	t.SetRatio(0.75f, 0.65f);
	t.SetTextSize(48);
	AddComponent<Text>(t);

	Text text_("", "りいてがき筆", { 0,0,500,0 });
	text_.SetText("メニューへ");
	text_.SetRatio(0.75f, 0.78f);
	text_.SetTextSize(48);
	AddComponent<Text>(text_);

	Image image;
	image.Load("Assets\\Image\\Buttons\\BTN_A.png", "Result_Multi");
	image.SetLayer(1);
	AddComponent<Image>(image);
	image.Load("Assets\\Image\\Buttons\\BTN_B.png", "Result_Multi");
	AddComponent<Image>(image);

	MoreInfo();
}

void Result_Multi::Update()
{
	if (isChange_ == false)
	{

		switch (Input::GetPadAnyDown())
		{
		case XINPUT_GAMEPAD_A:
			((RootObject_Result*)GetParent())->SceneChange();
			newSceneManager::ChangeScene(SCENE_ID::MENU, 1.0f);
			isChange_ = true;
			break;
		case XINPUT_GAMEPAD_B:
			((RootObject_Result*)GetParent())->SceneChange();
			newSceneManager::ChangeScene(SCENE_ID::PLAY, 1.0f);
			isChange_ = true;
			break;
		default:
			break;
		}
	}
}

void Result_Multi::Draw()
{
}

void Result_Multi::Release()
{
}
