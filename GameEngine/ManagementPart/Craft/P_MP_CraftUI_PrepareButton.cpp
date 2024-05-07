#include "P_MP_CraftUI_PrepareButton.h"
#include "P_MP_CraftUI_CraftPot.h"
#include "../../Engine/Systems/ImageSystem.h"
#include "../../Engine/DirectX_11/Input.h"
P_MP_CraftUI_PrepareButton::P_MP_CraftUI_PrepareButton(Object* parent)
	:GameObject(parent,"P_MP_CraftUI_PrepareButton")
{
}

P_MP_CraftUI_PrepareButton::~P_MP_CraftUI_PrepareButton()
{
}

void P_MP_CraftUI_PrepareButton::Initialize()
{
	//ポーション制作開始の画像
	Image potImage(this);
	potImage.Load("Assets/Image/PreparePot05.png");
	potImage.SetPosition({ -0.05f,-0.2f,0 });
	potImage.SetSize({ 0.3f,0.3f,0 });
	AddComponent<Image>(potImage);

	//矢印
	Image arrowImage(this);
	arrowImage.Load("Assets/Image/InputArrow.png");
	arrowImage.SetPosition({ -0.1f,0.3f,0 });
	arrowImage.SetSize({ 0.45f,0.45f,0 });
	AddComponent<Image>(arrowImage);
}

void P_MP_CraftUI_PrepareButton::Start()
{
}

void P_MP_CraftUI_PrepareButton::Update()
{
	//カーソルが画像に当たっていたら
	if (GetComponent<Image>().IsHitCursor())
	{
		//右クリックし始めたら
		if (Input::IsMouseButtonDown(0))
		{
			GetComponent<Image>().SetColor({ 0.7f,0.7f,0.7f });
		}
		//右クリックし終わったら
		if (Input::IsMouseButtonUp(0))
		{

			GetComponent<Image>().SetColor(1);
			((P_MP_CraftUI_CraftPot*)pParent_)->CreatePotion();
		}
	}
	else
			GetComponent<Image>().SetColor(1);

}

void P_MP_CraftUI_PrepareButton::Release()
{
}
