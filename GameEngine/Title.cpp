#include "Title.h"
#include"Engine/DirectX_11/Input.h"
#include"Engine/Systems/ImageSystem.h"
#include"Engine/newSceneManager.h"
#include"Engine/Systems/TextSystem.h"
#include "Engine/ResourceManager/Audio.h"
#include"TestObject.h"
#include"Engine/ResourceManager/Audio.h"

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
	Image image(this);
	image.Load("Assets/Image/StartButtonImage.png");
	XMFLOAT3 pos = { 0,-0.5f,0 };
	image.SetPosition(pos);
	AddComponent<Image>(image);

	Image fadeImage(this);
	fadeImage.Load("Assets/Image/PotionManagerUIBase1.png");
	fadeImage.SetSize({ 2, 2, 0 });
	fadeImage.SetColor({ 0,0,0,0 });
	AddComponent<Image>(fadeImage);

	time_ = std::make_shared<Time::Watch>();

	hAudio_ = Audio::Load("Assets/Audio/Confirm47.wav");

	//Instantiate<TestObject>(this);

}

void Title::Update()
{
	if (time_->GetSeconds<float>() >= 2.0f)
	{
		newSceneManager::ChangeScene(SCENE_ID::PLAY_MANAGEMENT);
	}
	if(Input::IsKeyDown(DIK_SPACE)&&time_->IsLock())
	{
		Audio::Play(hAudio_);
		time_->UnLock();
	}
	else if (!time_->IsLock())
	{
		GetComponent<Image>(1).SetAlpha(time_->GetSeconds<float>());
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