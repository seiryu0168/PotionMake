#include "FinishCraftUI.h"
#include"../../Engine/Systems/ImageSystem.h"
#include"../../Engine/DirectX_11/Input.h"
#include"../../InterSceneData.h"
#include"../../PlayerData.h"
#include"../../Engine/Systems/TextSystem.h"
FinishCraftUI::FinishCraftUI(Object* parent)
	:GameObject(parent,"FinishCraftUI"),
	okButtonImageNum_(-1)
{
}

FinishCraftUI::~FinishCraftUI()
{
}

void FinishCraftUI::Initialize()
{
	//背景の画像
	Image backImage(this);
	backImage.Load("Assets/Image/PotionManagerUIBase1.png");
	backImage.SetSize({ 2,2,0 });
	backImage.SetLayer(2);
	AddComponent<Image>(backImage);
	
	//ポーションのデータを取得
	PlayerData* data = InterSceneData::GetData<PlayerData>("Data01");
	PlayerData::PotionData pData = data->potionDataList_[data->potionDataList_.size() - 1];
	
	//ポーションのボトル部分の画像
	Image potionImage(this);
	potionImage.Load("Assets/Image/Potion_BaseImage.png");
	potionImage.SetLayer(2);
	potionImage.SetColor(pData.potionColor_);
	AddComponent<Image>(potionImage);
	
	//ポーションの縁の画像
	Image edgeImage(this);
	edgeImage.Load("Assets/Image/Potion_EdgeImage.png");
	edgeImage.SetLayer(2);
	AddComponent<Image>(edgeImage);

	//OKボタンの画像
	Image okButtonImage(this);
	okButtonImage.Load("Assets/Image/ItemBaseImage.png");
	okButtonImage.SetSize({ 2,1,0 });
	okButtonImage.SetPosition({ 0,-0.6f,0 });
	okButtonImage.SetLayer(2);
	okButtonImageNum_ = AddComponent<Image>(okButtonImage);

	//ポーションの名前
	Text potionNameText(this);
	potionNameText.SetRect({ 0,0,1000,200 });
	potionNameText.SetAlignmentType(ALIGNMENT_TYPE::CENTER_TOP);
	potionNameText.SetColor({ 0,0,0,1 });
	potionNameText.SetLayer(2);
	potionNameText.SetText(pData.potionName_);
	potionNameText.SetPosition({ 500,600 });
	AddComponent<Text>(potionNameText);
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

void FinishCraftUI::Release()
{
}
