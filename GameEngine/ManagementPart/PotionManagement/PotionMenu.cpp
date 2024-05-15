#include "PotionMenu.h"
#include "PotionStock.h"
#include "../../Engine/Systems/ImageSystem.h"
#include "../../Engine/DirectX_11/Input.h"
#include "../../Engine/Systems/TextSystem.h"
#include "../../CloseButton.h"
#include "../../Engine/ResourceManager/AudioManager.h"
PotionMenu::PotionMenu(Object* parent)
	:GameObject(parent,"PotionMenu"),
	isConfirm_(false),
	sellButtonImageNum_(-1),
	hAudio_Select_(-1),
	hAudio_Confirm_(-1),
	hAudio_Cancel_(-1),
	disposeButtonImageNum_(-1),
	cancelButtonImageNum_(-1)
{
}

PotionMenu::~PotionMenu()
{
}

void PotionMenu::Initialize()
{
	//UIの背景画像
	Image baseImage(this);
	baseImage.SetLayer(1);
	baseImage.Load("Assets/Image/UIBaseImage1.png");
	baseImage.SetSize({ 1.3f,1.3f,0 });
	AddComponent<Image>(baseImage);

	hAudio_Select_= AudioManager::Load("Assets/Audio/Confirm34.wav",false,1.0f,10);
	hAudio_Cancel_= AudioManager::Load("Assets/Audio/Confirm50.wav",false,1.0f,10);
	
}

void PotionMenu::Start()
{
	XMFLOAT3 pos = GetComponent<Image>().GetPosition();
	GameObject* clsBtn = Instantiate<CloseButton>(this);
	clsBtn->GetComponent<Image>().SetPosition({ pos.x - 0.295f,pos.y + 0.51f,0 });
	clsBtn->GetComponent<Image>().SetLayer(1);
}

void PotionMenu::Update()
{
	//kクリックしたら
	if (Input::IsMouseButtonDown(0))
	{
		//売るか捨てるか選択されてたら
		if (isConfirm_)
		{
			if (GetComponent<Image>(cancelButtonImageNum_).IsHitCursor())
			{
				AudioManager::Play(hAudio_Cancel_);
				((PotionStock*)pParent_)->SubPotion();
				KillMe();
			}
		}
		//選択されてなければ売るか捨てるか決められる
		else
		{

			if (GetComponent<Image>(sellButtonImageNum_).IsHitCursor())
			{
				((PotionStock*)pParent_)->AddSellPotion();
				AudioManager::Play(hAudio_Select_);
				KillMe();
			}

			if (GetComponent<Image>(disposeButtonImageNum_).IsHitCursor())
			{
				((PotionStock*)pParent_)->AddDisposePotion();
				AudioManager::Play(hAudio_Select_);
				KillMe();
			}
		}
	}
}

