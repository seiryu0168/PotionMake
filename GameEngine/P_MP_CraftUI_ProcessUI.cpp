#include "P_MP_CraftUI_ProcessUI.h"
#include"Engine/Systems/ImageSystem.h"
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
}

void P_MP_CraftUI_ProcessUI::Update()
{
}

void P_MP_CraftUI_ProcessUI::SetProcessImage(std::string imageName)
{
	Image processImage(this);
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
