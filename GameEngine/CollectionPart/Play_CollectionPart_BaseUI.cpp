#include "Play_CollectionPart_BaseUI.h"
#include "Play_CollectionPart_StageManager.h"
#include "P_CP_MenuUI.h"
#include "../Engine/Systems/TextSystem.h"
#include "../Engine/Systems/ImageSystem.h"
#include "../InterSceneData.h"
#include "../Engine/DirectX_11/Input.h"
#include "../Player_CollectionPart.h"
#include "../Engine/ResourceManager/AudioManager.h"

namespace
{
	RECT clipRange;
}

Play_CollectionPart_BaseUI::Play_CollectionPart_BaseUI(Object* parent)
	:GameObject(parent, "Play_CollectionPart_BaseUI"),
	isUIOpened_(false),
	player_(nullptr),
	hAudio_UIOpen_(-1)
{
}

Play_CollectionPart_BaseUI::~Play_CollectionPart_BaseUI()
{
}

void Play_CollectionPart_BaseUI::Initialize()
{
	XMINT2 range = { (int)(Direct3D::GetScreenWidth() * 0.5f),(int)(Direct3D::GetScreenHeight() * 0.5f) };
	clipRange = { range.x,range.y,range.x+1,range.y+1 };
	Direct3D::SetClipCursor(clipRange);
	Direct3D::ShowMouseCursor(false);
	
	//拾える素材を表示する背景画像
	Image actionImage(this);
	actionImage.Load("Assets/Image/SelectImage3.png");
	actionImage.SetPosition({ 0.7f,-0.015f,0 });
	actionImage.SetSize({ 0.7,0.7f,0 });
	AddComponent<Image>(actionImage);

	//素材名
	Text itemNameText(this, "Rounded M+ 1c");
	itemNameText.SetText("");
	itemNameText.SetRect({ 0,0,500,500 });
	itemNameText.SetTextSize(55);
	itemNameText.SetPosition({ 1350,505 });
	AddComponent<Text>(itemNameText);

	//押すキーの画像
	Image buttonImage(this);
	buttonImage.Load("Assets/Image/Circle.png");
	buttonImage.SetPosition({ 0.37f,-0.015f,0 });
	buttonImage.SetSize({ 0.5f,0.5f,0 });
	AddComponent<Image>(buttonImage);

	XMFLOAT3 buttonTextPos = buttonImage.GetPositionAtPixel();
	Text buttonText(this, "Rounded M+ 1c");
	buttonText.SetText("F");
	buttonText.SetColor({ 0,0,0,1 });
	buttonText.SetTextSize(40);
	buttonText.SetRect({ 0,0,40,40 });
	buttonText.SetPosition({ buttonTextPos.x - 10,buttonTextPos.y - 30 });
	AddComponent<Text>(buttonText);

	//ポインターの画像
	Image pointerImage(this);
	pointerImage.Load("Assets/Image/PointerDot.png");
	pointerImage.SetSize({ 0.1f,0.1f,0 });
	AddComponent<Image>(pointerImage);


	hAudio_UIOpen_ = AudioManager::Load("Assets/Audio/Confirm29.wav");
}

void Play_CollectionPart_BaseUI::Start()
{
	itemName_ = ((Play_CollectionPart_StageManager*)FindObject("Play_CollectionPart_StageManager"))->GetItemNameList();
	player_ = (Player_CollectionPart*)FindObject("Player_CollectionPart");
}

void Play_CollectionPart_BaseUI::Update()
{
	//UIが開かれていなければEscキーでメニューを開く
	if (Input::IsKeyDown(DIK_ESCAPE)&&!isUIOpened_)
	{
		AudioManager::Play(hAudio_UIOpen_);
		Instantiate<P_CP_MenuUI>(this);
		HiddenItemName();
		SetUIOpenFlag(true);
	}
}

void Play_CollectionPart_BaseUI::DisplayItemName(int itemNum)
{	
	//アイテム番号を使ってアイテム名を表示
	GetComponent<Image>().SetDraw(true);
	GetComponent<Image>(1).SetDraw(true);
	GetComponent<Text>().SetText(itemName_[itemNum]);
	GetComponent<Text>().isDraw_ = true;
	GetComponent<Text>(1).isDraw_ = true;
}

void Play_CollectionPart_BaseUI::HiddenItemName()
{
	GetComponent<Image>().SetDraw(false);
	GetComponent<Image>(1).SetDraw(false);
	GetComponent<Text>().isDraw_=false;
	GetComponent<Text>(1).isDraw_=false;
}

void Play_CollectionPart_BaseUI::SetUIOpenFlag(bool flag)
{
	isUIOpened_ = flag;
	player_->SetControllFlag(!flag);

	//メニューUIを閉じる
	if (!flag)
	{
		Direct3D::SetClipCursor(clipRange);
		Direct3D::ShowMouseCursor(false);
	}
	//メニューUIを開く
	else
	{
		Direct3D::SetClipCursor();
		Direct3D::ShowMouseCursor(true);
	}
}

void Play_CollectionPart_BaseUI::Release()
{
}