void PotionMenu::CreateMenu(int potionNum, const std::string& name, const XMFLOAT3& color,bool isConfirm)
{
	isConfirm_ = isConfirm;
	//ポーションの画像
	XMFLOAT3 pos = GetComponent<Image>().GetPosition();
	Image potionBaseImage(this);
	potionBaseImage.Load("Assets/Image/ItemBaseImage.png");
	potionBaseImage.SetLayer(1);
	potionBaseImage.SetSize({ 2.0f,2.0f,0, });
	potionBaseImage.SetPosition({ pos.x,pos.y + 0.25f,0 });
	AddComponent<Image>(potionBaseImage);

	//ポーションのベース画像
	Image potionImage(this);
	potionImage.Load("Assets/Image/Potion_BaseImage.png");
	potionImage.SetColor(color);
	potionImage.SetLayer(1);
	potionImage.SetSize({ 0.5f,0.5f,0 });
	potionImage.SetPosition({ pos.x,pos.y+0.25f,0 });
	AddComponent<Image>(potionImage);
	
	//ポーションの縁画像
	Image potionEdgeImage(this);
	potionEdgeImage.Load("Assets/Image/Potion_EdgeImage.png");
	potionEdgeImage.SetSize({ 0.5f,0.5f,0 });
	potionEdgeImage.SetLayer(1);
	potionEdgeImage.SetPosition({ pos.x,pos.y + 0.25f,0 });
	AddComponent<Image>(potionEdgeImage);

	XMFLOAT3 textPos = GetComponent<Image>().GetPositionAtPixel();
	
	//ポーション名
	Text potionNameText(this);
	potionNameText.SetText(name);
	potionNameText.SetAlignmentType(ALIGNMENT_TYPE::CENTER_TOP);
	potionNameText.SetTextSize(40);
	potionNameText.SetLayer(1);
	potionNameText.SetPosition({ textPos.x - 250,textPos.y + 40 });
	AddComponent<Text>(potionNameText);

	//売るか捨てるか選択されてたらキャンセルボタンを表示
	if (isConfirm)
	{

		//キャンセルボタン
		Image cancelButton(this);
		cancelButton.Load("Assets/Image/ButtonImage02.png");
		cancelButton.SetPosition({ pos.x,pos.y - 0.4f,0 });
		//cancelButton.SetSize({ 1,1,0 });
		cancelButton.SetLayer(1);
		cancelButtonImageNum_ = AddComponent<Image>(cancelButton);

		XMFLOAT3 imagePos = cancelButton.GetPositionAtPixel();
		Text cancelText(this);
		cancelText.SetText("キャンセル");
		cancelText.SetTextSize(50);
		cancelText.SetAlignmentType(ALIGNMENT_TYPE::CENTER_TOP);
		cancelText.SetRect({ 0,0,220,60 });
		cancelText.SetLayer(1);
		cancelText.SetColor({ 1,1,1,1 });
		cancelText.SetPosition({ imagePos.x-100,imagePos.y-5});
		AddComponent<Text>(cancelText);
	}
	//選択されてなければ販売/破棄ボタンを表示
	else
	{


		//販売ボタン
		Image sellButton(this);
		sellButton.Load("Assets/Image/ButtonImage02.png");
		sellButton.SetPosition({ pos.x - 0.15f,pos.y - 0.4f,0 });
		sellButton.SetSize({ 0.5f,0.5f,0 });
		sellButton.SetLayer(1);
		sellButtonImageNum_ = AddComponent<Image>(sellButton);

		XMFLOAT3 imagePos = sellButton.GetPositionAtPixel();
		Text sellText(this);
		sellText.SetText("売る");
		sellText.SetTextSize(40);
		sellText.SetAlignmentType(ALIGNMENT_TYPE::CENTER_TOP);
		sellText.SetRect({ 0,0,120,50 });
		sellText.SetLayer(1);
		sellText.SetColor({ 1,1,1,1 });
		sellText.SetPosition({ imagePos.x - 50,imagePos.y});
		AddComponent<Text>(sellText);

		//破棄ボタン
		Image disposeButton(this);
		disposeButton.Load("Assets/Image/ButtonImage02.png");
		disposeButton.SetPosition({ pos.x + 0.15f,pos.y - 0.4f,0 });
		disposeButton.SetSize({ 0.5f,0.5f,0 });
		disposeButton.SetLayer(1);
		disposeButtonImageNum_ = AddComponent<Image>(disposeButton);
		
		
		imagePos = disposeButton.GetPositionAtPixel();
		Text disposeText(this);
		disposeText.SetText("捨てる");
		disposeText.SetTextSize(40);
		disposeText.SetAlignmentType(ALIGNMENT_TYPE::CENTER_TOP);
		disposeText.SetRect({ 0,0,120,50 });
		disposeText.SetLayer(1);
		disposeText.SetColor({ 1,1,1,1 });
		disposeText.SetPosition({ imagePos.x - 50,imagePos.y});
		AddComponent<Text>(disposeText);


	}
}

void PotionMenu::Release()
{
	((PotionStock*)pParent_)->SetEnablePotionStock(true);
}
