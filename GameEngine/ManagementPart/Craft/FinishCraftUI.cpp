#include "FinishCraftUI.h"
#include "../../Engine/Systems/ImageSystem.h"
#include "../../Engine/DirectX_11/Input.h"
#include "../../InterSceneData.h"
#include "../../PlayerData.h"
#include "../../Engine/Systems/TextSystem.h"
#include "../../Engine/ResourceManager/AudioManager.h"
FinishCraftUI::FinishCraftUI(Object* parent)
	:GameObject(parent,"FinishCraftUI"),
	okButtonImageNum_(-1),
	uiPos_({ 0,0,0 })
{
}

FinishCraftUI::~FinishCraftUI()
{
}

void FinishCraftUI::Initialize()
{
	CreateBase();
	
	//ポーションのデータを取得
	PlayerData* data = InterSceneData::GetData<PlayerData>("Data01");
	PlayerData::PotionData pData = data->potionDataList_[data->potionDataList_.size() - 1];
	
	//ポーションのボトル部分の画像
	Image potionImage(this);
	potionImage.Load("Assets/Image/Potion_BaseImage.png");
	potionImage.SetPosition({ 0, 0.3f, 0 });
	potionImage.SetLayer(2);
	potionImage.SetColor(pData.potionColor_);
	AddComponent<Image>(potionImage);
	
	//ポーションの縁の画像
	Image edgeImage(this);
	edgeImage.Load("Assets/Image/Potion_EdgeImage.png");
	edgeImage.SetPosition({ 0,0.3f,0 });
	edgeImage.SetLayer(2);
	AddComponent<Image>(edgeImage);

	//ポーションの名前
	Text potionNameText(this);
	potionNameText.SetRect({ 0,0,1000,200 });
	potionNameText.SetAlignmentType(ALIGNMENT_TYPE::CENTER_TOP);
	potionNameText.SetColor({ 0,0,0,1 });
	potionNameText.SetLayer(2);
	potionNameText.SetText(pData.potionName_);
	potionNameText.SetPosition({ 500,600 });
	AddComponent<Text>(potionNameText);

	//OKボタンの画像
	Image OKImage(this);
	OKImage.Load("Assets/Image/ButtonImage02.png");
	OKImage.SetPosition({ 0,-0.6f,0 });
	OKImage.SetLayer(2);
	okButtonImageNum_ = AddComponent<Image>(OKImage);

	Text OKText(this);
	OKText.SetText("OK");
	OKText.SetLayer(2);
	OKText.SetPosition({ 900,840 });
	AddComponent<Text>(OKText);

	hAudio_Success_ = AudioManager::Load("Assets/Audio/Success01.wav");
	AudioManager::Play(hAudio_Success_);
}

void FinishCraftUI::Start()
{
}

void FinishCraftUI::Update()
{
	//OKボタンをクリックしたら
	if (Input::IsMouseButtonDown(0) && GetComponent<Image>(okButtonImageNum_).IsHitCursor())
	{
		pParent_->KillMe();
	}
}

