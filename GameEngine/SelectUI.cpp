#include "SelectUI.h"
#include"Engine/Systems/ImageSystem.h"
#include"Easing.h"
#include"Engine/DirectX_11/Input.h"
#include"Engine/Systems/TextSystem.h"
#include"Engine/newSceneManager.h"
#include"InterSceneData.h"
#include"Engine/ResourceManager/CsvReader.h"
#include"StaticResource.h"
#include <numbers>
namespace
{
	const static float	MOVE = 0.35f;
	const static int	MAX_MOVE_TIME = 11;
	const static XMFLOAT2  IMAGE_OFFSET = { 0.55f,-0.49f };
	const static float  IMAGE_RATIO = -10.0f;
	const static int	TEXT_SIZE_DEFAULT = 54;
	const static int	TEXT_SIZE_PICKUP = 90;

	//それぞれのテキストの位置
	const static std::map<int, XMFLOAT2> Position = {
		{-2, {0.125f, -0.2f}},
		{-1, {0.125f, 0.15f}},
		{ 0, {0.125f, 0.5f}},
		{ 1, {0.125f, 0.85f}},
		{ 2, {0.125f, 1.2f}},
	};

	const static XMFLOAT3 POSITION_DEFAULT = { -9999,-9999,0 };
	const static std::vector<XMFLOAT3> Arrow_Position = {
		{-0.5f, -0.8f, 1},
		{-0.5f, 0.8f, 1}
	};

	//矢印の動きの周期
	const static int Arrow_Period = 90;
	const static float ARROW_DEFAULT_ALPHA = 0.5f;
}

SelectUI::SelectUI(Object* parent)
	:GameObject(parent, "SelectUI"),
	moveDir_(0),
	state_(SELECT_STATE::STATE_INPUT),
	buttonNum_(0),
	moveTime_(0),
	playCount_(1),
	countTextNum_(-1),
	buttonCount_(0),
	inputInterval_(0),
	Selection_(),
	ArrowFrame_(0),
	ArrowId_()
{
}

SelectUI::~SelectUI()
{
}

void SelectUI::Initialize()
{

	CsvReader reader("Assets/GameDatas/GameData.csv");
	for (int i = 0; i < reader.GetLines(); i++)
	{
		Text text(reader.GetString(i, 0), "りいてがき筆", {0,0,500,50});
		//text.SetText(reader.GetString(i, 0));
		text.SetAlignmentType(ALIGNMENT_TYPE::CENTER_CENTER);
		moveUIList_.push_back((int)AddComponent<Text>(text));
		playerCountList_.push_back(reader.GetInt(i, 2));

		Image image;
		image.Load("Assets\\Image\\"+reader.GetString(i,1));
		AddComponent<Image>(image);

	}

	for (int i = 0; i < moveUIList_.size(); i++)
	{
		GetComponent<Text>(i).SetRatio(Position.at(2).x, Position.at(2).y);
		GetComponent<Text>(i).SetTextSize(TEXT_SIZE_DEFAULT);
		GetComponent<Image>(i).SetPosition(POSITION_DEFAULT);
		basePosList_.push_back(POSITION_DEFAULT);
	}

	Selection_[-2] = moveUIList_.end() - 2;
	Selection_[-1] = moveUIList_.end() - 1;
	Selection_[0] = moveUIList_.begin();
	Selection_[1] = Selection_[0] + 1;
	Selection_[2] = Selection_[1] + 1;
	buttonNum_ = *Selection_[0];

	int num = InterSceneData::GetData<int>("GameNumber");

	while (*Selection_[0] != num)
		ItrIncrement();

	GetComponent<Text>(buttonNum_).SetTextSize(TEXT_SIZE_PICKUP);

	ArrowLoad();

	UIPositioning();

	timer_ = std::make_shared<Time::Watch>();
	filterNum_ = AddComponent<Image>(StaticResource::GetImage("Filter"));
}
void SelectUI::Input()
{
	//ボタンの処理
	moveDir_ = 0;

	//上に移動
	if (Input::IsPadButton(XINPUT_GAMEPAD_DPAD_UP) || Input::GetLStick_Y() > 0)
	{
		moveDir_ = 1;

		GetComponent<Text>(buttonNum_).SetTextSize(TEXT_SIZE_DEFAULT);
		state_ = SELECT_STATE::STATE_MOVE;

		//矢印を明るくする
		GetComponent<Image>(ArrowId_[1]).SetAlpha(1);
		
		ItrIncrement();
	}
	//下に移動
	else if (Input::IsPadButton(XINPUT_GAMEPAD_DPAD_DOWN) || Input::GetLStick_Y() < 0)
	{
		moveDir_ = -1;

		GetComponent<Text>(buttonNum_).SetTextSize(TEXT_SIZE_DEFAULT);
		state_ = SELECT_STATE::STATE_MOVE;

		//矢印を明るくする
		GetComponent<Image>(ArrowId_[0]).SetAlpha(1);

		ItrDecrement();
	}
	else if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A))
	{
		PushedButton(buttonNum_);
	}
}

