#include "PotionMenu.h"
#include"../../Engine/Systems/ImageSystem.h"
#include"../../Engine/DirectX_11/Input.h"
#include"PotionStock.h"
#include"../../Engine/Systems/TextSystem.h"
#include"../../CloseButton.h"
PotionMenu::PotionMenu(Object* parent)
	:GameObject(parent,"PotionMenu"),
	isConfirm_(false)
{
}

PotionMenu::~PotionMenu()
{
}

void PotionMenu::Initialize()
{
	Image baseImage(this);
	baseImage.SetLayer(1);
	baseImage.Load("Assets/Image/UIBaseImage1.png");
	AddComponent<Image>(baseImage);
}

void PotionMenu::Start()
{
	XMFLOAT3 pos = GetComponent<Image>().GetPosition();
	GameObject* clsBtn = Instantiate<CloseButton>(this);
	clsBtn->GetComponent<Image>().SetPosition({ pos.x - 0.2f,pos.y + 0.3f,0 });
	clsBtn->GetComponent<Image>().SetLayer(1);
}

void PotionMenu::Update()
{
	//k�N���b�N������
	if (Input::IsMouseButtonDown(0))
	{
		//���邩�̂Ă邩�I������Ă���
		if (isConfirm_)
		{
			if (GetComponent<Image>(cancelButtonImageNum_).IsHitCursor())
			{
				((PotionStock*)pParent_)->SubPotion();
				KillMe();
			}
		}
		//�I������ĂȂ���Δ��邩�̂Ă邩���߂���
		else
		{

			if (GetComponent<Image>(sellButtonImageNum_).IsHitCursor())
			{
				((PotionStock*)pParent_)->AddSellPotion();
				KillMe();
			}

			if (GetComponent<Image>(disposeButtonImageNum_).IsHitCursor())
			{
				((PotionStock*)pParent_)->AddDisposePotion();
				KillMe();
			}
		}
	}
}

void PotionMenu::CreateMenu(int potionNum, const std::string& name, const XMFLOAT3& color,bool isConfirm)
{
	isConfirm_ = isConfirm;
	//�|�[�V�����̉摜
	XMFLOAT3 pos = GetComponent<Image>().GetPosition();
	Image potionBaseImage(this);
	potionBaseImage.Load("Assets/Image/ItemBaseImage.png");
	potionBaseImage.SetLayer(1);
	potionBaseImage.SetSize({ 2.0f,2.0f,0, });
	potionBaseImage.SetPosition({ pos.x,pos.y + 0.2f,0 });
	AddComponent<Image>(potionBaseImage);

	Image potionImage(this);
	potionImage.Load("Assets/Image/Potion_BaseImage.png");
	potionImage.SetColor(color);
	potionImage.SetLayer(1);
	potionImage.SetSize({ 0.5f,0.5f,0 });
	potionImage.SetPosition({ pos.x,pos.y+0.2f,0 });
	AddComponent<Image>(potionImage);
	
	Image potionEdgeImage(this);
	potionEdgeImage.Load("Assets/Image/Potion_EdgeImage.png");
	potionEdgeImage.SetSize({ 0.5f,0.5f,0 });
	potionEdgeImage.SetLayer(1);
	potionEdgeImage.SetPosition({ pos.x,pos.y + 0.2f,0 });
	AddComponent<Image>(potionEdgeImage);

	XMFLOAT3 textPos = GetComponent<Image>().GetPositionAtPixel();

	Text potionNameText(this);
	potionNameText.SetText(name);
	potionNameText.SetAlignmentType(ALIGNMENT_TYPE::CENTER_TOP);
	potionNameText.SetTextSize(40);
	potionNameText.SetLayer(1);
	potionNameText.SetPosition({ textPos.x - 250,textPos.y + 40 });
	AddComponent<Text>(potionNameText);

	//���邩�̂Ă邩�I������Ă���L�����Z���{�^����\��
	if (isConfirm)
	{

		//�L�����Z���{�^��
		Image cancelButton(this);
		cancelButton.Load("Assets/Image/PotionManagerUIBase1.png");
		cancelButton.SetPosition({ pos.x,pos.y - 0.3f,0 });
		cancelButton.SetSize({ 0.125*1.5f,0.125*0.5f,0 });
		cancelButton.SetLayer(1);
		cancelButtonImageNum_ = AddComponent<Image>(cancelButton);

		XMFLOAT3 imagePos = cancelButton.GetPositionAtPixel();
		Text cancelText(this);
		cancelText.SetText("�L�����Z��");
		cancelText.SetTextSize(40);
		cancelText.SetLayer(1);
		cancelText.SetColor({ 0,0,0,1 });
		cancelText.SetPosition({ imagePos.x-80,imagePos.y-30 });
		AddComponent<Text>(cancelText);
	}
	//�I������ĂȂ���Δ̔�/�j���{�^����\��
	else
	{


		//�̔��{�^��
		Image sellButton(this);
		sellButton.Load("Assets/Image/PotionManagerUIBase1.png");
		sellButton.SetPosition({ pos.x - 0.15f,pos.y - 0.3f,0 });
		sellButton.SetSize({ 0.125*1,0.125*0.3f,0 });
		sellButton.SetLayer(1);
		sellButtonImageNum_ = AddComponent<Image>(sellButton);

		XMFLOAT3 imagePos = sellButton.GetPositionAtPixel();
		Text sellText(this);
		sellText.SetText("����");
		sellText.SetTextSize(30);
		sellText.SetLayer(1);
		sellText.SetColor({ 0,0,0,1 });
		sellText.SetPosition({ imagePos.x - 30,imagePos.y - 20 });
		AddComponent<Text>(sellText);

		//�j���{�^��
		Image disposeButton(this);
		disposeButton.Load("Assets/Image/PotionManagerUIBase1.png");
		disposeButton.SetPosition({ pos.x + 0.15f,pos.y - 0.3f,0 });
		disposeButton.SetSize({ 0.125*1,0.125*0.3f,0 });
		disposeButton.SetLayer(1);
		disposeButtonImageNum_ = AddComponent<Image>(disposeButton);
		
		
		imagePos = disposeButton.GetPositionAtPixel();
		Text disposeText(this);
		disposeText.SetText("�̂Ă�");
		disposeText.SetTextSize(30);
		disposeText.SetLayer(1);
		disposeText.SetColor({ 0,0,0,1 });
		disposeText.SetPosition({ imagePos.x - 30,imagePos.y - 20 });
		AddComponent<Text>(disposeText);


	}
}

void PotionMenu::Release()
{
	((PotionStock*)pParent_)->SetEnablePotionStock(true);
}