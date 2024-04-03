#include "P_MP_CraftUI_ProcessUI.h"
#include"Engine/Systems/ImageSystem.h"
#include"Engine/DirectX_11/Input.h"
#include"P_MP_CraftUI_CraftPot.h"
P_MP_CraftUI_ProcessUI::P_MP_CraftUI_ProcessUI(Object* parent)
	:GameObject(parent,"P_MP_CraftUI_ProcessUI"),
	processNum_(-1),
	isClicked_(false)

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
	if (Input::IsMouseButtonDown(0)&&GetComponent<Image>().IsHitCursor()&&!isClicked_)
	{
		((P_MP_CraftUI_CraftPot*)craftPotObject_)->AddProcessData(processNum_);
		GetComponent<Image>().SetColor({ 1,1,1 });	
		isClicked_ = !isClicked_;
	}
	else if (Input::IsMouseButtonDown(1) && GetComponent<Image>().IsHitCursor() && isClicked_)
	{
		((P_MP_CraftUI_CraftPot*)craftPotObject_)->SubProcessData(processNum_);
		GetComponent<Image>().SetColor({ 0.7f,0.7f,0.7f });
		isClicked_ = !isClicked_;
	}
}

void P_MP_CraftUI_ProcessUI::SetProcessImage(std::string imageName)
{
	Image processImage(this);
	processImage.SetLayer(1);
	processImage.Load(imageName);
	processImage.SetColor({ 0.7f,0.7f,0.7f });
	AddComponent<Image>(processImage);

}

void P_MP_CraftUI_ProcessUI::ActiveUI(bool isActive)
{
	GetComponent<Image>().SetDraw(isActive);
}

void P_MP_CraftUI_ProcessUI::Release()
{
}
