#include "Framework.h"
#include "../Engine/DirectX_11/Input.h"
#include "../Engine/Brightness.h"
#include "../Engine/newSceneManager.h"
#include"../StaticResource.h"
#include <map>

namespace
{
	static const std::vector<std::string> MENULIST =
	{
		"戻る",
		"はじめから",
		"メニューへ"
	};

	static const std::vector<XMFLOAT2> MENUPOS =
	{
		{0.1f, 0.85f}, {0.35f, 0.85f}, {0.7f, 0.85f}
	};

	static const int TEXTSIZE = 72;
	static const int SELECTSIZE = 96;

	//選んでいる番号
	const enum SELECT
	{
		RETURN = 0,
		RESTART,
		TO_MENU
	};

	//シーンを変更するためのインターバル
	static const int TO_SCENE_CHANGE = 90;

	//値に応じてシーンを変更するためのコンテナ
	static const std::map<int, SCENE_ID> CHANGE_SCENE =
	{
		{RESTART, SCENE_ID::PLAY},
		{TO_MENU, SCENE_ID::MENU}
	};
	
	//ポーズ状態の時の背景の暗さ
	static const float DARKNESS = 0.6f;
}

Framework::Framework(Object* parent, const std::string& name)
	: Object(parent, name), Players_(1), GameTime_(), MenuTexts_(), Select_(0), CallPause_(false), Privilege_(1), Frame_(0), nowState_(STATE::PLAY)
{
	AddComponent<Image>(StaticResource::GetImage("GameFinishImage"));
	Load();
}

Framework::~Framework()
{
}

void Framework::Draw()
{
	if (!isUpdate_)
	{
		Brightness::Draw();
		for (auto&& i : MenuTexts_)
		{
			i.Draw();
		}
	}
}

void Framework::PauseMenu()
{
	//いずれかのプレイヤーがStartボタンを押すと状態が切り替わる
	if (int push = Input::IsAnyPadDown(XINPUT_GAMEPAD_START); push != NO_PUSHING)
	{
		Privilege_ = push;
		CallPause_ = isUpdate_;
		SetUpdate(!isUpdate_);

		if (isUpdate_)
		{
			Brightness::SetRatio(0);
			nowState_ = STATE::PLAY;
		}
		else
		{
			Brightness::SetRatio(DARKNESS);
			MenuTexts_[0].SetTextSize(SELECTSIZE);
			nowState_ = STATE::PAUSE;
		}
	}
}

void Framework::Conduct()
{
	switch (Select_)
	{
		//戻るが押されたとき
	case SELECT::RETURN:
		CallPause_ = isUpdate_;
		SetUpdate(!isUpdate_);

		Brightness::SetRatio(0);

		nowState_ = STATE::PLAY;
		break;

		//はじめから,或いはメニューへが押されたとき
	case SELECT::RESTART:
	case SELECT::TO_MENU:
		newSceneManager::ChangeScene(CHANGE_SCENE.at(Select_), TO_SCENE_CHANGE);
		nowState_ = STATE::SCENE_CHANGE;
		break;

	default:
		break;
	}
}

void Framework::Load()
{
	for (int i = 0; i < MENULIST.size(); i++)
	{
		Text countText(MENULIST[i], "りいてがき筆", {0,0,600,50});
		countText.SetRatio(MENUPOS[i].x, MENUPOS[i].y);
		countText.SetTextSize(TEXTSIZE);
		MenuTexts_.push_back(countText);
	}
}

void Framework::State_Pause()
{
	//Dパッドの左右で選択
	switch (Input::GetPadOnlyDown(Privilege_))
	{
	case XINPUT_GAMEPAD_DPAD_RIGHT:
		MenuTexts_[Select_].SetTextSize(TEXTSIZE);
		if (++Select_ >= MenuTexts_.size())
			Select_ -= MenuTexts_.size();

		MenuTexts_[Select_].SetTextSize(SELECTSIZE);
		break;

	case XINPUT_GAMEPAD_DPAD_LEFT:
		MenuTexts_[Select_].SetTextSize(TEXTSIZE);
		if (--Select_ < 0)
			Select_ += MenuTexts_.size();

		MenuTexts_[Select_].SetTextSize(SELECTSIZE);
		break;

	case XINPUT_GAMEPAD_A:
		Conduct();
		break;

	default:
		break;
	}
}

void Framework::State_SceneChange()
{
	Brightness::SetRatio(DARKNESS + (float)std::lerp(0, 1 - DARKNESS, ++Frame_ / (float)TO_SCENE_CHANGE));
	for (auto&& i : MenuTexts_)
	{
		i.SetColor({ 1,1,1,(float)std::lerp(1, 0, ++Frame_ / (float)TO_SCENE_CHANGE) });
	}
}

void Framework::Finish()
{
	GetComponent<Image>().SetPosition({ 0,2.0f-Clamp<float>(2.0f*((float)++Frame_ / TO_SCENE_CHANGE)*1.4f,0.0f,2.0f),0});

	if (Frame_ >= TO_SCENE_CHANGE)
	{
		newSceneManager::ChangeScene(SCENE_ID::RESULT);
	}
}

void Framework::GameFinish(bool isFinish)
{
	isFinish_ = isFinish;
	GetComponent<Image>().SetDraw(isFinish_);
}

void Framework::Pause()
{
	switch (nowState_)
	{
	case STATE::PLAY:
		PauseMenu();
		break;
	case STATE::PAUSE:
		PauseMenu();
		State_Pause();
		break;
	case STATE::SCENE_CHANGE:
		State_SceneChange();
		break;
	default:
		break;
	}
}