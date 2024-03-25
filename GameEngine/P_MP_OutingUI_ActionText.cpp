#include "P_MP_OutingUI_ActionText.h"
#include"Engine/DirectX_11/Input.h"
#include"Engine/Systems/ImageSystem.h"
#include"Engine/Systems/TextSystem.h"
P_MP_OutingUI_ActionText::P_MP_OutingUI_ActionText(Object* parent)
	:GameObject(parent,"P_MP_OutingUI_ActionText")
{
}

P_MP_OutingUI_ActionText::~P_MP_OutingUI_ActionText()
{
}

void P_MP_OutingUI_ActionText::Initialize()
{
	Image selectImage(this);
	selectImage.Load("Assets/Image/SelectImage1.png");
	selectImage.SetSize({ 1,0.18f,0 });
	selectImage.SetAlpha(0);
	selectImage.SetPosition({ 0,-0.02f,0 });
	AddComponent<Image>(selectImage);
	Text actionText(this);
	actionText.SetAlignmentType(ALIGNMENT_TYPE::CENTER_TOP);
	actionText.SetText("çÃèWÇ…èoÇ©ÇØÇÈ\nîÑÇËÇ…çsÇ≠");
	actionText.SetPosition({ 700,500 });
	AddComponent<Text>(actionText);
}

void P_MP_OutingUI_ActionText::Start()
{
}

void P_MP_OutingUI_ActionText::Update()
{
	XMFLOAT3 mousePos = StoreFloat3(Input::GetMousePosition());
	float screenH = (float)Direct3D::GetScreenHeight();
	if (mousePos.x >= 700.0f && mousePos.x <= 1210.0f &&
		mousePos.y >= 500.0f && mousePos.y <= 590.0f)
	{
		GetComponent<Image>().SetPosition({ 0,-0.02f,0 });
		GetComponent<Image>().SetAlpha(1);
	}
	else if (mousePos.x >= 700.0f && mousePos.x <= 1210.0f &&
			 mousePos.y >= 600.0f && mousePos.y <= 690.0f)
	{
		GetComponent<Image>().SetPosition({ 0,-0.2f,0 });
		GetComponent<Image>().SetAlpha(1);
	}
	else
		GetComponent<Image>().SetAlpha(0);
}

void P_MP_OutingUI_ActionText::Release()
{
}
