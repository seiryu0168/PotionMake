#include "Play_ManagementPart_CraftUI.h"
#include"Engine/Systems/TextSystem.h"
#include"Engine/Systems/ImageSystem.h"
#include"CloseButton.h"
#include"Engine/DirectX_11/Input.h"
#include"P_MP_CraftUI_ResourceStockUI.h"
#include"P_MP_CraftUI_PotionStatusUI.h"
#include"P_MP_CraftUI_PrepareUI.h"
Play_ManagementPart_CraftUI::Play_ManagementPart_CraftUI(Object* parent)
	:GameObject(parent,"Play_ManagementPart_CraftUI")
{
}

Play_ManagementPart_CraftUI::~Play_ManagementPart_CraftUI()
{
}

void Play_ManagementPart_CraftUI::Initialize()
{
	Text craftUIText(this);
	craftUIText.SetText("É|Å[ÉVÉáÉìÇçÏÇÈ");
	craftUIText.SetPosition({ 600,30 });
	AddComponent<Text>(craftUIText);
	Instantiate<P_MP_CraftUI_ResourceStockUI>(this);
	Instantiate<P_MP_CraftUI_PotionStatusUI>(this);
	Instantiate<P_MP_CraftUI_PrepareUI>(this);
	Instantiate<CloseButton>(this);
}

void Play_ManagementPart_CraftUI::Update()
{
	//if (Input::IsMouseButtonDown(0))
	//{
	//	XMFLOAT3 mousePos = StoreFloat3(Input::GetMousePosition());
	//	if (!(mousePos.x >= 700.0f && mousePos.x <= 1210.0f &&
	//		mousePos.y >= 270 && mousePos.y <= 790.0f))
	//	{
	//		KillMe();
	//	}
	//}
}

void Play_ManagementPart_CraftUI::Release()
{
}
