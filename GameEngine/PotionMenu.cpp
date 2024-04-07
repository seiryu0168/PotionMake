#include "PotionMenu.h"
#include"Engine/Systems/ImageSystem.h"
#include"Engine/DirectX_11/Input.h"
#include"PotionStock.h"
PotionMenu::PotionMenu(Object* parent)
	:GameObject(parent,"PotionMenu")
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
	if (Input::IsMouseButtonDown(0))
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

void PotionMenu::CreateMenu(int potionNum, const std::string& name, const XMFLOAT3& color)
{
	//�|�[�V�����̉摜
	XMFLOAT3 pos = GetComponent<Image>().GetPosition();
	Image potionImage(this);
	potionImage.Load("Assets/Image/ItemBaseImage.png");
	potionImage.SetPosition({ pos.x,pos.y + 0.2f,0 });
	AddComponent<Image>(potionImage);
	
	//�̔��{�^��
	Image sellButton(this);
	sellButton.Load("Assets/Image/ItemBaseImage.png");
	sellButton.SetPosition({ pos.x-0.15f,pos.y - 0.2f,0 });
	sellButton.SetSize({ 1,0.3f,0 });
	sellButtonImageNum_ = AddComponent<Image>(sellButton);

	//�j���{�^��
	Image disposeButton(this);
	disposeButton.Load("Assets/Image/ItemBaseImage.png");
	disposeButton.SetPosition({ pos.x + 0.15f,pos.y - 0.2f,0 });
	disposeButton.SetSize({ 1,0.3f,0 });
	disposeButtonImageNum_ = AddComponent<Image>(disposeButton);
}

void PotionMenu::Release()
{
}
