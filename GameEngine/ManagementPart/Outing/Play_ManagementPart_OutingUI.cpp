#include "Play_ManagementPart_OutingUI.h"
#include"../../Engine/Systems/TextSystem.h"
#include"../../Engine/Systems/ImageSystem.h"
#include"../../Engine/DirectX_11/Input.h"
#include"../../Play_ManagementPart_BaseUI.h"
#include"P_MP_OutingUI_ActionText.h"
Play_ManagementPart_OutingUI::Play_ManagementPart_OutingUI(Object* parent)
	:UIBase(parent,"Play_ManagementPart_OutingUI")
{
}

Play_ManagementPart_OutingUI::~Play_ManagementPart_OutingUI()
{
}

void Play_ManagementPart_OutingUI::Initialize()
{
	Image uiBaseImage(this);
	uiBaseImage.Load("Assets/Image/UIBaseImage1.png");
	AddComponent<Image>(uiBaseImage);

	Text collectionText(this);
	collectionText.SetText("外出");
	collectionText.SetPosition({ 880,300 });
	AddComponent<Text>(collectionText);

	Instantiate<P_MP_OutingUI_ActionText>(this);
}

void Play_ManagementPart_OutingUI::Update()
{
	//クリックしたら
	if (Input::IsMouseButtonDown(0))
	{
		XMFLOAT3 mousePos = StoreFloat3(Input::GetMousePosition());
		if (!(mousePos.x >= 700.0f && mousePos.x <= 1210.0f &&
			mousePos.y >= 270 && mousePos.y <= 790.0f))
		{
			KillMe();
		}
	}
}

void Play_ManagementPart_OutingUI::Release()
{
	Direct3D::ShowMouseCursor(false);
	XMINT2 rectPos = { (int)(Direct3D::GetScreenWidth() * 0.5f),(int)(Direct3D::GetScreenHeight() * 0.5f) };
	Direct3D::SetClipCursor({ rectPos.x,rectPos.y,rectPos.x + 1,rectPos.y + 1 });
	((Play_ManagementPart_BaseUI*)pParent_)->SetAccessUIFlag(false);
}
