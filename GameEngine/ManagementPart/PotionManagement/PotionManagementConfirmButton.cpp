#include "PotionManagementConfirmButton.h"
#include"../../Engine/Systems/ImageSystem.h"
#include"../../Engine/DirectX_11/Input.h"
#include"P_MP_PotionManagerUI_PotionStockUI.h"
PotionManagementConfirmButton::PotionManagementConfirmButton(Object* parent)
	:GameObject(parent,"PotionManagementConfirmButton")
{
}

PotionManagementConfirmButton::~PotionManagementConfirmButton()
{
}

void PotionManagementConfirmButton::Initialize()
{
	//確定ボタンの画像
	Image confirmImage(this);
	confirmImage.Load("Assets/Image/ConfirmImage01.png");
	confirmImage.SetPosition({ -0.7f,-0.7f,0 });
	confirmImage.SetSize({ 1.5f,0.5f,0 });
	AddComponent<Image>(confirmImage);
}

void PotionManagementConfirmButton::Start()
{
}

void PotionManagementConfirmButton::Update()
{
	if (Input::IsMouseButtonDown(0) && GetComponent<Image>().IsHitCursor())
	{
		//ポーションのデータ管理を始める
		((P_MP_PotionManagerUI_PotionStockUI*)pParent_)->ConfirmPotionManagement();
	}
}

void PotionManagementConfirmButton::Release()
{
}
