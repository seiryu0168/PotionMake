#include "Play_ManagementPart_CraftUI.h"
#include"Engine/Systems/TextSystem.h"
#include"Engine/Systems/ImageSystem.h"
#include"CloseButton.h"
#include"Engine/DirectX_11/Input.h"
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
	craftUIText.SetText("ƒ|[ƒVƒ‡ƒ“‚ğì‚é");
	craftUIText.SetPosition({ 1000.0f,500.0f });
	AddComponent<Text>(craftUIText);

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
