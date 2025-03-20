#include "Title.h"
#include"Engine/DirectX_11/Input.h"
#include"Engine/Systems/ImageSystem.h"
#include"Engine/newSceneManager.h"
#include"Engine/Systems/TextSystem.h"
#include "Engine/ResourceManager/AudioManager.h"
#include"TestObject.h"
#include"Easing.h"

namespace
{
	const static int TO_SCENE_CHANGE = 30;	//押されてから画面遷移までのフレーム数
	const static int TO_TEXT_CHANGE = 10;	//文字を点滅させるスパン
}

Title::Title(Object* parent)
	:GameObject(parent, "Title"),
	State_(STATE::WAIT),
	time_(nullptr),
	Frame_(0),
	hAudio_(-1),
	timeF_(0)
{
}

Title::~Title()
{
}

void Title::Initialize()
{

	Image titleImage(this);
	titleImage.Load("Assets/Image/TitleImageEnableTitle.png");
	titleImage.SetSize({ 1.05,1.05,0 });
	AddComponent<Image>(titleImage);

	Image image(this);
	image.Load("Assets/Image/StartButtonImage02.png");
	XMFLOAT3 pos = { 0,-0.5f,0 };
	image.SetPosition(pos);
	image.SetSize({ 1.5,1.5,0 });
	imageNum_=AddComponent<Image>(image);

	Image fadeImage(this);
	fadeImage.Load("Assets/Image/PotionManagerUIBase1.png");
	fadeImage.SetSize({ 2, 2, 0 });
	fadeImage.SetColor({ 0,0,0,0 });
	AddComponent<Image>(fadeImage);

	Text startButtonText(this, "Rounded M+ 1c");
	startButtonText.SetText("スペースキーで始める");
	startButtonText.SetAlignmentType(ALIGNMENT_TYPE::CENTER_CENTER);
	startButtonText.SetRect({ 0,0,512,256 });
	startButtonText.SetTextSize(50);
	startButtonText.SetColor({ 0,0,0,1 });
	//画像位置をテキスト位置に変換
	float w = Direct3D::GetScreenWidth() * 0.5f;
	float h = Direct3D::GetScreenHeight() * 0.5f;
	TEXT_RECT rect = startButtonText.GetRect();
	XMFLOAT2 txtPos = { w + (w * pos.x)-(rect.right*0.5f),h - (h * pos.y)-(rect.bottom*0.5f)-39 };

	startButtonText.SetPosition({ txtPos.x,txtPos.y });
	textNum_ = AddComponent<Text>(startButtonText);
	time_ = std::make_shared<Time::Watch>();

	hAudio_ = AudioManager::Load("Assets/Audio/Confirm47.wav");
}

void Title::Update()
{
	//ボタンの点滅間隔を制御
	{
		float alpha = 0.3f + (sinf(timeF_ * 0.5f) * 0.5f + 0.3f);
		GetComponent<Image>(imageNum_).SetAlpha(alpha);
		GetComponent<Text>(textNum_).SetColor({ 0,0,0,0.3f + alpha });
	}
	timeF_+=0.05f;
	
	//シーン切り替え
	if (time_->GetSeconds<float>() >= 2.0f)
	{
		newSceneManager::ChangeScene(SCENE_ID::PLAY_MANAGEMENT);
	}
	//スペースキーが押されたら
	if(Input::IsKeyDown(DIK_SPACE)&&time_->IsLock())
	{
		AudioManager::Play(hAudio_);
		time_->UnLock();
	}
	else if (!time_->IsLock())
	{
		GetComponent<Image>(2).SetAlpha(time_->GetSeconds<float>());
	}
}

void Title::Release()
{
}

void Title::Waiting()
{
	
}

void Title::Pushed()
{
}