void FinishCraftUI::CreateBase()
{
	XMFLOAT3 windowSize;
	XMFLOAT3 imageRatio;
	float edgeSize = 1.0f;
	Image uiBaseImage(this);
	uiBaseImage.Load("Assets/Image/UIBaseImage2.png");
	uiBaseImage.SetPosition({ uiPos_.x,uiPos_.y,0 });
	uiBaseImage.SetSize({ 16.0f*(Direct3D::GetScreenWidth() /1024.0f), 16.0f*(Direct3D::GetScreenHeight()/ 1024.0f), 0});
	uiBaseImage.SetLayer(2);
	windowSize = uiBaseImage.GetSizeAtPixel();
	imageRatio = uiBaseImage.GetSize();
	AddComponent<Image>(uiBaseImage);

	windowSize = { windowSize.x / (Direct3D::GetScreenWidth()),
				   windowSize.y / (Direct3D::GetScreenHeight()),0 };
	Image uiWidthEdgeImage1(this);
	uiWidthEdgeImage1.Load("Assets/Image/UIEdge_Width.png");
	uiWidthEdgeImage1.SetPosition({ uiPos_.x,uiPos_.y + windowSize.y * 0.9f,0 });
	uiWidthEdgeImage1.SetSize({ imageRatio.x * 0.95f,edgeSize,0 });
	uiWidthEdgeImage1.SetLayer(2);
	AddComponent<Image>(uiWidthEdgeImage1);
	Image uiWidthEdgeImage2(this);
	uiWidthEdgeImage2.Load("Assets/Image/UIEdge_Width.png");
	uiWidthEdgeImage2.SetPosition({ uiPos_.x,uiPos_.y - windowSize.y * 0.9f,0 });
	uiWidthEdgeImage2.SetSize({ imageRatio.x * 0.95f,edgeSize,0 });
	uiWidthEdgeImage2.SetLayer(2);
	AddComponent<Image>(uiWidthEdgeImage2);

	Image uiHeightEdgeImage1(this);
	uiHeightEdgeImage1.Load("Assets/Image/UIEdge_Height.png");
	uiHeightEdgeImage1.SetPosition({ uiPos_.x + windowSize.x * 0.95f,uiPos_.y,0 });
	uiHeightEdgeImage1.SetSize({ edgeSize,imageRatio.y * 0.9f,0 });
	uiHeightEdgeImage1.SetLayer(2);
	AddComponent<Image>(uiHeightEdgeImage1);
	Image uiHeightEdgeImage2(this);
	uiHeightEdgeImage2.Load("Assets/Image/UIEdge_Height.png");
	uiHeightEdgeImage2.SetPosition({ uiPos_.x - windowSize.x * 0.95f,uiPos_.y,0 });
	uiHeightEdgeImage2.SetSize({ edgeSize,imageRatio.y * 0.9f,0 });
	uiHeightEdgeImage2.SetLayer(2);
	AddComponent<Image>(uiHeightEdgeImage2);

	Image uiCornerImage1(this);
	uiCornerImage1.Load("Assets/Image/UIEdge_Corner.png");
	uiCornerImage1.SetPosition({ uiPos_.x + windowSize.x * 0.95f,uiPos_.y + windowSize.y * 0.901f,0 });
	uiCornerImage1.SetSize({ edgeSize,edgeSize,0 });
	uiCornerImage1.SetLayer(2);
	AddComponent<Image>(uiCornerImage1);

	Image uiCornerImage2(this);
	uiCornerImage2.Load("Assets/Image/UIEdge_Corner.png");
	uiCornerImage2.SetPosition({ uiPos_.x + windowSize.x * 0.9495f,uiPos_.y - windowSize.y * 0.901f,0 });
	uiCornerImage2.SetSize({ edgeSize,edgeSize,0 });
	uiCornerImage2.SetLayer(2);
	uiCornerImage2.SetRotation({ 0,0,-90 });
	AddComponent<Image>(uiCornerImage2);

	Image uiCornerImage3(this);
	uiCornerImage3.Load("Assets/Image/UIEdge_Corner.png");
	uiCornerImage3.SetPosition({ uiPos_.x - windowSize.x * 0.9505f,uiPos_.y - windowSize.y * 0.901f,0 });
	uiCornerImage3.SetSize({ edgeSize,edgeSize,0 });
	uiCornerImage3.SetLayer(2);
	uiCornerImage3.SetRotation({ 0,0,180 });
	AddComponent<Image>(uiCornerImage3);

	Image uiCornerImage4(this);
	uiCornerImage4.Load("Assets/Image/UIEdge_Corner.png");
	uiCornerImage4.SetPosition({ uiPos_.x - windowSize.x * 0.95f,uiPos_.y + windowSize.y * 0.9f,0 });
	uiCornerImage4.SetSize({ edgeSize,edgeSize,0 });
	uiCornerImage4.SetLayer(2);
	uiCornerImage4.SetRotation({ 0,0,90 });
	AddComponent<Image>(uiCornerImage4);
}

void FinishCraftUI::Release()
{
}
