#include "P_MP_CraftUI_ProcessUI.h"
#include"Engine/Systems/ImageSystem.h"
#include"Engine/DirectX_11/Input.h"
#include"P_MP_CraftUI_CraftPot.h"
P_MP_CraftUI_ProcessUI::P_MP_CraftUI_ProcessUI(Object* parent)
	:GameObject(parent,"P_MP_CraftUI_ProcessUI"),
	processNum_(-1)
{
}

P_MP_CraftUI_ProcessUI::~P_MP_CraftUI_ProcessUI()
{
}

void P_MP_CraftUI_ProcessUI::Initialize()
{

}

void P_MP_CraftUI_ProcessUI::Start()
{
	craftPotObject_= (GameObject*)FindObject("P_MP_CraftUI_CraftPot");
}

void P_MP_CraftUI_ProcessUI::Update()
{
	if (Input::IsMouseButtonDown(0))
	{
		((P_MP_CraftUI_CraftPot*)craftPotObject_)->AddProcessData(processNum_);
	}
}

void P_MP_CraftUI_ProcessUI::SetProcessImage(std::string imageName)
{
	Image processImage(this);
	processImage.SetLayer(1);
	processImage.Load(imageName);
	AddComponent<Image>(processImage);

}

void P_MP_CraftUI_ProcessUI::ActiveUI(bool isActive)
{
	GetComponent<Image>().SetDraw(isActive);
}

void P_MP_CraftUI_ProcessUI::Release()
{
}
