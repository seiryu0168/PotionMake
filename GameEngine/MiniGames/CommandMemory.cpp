#include "CommandMemory.h"
#include "P_CommandMemory.h"
#include "../Engine/Components/Image.h"
#include "../Engine/newSceneManager.h"
#include "../Engine/ResourceManager/Audio.h"
#include "../InterSceneData.h"
#include <Xinput.h>
#include <format>

namespace
{
	static const std::string dir = "Assets\\Image\\Buttons\\";
	static const std::vector<std::string> imageNames_ =
	{
		"BTN_A.png",
		"BTN_B.png",
		"BTN_X.png",
		"BTN_Y.png",
		"BTN_LB.png",
		"BTN_RB.png",
		"STK_L.png",
		"STK_R.png",
		"DIR_D.png",
		"DIR_U.png",
		"DIR_L.png",
		"DIR_R.png"
	};
	static const std::vector<WORD> buttonNames_ =
	{
		XINPUT_GAMEPAD_A,
		XINPUT_GAMEPAD_B,
		XINPUT_GAMEPAD_X,
		XINPUT_GAMEPAD_Y,
		XINPUT_GAMEPAD_LEFT_SHOULDER,
		XINPUT_GAMEPAD_RIGHT_SHOULDER,
		XINPUT_GAMEPAD_LEFT_THUMB,
		XINPUT_GAMEPAD_RIGHT_THUMB,
		XINPUT_GAMEPAD_DPAD_DOWN,
		XINPUT_GAMEPAD_DPAD_UP,
		XINPUT_GAMEPAD_DPAD_LEFT,
		XINPUT_GAMEPAD_DPAD_RIGHT,
	};

	static const float ImageSize = 1.35f;
	static const float MaxSize = 2.35f;
	static const float MaxMove = 30;

	static const std::string Choices = "コマンドを追加してください";
}

CommandMemory::CommandMemory(Object* parent)
	: Framework(parent, "CommandMemory"), cmList_(), NowPlayer_(0), itr_(), text_(nullptr), Images_(),
	now_(NULL), prev_(XINPUT_GAMEPAD_A), RemainingText_(nullptr), choiced_(false), moveCount_(0), hAudio_(-1), state_(STATE::PLAY)
{
}

CommandMemory::~CommandMemory()
{
}

void CommandMemory::Initialize()
{
	Players_ = 2;
	PlayerInitialize<P_CommandMemory>();

	itr_ = cmList_.begin();

	Text text;
	text.SetAlignmentType(ALIGNMENT_TYPE::CENTER_TOP);
	text.SetRect({ 0,0,1100,200 });
	text.SetText(std::format("プレイヤー{:d}のターンです", NowPlayer_ + 1));
	text.SetRatio(0.2f,0);
	AddComponent<Text>(text);

	text_ = &GetComponent<Text>(0);
	ImageLoad();

	Text t;
	t.SetAlignmentType(ALIGNMENT_TYPE::CENTER_TOP);
	t.SetRect({ 0,0,1100,200 });
	t.SetText(Choices);
	t.SetRatio(0.2f, 0.25f);
	AddComponent<Text>(t);
	RemainingText_ = &GetComponent<Text>(1);

	hAudio_ = Audio::Load("Assets\\Audio\\bell.wav", false, 1, 10);
}

void CommandMemory::Update()
{
	if (choiced_)
	{
		float size = (float)std::lerp(ImageSize, MaxSize, ++moveCount_ / MaxMove);
		Images_[now_]->SetSize({ size, size, 1 });
		float alpha = (float)std::lerp(1, 0, moveCount_ / MaxMove);
		Images_[now_]->SetAlpha(alpha);

		if (moveCount_ >= MaxMove)
		{
			choiced_ = false;
			moveCount_ = 0;
		}
	}

	if (state_ == STATE::FINISH)
		Finish();
}

void CommandMemory::Release()
{
}

void CommandMemory::StaticUpdate()
{
	Pause();
}

void CommandMemory::sendCommand(int Button, int Playerid)
{
	//プレイ状態であることを確かめ、
	//操作権を持つプレイヤーか確かめる
	if (state_ == STATE::PLAY && NowPlayer_ == Playerid)
	{
		if (itr_ == cmList_.end())
		{
			choiced_ = true;
			moveCount_ = 0;
			prev_ = now_;
			now_ = Button;

			if (!cmList_.empty())
			{
				Images_[prev_]->SetAlpha(0);
				Images_[prev_]->SetSize({ ImageSize,ImageSize,1 });
			}

			//要素を追加し、イテレータを初期位置に戻す
			cmList_.push_back(Button);
			itr_ = cmList_.begin();

			//プレイヤーの操作権を変更
			if (++NowPlayer_ >= Players_)
				NowPlayer_ = (Players_ - 2);

			text_->SetText(std::format("プレイヤー{:d}のターンです", NowPlayer_ + 1));
			RemainingText_->SetText(std::format("あと{:d}コマンド", cmList_.size() + 1));

			Audio::Play(hAudio_);
		}
		else
		{
			if (*itr_ == Button)
			{
				choiced_ = true;
				moveCount_ = 0;
				prev_ = now_;
				now_ = Button;
				Images_[prev_]->SetAlpha(0);
				Images_[prev_]->SetSize({ ImageSize,ImageSize,1 });
				++itr_;
				RemainingText_->SetText(std::format("あと{:d}コマンド", std::distance(itr_, cmList_.end()) + 1));

				Audio::Play(hAudio_);
			}
			else
			{
				if (++NowPlayer_ >= Players_)
					NowPlayer_ = (Players_ - 2);
				InterSceneData::AddData("ResultData", NowPlayer_);
				//newSceneManager::ChangeScene(SCENE_ID::RESULT);
				GameFinish(true);
				state_ = STATE::FINISH;
			}
		}
	}
}

void CommandMemory::ImageLoad()
{
	Image image;
	image.SetLayer(0);
	{
		image.Load("Assets\\Image\\CM_BG.png", "Command");
		AddComponent(image);
	}

	{
		image.Load("Assets\\Image\\CM_Player_Rev.png", "Command");
		AddComponent(image);
	}

	{
		image.Load("Assets\\Image\\CM_Player.png", "Command");
		AddComponent(image);
	}

	for (int i = 0; i != imageNames_.size(); i++)
	{
		image.Load(dir + imageNames_[i]);
		image.SetAlpha(0);
		image.SetSize({ ImageSize,ImageSize,1 });
		image.SetPosition({ 0,0,0 });
		int hPict = AddComponent(image);
		Images_.insert({ buttonNames_[i], &GetComponent<Image>(hPict)});
	}
}
