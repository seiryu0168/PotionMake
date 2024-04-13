#include "PotionMenu.h"
#include"../../Engine/Systems/ImageSystem.h"
#include"../../Engine/DirectX_11/Input.h"
#include"PotionStock.h"
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
	baseImage.Load("Assets/Image/UIBaseImage1.png");
	AddComponent<Image>(baseImage);
}

void PotionMenu::Start()
{
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
	potionBaseImage.SetSize({ 2.0f,2.0f,0, });
	potionBaseImage.SetPosition({ pos.x,pos.y + 0.2f,0 });
	AddComponent<Image>(potionBaseImage);

	Image potionImage(this);
	potionImage.Load("Assets/Image/Potion_BaseImage.png");
	potionImage.SetColor(color);
	potionImage.SetSize({ 0.5f,0.5f,0 });
	potionImage.SetPosition({ pos.x,pos.y+0.2f,0 });
	AddComponent<Image>(potionImage);
	
	Image potionEdgeImage(this);
	potionEdgeImage.Load("Assets/Image/Potion_EdgeImage.png");
	potionEdgeImage.SetSize({ 0.5f,0.5f,0 });
	potionEdgeImage.SetPosition({ pos.x,pos.y + 0.2f,0 });
	AddComponent<Image>(potionEdgeImage);

	//���邩�̂Ă邩�I������Ă���L�����Z���{�^����\��
	if (isConfirm)
	{

		//�L�����Z���{�^��
		Image cancelButton(this);
		cancelButton.Load("Assets/Image/ItemBaseImage.png");
		cancelButton.SetPosition({ pos.x,pos.y - 0.2f,0 });
		cancelButton.SetSize({ 1.5f,0.5f,0 });
		cancelButtonImageNum_ = AddComponent<Image>(cancelButton);
	}
	//�I������ĂȂ���Δ̔�/�j���{�^����\��
	else
	{


		//�̔��{�^��
		Image sellButton(this);
		sellButton.Load("Assets/Image/ItemBaseImage.png");
		sellButton.SetPosition({ pos.x - 0.15f,pos.y - 0.2f,0 });
		sellButton.SetSize({ 1,0.3f,0 });
		sellButtonImageNum_ = AddComponent<Image>(sellButton);

		//�j���{�^��
		Image disposeButton(this);
		disposeButton.Load("Assets/Image/ItemBaseImage.png");
		disposeButton.SetPosition({ pos.x + 0.15f,pos.y - 0.2f,0 });
		disposeButton.SetSize({ 1,0.3f,0 });
		disposeButtonImageNum_ = AddComponent<Image>(disposeButton);
	}
}

void PotionMenu::Release()
{
}
