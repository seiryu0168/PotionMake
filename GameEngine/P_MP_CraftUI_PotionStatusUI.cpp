#include "P_MP_CraftUI_PotionStatusUI.h"
#include"Engine/Systems/ImageSystem.h"
#include"Engine/Systems/TextSystem.h"
#include"PotionStatusGauge.h"
P_MP_CraftUI_PotionStatusUI::P_MP_CraftUI_PotionStatusUI(Object* parent)
	:GameObject(parent,"P_MP_CraftUI_PotionStatusUI"),
	uiPos_({ -0.6,-0.67f })
{
}

P_MP_CraftUI_PotionStatusUI::~P_MP_CraftUI_PotionStatusUI()
{
}

void P_MP_CraftUI_PotionStatusUI::Initialize()
{
	Image uiBaseImage(this);
	uiBaseImage.Load("Assets/Image/PotionManagerUIBase1.png");
	uiBaseImage.SetPosition({ uiPos_.x,uiPos_.y,0 });
	uiBaseImage.SetSize({ 0.7f,0.3f,0 });
	AddComponent<Image>(uiBaseImage);

	XMFLOAT2 diff = { -0.3f,-0.1f };
	//�|�[�V�����̊e�p�����[�^��\��
	for (int i = 0; i < 5; i++)
	{
		GameObject* gauge = Instantiate<PotionStatusGauge>(this);
		gauge->GetComponent<Image>().SetPosition({ uiPos_.x + diff.x,uiPos_.y + diff.y,0 });
		diff.x += 0.1f;
	}


}

void P_MP_CraftUI_PotionStatusUI::Start()
{
}

void P_MP_CraftUI_PotionStatusUI::Update()
{
}

void P_MP_CraftUI_PotionStatusUI::Release()
{
}
