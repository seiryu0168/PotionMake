#include "Title.h"
#include"Engine/DirectX_11/Input.h"
#include"Engine/Systems/ImageSystem.h"
#include"Engine/newSceneManager.h"
#include"Engine/Systems/TextSystem.h"
#include "Engine/ResourceManager/Audio.h"
//#include"TestObject.h"

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
	hAudio_(0),
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

	//Instantiate<TestObject>(this);

}

void Title::Update()
{
	timeF_ += 2.0f;
	GetComponent<Image>().SetRotation({ 0,0,timeF_ });
	if(Input::IsKeyDown(DIK_SPACE))
	{
		newSceneManager::ChangeScene(SCENE_ID::PLAY_COLLECTION);
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