void SelectUI::Move()
{
	moveTime_++;
	moveTime_ = min(moveTime_, MAX_MOVE_TIME);
	//動き終わったか
	if (moveTime_ >= MAX_MOVE_TIME)
	{
		state_ = SELECT_STATE::STATE_INPUT;
		moveTime_ = 0;
		//動かしたセレクト画面の位置を確定させる
		for (XMFLOAT3& i : basePosList_)
		{
			i.y += MOVE * moveDir_;
		}
		GetComponent<Text>(buttonNum_).SetTextSize(TEXT_SIZE_PICKUP);

		for (int i = 0; i < std::size(ArrowId_); i++)
			GetComponent<Image>(ArrowId_[i]).SetAlpha(ARROW_DEFAULT_ALPHA);

		UIPositioning();
		return;
	}
	//セレクト画面を動かす
	MoveButton(Easing::EaseInCubic((float)moveTime_ / (float)(MAX_MOVE_TIME - 1)));
}

void SelectUI::Selected()
{
	//画面を暗転
	float ratio = timer_->GetSeconds<float>();
	GetComponent<Image>(filterNum_).SetAlpha(ratio);
	//1秒たったらシーン切り替え
	if ( ratio >= 1.0f)
	{
		newSceneManager::ChangeScene(SCENE_ID::PLAY);
	}
}

void SelectUI::Update()
{
	ArrowMove();

	switch (state_)
	{
	case SELECT_STATE::STATE_INPUT:
		Input();
		break;
	case SELECT_STATE::STATE_MOVE:
		Move();
		break;
	case SELECT_STATE::STATE_SELECTED:
		Selected();
		break;
	default:
		break;
	}
}

void SelectUI::MoveButton(float ratio)
{
	//ボタンとゲームの画像を上下に動かす
	float delta = MOVE * ratio * moveDir_;
	for (auto&& itr : Selection_)
	{
		GetComponent<Image>(*itr.second).
			SetPosition({ -basePosList_[*itr.second].x + IMAGE_OFFSET.x,
								 (basePosList_[*itr.second].y + IMAGE_OFFSET.y + delta) * IMAGE_RATIO,
								  basePosList_[*itr.second].z });
		GetComponent<Text>(*itr.second).
			SetRatio(basePosList_[*itr.second].x,
				basePosList_[*itr.second].y + delta);
	}
}

void SelectUI::PushedButton(int buttonNum)
{
	//選んだゲームの情報とプレイヤー数を保存
	InterSceneData::DeleteData<int>("PlayerCount");
	InterSceneData::DeleteData<int>("GameNumber");
	InterSceneData::AddData<int>("PlayerCount", playerCountList_[buttonNum_]);
	InterSceneData::AddData<int>("GameNumber", buttonNum_);
	//ゲーム選んだので状態をSTATE_SELECTEDにする
	state_ = SELECT_STATE::STATE_SELECTED;
	timer_->UnLock();
	GetComponent<Image>(filterNum_).SetDraw(true);
}

void SelectUI::Release()
{
}

void SelectUI::ItrIncrement()
{
	Selection_[2] = Selection_[1];
	Selection_[1] = Selection_[0];
	Selection_[0] = Selection_[-1];
	Selection_[-1] = Selection_[-2];
	if (Selection_[-2] == begin(moveUIList_))
		Selection_[-2] = moveUIList_.end();
	--Selection_[-2];

	buttonNum_ = *Selection_[0];
}

void SelectUI::ItrDecrement()
{
	Selection_[-2] = Selection_[-1];
	Selection_[-1] = Selection_[0];
	Selection_[0] = Selection_[1];
	Selection_[1] = Selection_[2];
	if (++Selection_[2] == end(moveUIList_))
		Selection_[2] = moveUIList_.begin();

	buttonNum_ = *Selection_[0];
}

void SelectUI::UIPositioning()
{
	for (int i = -2; i <= 2; i++)
	{
		GetComponent<Text>(*Selection_[i]).SetRatio(Position.at(i).x, Position.at(i).y);
		basePosList_[*Selection_[i]] = { Position.at(i).x, Position.at(i).y, 0 };
		GetComponent<Image>(*Selection_[i]).
			SetPosition({ -Position.at(i).x + IMAGE_OFFSET.x,
								 (Position.at(i).y + IMAGE_OFFSET.y) * IMAGE_RATIO, 0 });
	}
}

void SelectUI::ArrowLoad()
{
	Image i;
	i.Load("Assets\\Image\\Select_Arrow.png");
	i.SetPosition(Arrow_Position[0]);
	i.SetAlpha(ARROW_DEFAULT_ALPHA);
	ArrowId_[0] = (int)AddComponent<Image>(i);

	Image image;
	image.Load("Assets\\Image\\Select_Arrow.png");
	image.SetPosition(Arrow_Position[1]);
	image.SetRotation({ 0,0,180 });
	image.SetAlpha(ARROW_DEFAULT_ALPHA);
	ArrowId_[1] = (int)AddComponent<Image>(image);
}

void SelectUI::ArrowMove()
{
	if (++ArrowFrame_ > Arrow_Period)
		ArrowFrame_ -= Arrow_Period;
	float y = std::sinf(ArrowFrame_ * std::numbers::pi_v<float> / Arrow_Period) * 0.05f;
	XMFLOAT3 pos = Arrow_Position[0];
	pos.y -= y;
	GetComponent<Image>(ArrowId_[0]).SetPosition(pos);

	pos = Arrow_Position[1];
	pos.y += y;
	GetComponent<Image>(ArrowId_[1]).SetPosition(pos);
}
