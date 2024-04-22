#include "P_MP_OutingUI_ActionText.h"
#include"../../Engine/DirectX_11/Input.h"
#include"../../Engine/Systems/ImageSystem.h"
#include"../../Engine/Systems/TextSystem.h"
#include"../../Engine/newSceneManager.h"
#include"../../P_MP_SettlementUI.h"
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
	actionText.SetText("採集に出かける\n売りに行く");
	actionText.SetPosition({ 700,500 });
	AddComponent<Text>(actionText);
}

void P_MP_OutingUI_ActionText::Start()
{
}

void P_MP_OutingUI_ActionText::Update()
{
	int forcusNum = -1;
	//マウスの位置によって強調する
	XMFLOAT3 mousePos = StoreFloat3(Input::GetMousePosition());
	float screenH = (float)Direct3D::GetScreenHeight();
	if (mousePos.x >= 700.0f && mousePos.x <= 1210.0f &&
		mousePos.y >= 500.0f && mousePos.y <= 590.0f)
	{
		GetComponent<Image>().SetPosition({ 0,-0.02f,0 });
		GetComponent<Image>().SetAlpha(1);
		forcusNum = 0;
	}
	else if (mousePos.x >= 700.0f && mousePos.x <= 1210.0f &&
			 mousePos.y >= 600.0f && mousePos.y <= 690.0f)
	{
		GetComponent<Image>().SetPosition({ 0,-0.2f,0 });
		GetComponent<Image>().SetAlpha(1);
		forcusNum = 1;
	}
	else
	{
		GetComponent<Image>().SetAlpha(0);
		forcusNum = -1;
	}
	if (Input::IsMouseButtonUp(0)&& forcusNum>=0)
	{
		Outing(forcusNum);
	}
}

void P_MP_OutingUI_ActionText::Outing(int outNum)
{
	if (outNum == 0)
	{
		newSceneManager::ChangeScene(SCENE_ID::PLAY_COLLECTION);
	}
	else if (outNum == 1)
	{
		Instantiate<P_MP_SettlementUI>(this);
	}
}

void P_MP_OutingUI_ActionText::Release()
{
}
