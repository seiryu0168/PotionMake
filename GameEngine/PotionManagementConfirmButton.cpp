#include "PotionManagementConfirmButton.h"
#include"Engine/Systems/ImageSystem.h"
#include"Engine/DirectX_11/Input.h"
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
	Image confirmImage(this);
	confirmImage.Load("Assets/Image/ConfirmImage01.png");
	AddComponent<Image>(confirmImage);
}

void PotionManagementConfirmButton::Start()
{
}

void PotionManagementConfirmButton::Update()
{
	if (Input::IsMouseButtonDown(0) && GetComponent<Image>().IsHitCursor())
	{
		((P_MP_PotionManagerUI_PotionStockUI*)pParent_)->ConfirmPotionManagement();
	}
}

void PotionManagementConfirmButton::Release()
{
}
