#include "Result_Shooting.h"
#include"../InterSceneData.h"
#include"../Engine/Systems/TextSystem.h"
#include"../Engine/Systems/ImageSystem.h"
#include"../Engine/ResourceManager/json.hpp"
#include"../Scenes/RootObject/RootObject_Result.h"
#include<fstream>
#include"../Engine/DirectX_11/Input.h"
#include"../Engine/newSceneManager.h"

namespace
{
	const float SHOWTIME = 3.0f;
	const XMFLOAT2 RETURN_TEXT_POS = { 750,700 };
	const int MAX_SCORE = 30;
}

Result_Shooting::Result_Shooting(Object* parent)
	:Result_Single(parent,"Result_Shooting"),
	status_(CountStatus::STAY),
	count_(0),resultTextNum_(0),
	interval_(0),
	isChange_(false)
{
}

Result_Shooting::~Result_Shooting()
{
}

void Result_Shooting::Initialize()
{
	time_ = std::make_unique<Time::Watch>();
	time_->UnLock();
	//テキストの用意
	Text text("結果", "りいてがき筆", { 0,0,200,50 });
	text.SetPosition({ 750,0 });
	text.SetTextSize(100);
	AddComponent<Text>(text);

	//リザルトを取得
	score_ = InterSceneData::GetData<int>("ResultData");
	if (score_ >= MAX_SCORE)
	{
		Text text("Perfect!!", "りいてがき筆", { 0,0,500,50 });
		text.SetColor({ 0, 0, 0, 0 });
		text.SetPosition({ 1200,500 });
		perfectTextNum_ = AddComponent<Text>(text);
	}
	Text scoreText("落とした数 0 個", "りいてがき筆", {0,0,600,50});
	scoreText.SetPosition( {500,500 });
	resultTextNum_ = AddComponent<Text>(scoreText);
	{
		Image image;
		image.Load("Assets/Image/SelectUI_Shooting_BackGroundImage.jpg");
		AddComponent<Image>(image);
	}

	interval_ = Clamp<float>((SHOWTIME / (float)score_),0.2f,1.0f);
}

void Result_Shooting::Update()
{
	//今の状態によって挙動が変わる
	//STAY	 : 止めておく
	//SHOW	 : リザルト表示
	//FINISH : 入力
	switch (status_)
	{
	case CountStatus::STAY:
		Stay();
		break;
	case CountStatus::SHOW:
		ShowResult();
		break;
	case CountStatus::FINISH:
		Finish();
		break;
	}
}

void Result_Shooting::Stay()
{
	if (time_->GetSeconds<float>() >= 1.0f)
		status_ = CountStatus::SHOW;
}

void Result_Shooting::ShowResult()
{
	//スコアを数える(count_)
	if ((interval_ * count_) <= time_->GetSeconds<float>()-1.0f)
	{
		count_++;
		GetComponent<Text>(resultTextNum_).SetText("落とした数 " + std::to_string(count_)+" 個");
	}
	//カウントがスコア以上になったらカウントをやめてFINISH状態に移行
	if (count_ >= score_)
	{
		GetComponent<Text>(resultTextNum_).SetText("落とした数 " + std::to_string(score_)+" 個");
		if (score_ >= MAX_SCORE)
		{
			GetComponent<Text>(perfectTextNum_).SetColor({ 1,0,0,1 });

		}
		//時間を止める
		time_->Lock();
		ShowCommand();
		status_ = CountStatus::FINISH;
	}
}

void Result_Shooting::ShowCommand()
{
	//セレクト画面に戻るかもう一回やるかの文字とコマンド表示
	Text retryText("もう一度", "りいてがき筆", { 0,0,500,50 });
	retryText.SetRatio(0.7f, 0.65f);
	retryText.SetTextSize(48);
	AddComponent<Text>(retryText);

	Text toMenuText_("メニューへ", "りいてがき筆", { 0,0,500,50 });
	toMenuText_.SetRatio(0.7f, 0.78f);
	toMenuText_.SetTextSize(48);
	AddComponent<Text>(toMenuText_);

	{
		Image image;
		image.Load("Assets\\Image\\Buttons\\BTN_A.png", "Result_Multi");
		AddComponent<Image>(image);
	}
	{
		Image image;
		image.Load("Assets\\Image\\Buttons\\BTN_B.png", "Result_Multi");
		AddComponent<Image>(image);
	}
}

void Result_Shooting::Finish()
{
	//セレクト画面に戻るかもう一回やるか選択
	if (isChange_ == false)
	{

		if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A))
		{
			isChange_ = true;
			((RootObject_Result*)GetParent())->SceneChange();
			newSceneManager::ChangeScene(SCENE_ID::MENU, 1.0f);
		}
		else if (Input::IsPadButtonDown(XINPUT_GAMEPAD_B))
		{
			isChange_ = true;
			((RootObject_Result*)GetParent())->SceneChange();
			newSceneManager::ChangeScene(SCENE_ID::PLAY, 1.0f);
		}
	}
}

void Result_Shooting::Release()
{
}
