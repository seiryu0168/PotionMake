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

	//ポインターの画像
	Image pointerImage(this);
	pointerImage.Load("Assets/Image/PointerDot.png");
	pointerImage.SetSize({ 0.1f,0.1f,0 });
	AddComponent<Image>(pointerImage);

	//素材名
	Text itemNameText(this);
	itemNameText.SetText("");
	itemNameText.SetRect({ 0,0,500,500 });
	itemNameText.SetPosition({ 1320,500 });
	AddComponent<Text>(itemNameText);

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
	GetComponent<Text>().SetText(itemName_[itemNum]);
	GetComponent<Text>().isDraw_ = true;
}

void Play_CollectionPart_BaseUI::HiddenItemName()
{
	GetComponent<Image>().SetDraw(false);
	GetComponent<Text>().isDraw_=false;
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
