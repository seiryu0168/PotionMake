#include "ResourceMenuChangeButton.h"
#include "P_MP_CraftUI_ResourceStockUI.h"
#include "../../Engine/DirectX_11/Input.h"
#include "../../Engine/Systems/ImageSystem.h"
ResourceMenuChangeButton::ResourceMenuChangeButton(Object* parent)
	:GameObject(parent,"ResourceMenuChangeButton")
{
}

ResourceMenuChangeButton::~ResourceMenuChangeButton()
{
}

void ResourceMenuChangeButton::Initialize()
{
	{

		Image buttonImage(this);
		buttonImage.Load("Assets/Image/SelectImage4.png");
		buttonImage.SetSize({ 0.2f,0.2f,0 });
		AddComponent<Image>(buttonImage);
	}
	{

		Image buttonImage(this);
		buttonImage.Load("Assets/Image/SelectImage4.png");
		buttonImage.SetSize({ 0.2f,0.2f,0 });
		AddComponent<Image>(buttonImage);
	}
}

void ResourceMenuChangeButton::Update()
{
	//‰æ‘œ‚ðƒNƒŠƒbƒN‚µ‚½‚ç
	if (Input::IsMouseButtonDown(0) && GetComponent<Image>(0).IsHitCursor())
	{
		((P_MP_CraftUI_ResourceStockUI*)pParent_)->ModeChange(ResourceMenuMode::ResourceSelect);
	}
	if (Input::IsMouseButtonDown(0) && GetComponent<Image>(1).IsHitCursor())
	{
		((P_MP_CraftUI_ResourceStockUI*)pParent_)->ModeChange(ResourceMenuMode::ProcessSelect);
	}
}

void ResourceMenuChangeButton::Release()
{
}
