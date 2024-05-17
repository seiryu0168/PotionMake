#include "P_MP_OutingUI_ActionText.h"
#include "Play_ManagementPart_OutingUI.h"
#include "../Outing/P_MP_SettlementUI.h"
#include "../../Engine/DirectX_11/Input.h"
#include "../../Engine/Systems/ImageSystem.h"
#include "../../Engine/Systems/TextSystem.h"
#include "../../Engine/newSceneManager.h"
P_MP_OutingUI_ActionText::P_MP_OutingUI_ActionText(Object* parent)
	:GameObject(parent,"P_MP_OutingUI_ActionText")
{
}

P_MP_OutingUI_ActionText::~P_MP_OutingUI_ActionText()
{
}

void P_MP_OutingUI_ActionText::Initialize()
{
	{

		Image selectImage(this);
		selectImage.Load("Assets/Image/SelectImage1.png");
		selectImage.SetSize({ 1,0.18f,0 });
		selectImage.SetAlpha(0);
		selectImage.SetPosition({ 0,0.1f,0 });
		AddComponent<Image>(selectImage);
		XMFLOAT3 txtPos = selectImage.GetPositionAtPixel();
		XMFLOAT3 txtSize = selectImage.GetSizeAtPixel();
		Text actionText(this);
		actionText.SetAlignmentType(ALIGNMENT_TYPE::CENTER_TOP);
		actionText.SetText("採集に出かける");
		actionText.SetPosition({ txtPos.x - txtSize.x * 0.5f,txtPos.y - txtSize.y * 0.5f });
		AddComponent<Text>(actionText);
	}
	{

		Image selectImage(this);
		selectImage.Load("Assets/Image/SelectImage1.png");
		selectImage.SetSize({ 1,0.18f,0 });
		selectImage.SetAlpha(0);
		selectImage.SetPosition({ 0,-0.1f,0 });
		AddComponent<Image>(selectImage);
		XMFLOAT3 txtPos = selectImage.GetPositionAtPixel();
		XMFLOAT3 txtSize = selectImage.GetSizeAtPixel();
		Text actionText(this);
		actionText.SetAlignmentType(ALIGNMENT_TYPE::CENTER_TOP);
		actionText.SetText("売りに行く");
		actionText.SetPosition({ txtPos.x - txtSize.x*0.5f,txtPos.y - txtSize.y*0.5f });
		AddComponent<Text>(actionText);
	}

	
}

void P_MP_OutingUI_ActionText::Start()
{
}

void P_MP_OutingUI_ActionText::Update()
{
	int forcusNum = -1;
	//マウスの位置によって強調する
	//XMFLOAT3 mousePos = StoreFloat3(Input::GetMousePosition());
	float screenH = (float)Direct3D::GetScreenHeight();

	if (GetComponent<Image>().IsHitCursor())
	{
		//GetComponent<Image>().SetPosition({ 0,0.02,0 });
		GetComponent<Image>().SetAlpha(1);
		forcusNum = 0;
	}
	else
	{
		GetComponent<Image>().SetAlpha(0);
	}
	if (GetComponent<Image>(1).IsHitCursor())
	{
		//GetComponent<Image>(1).SetPosition({ 0,0.02,0 });
		GetComponent<Image>(1).SetAlpha(1);
		forcusNum = 1;
	}
	else
	{
		GetComponent<Image>(1).SetAlpha(0);
	}





	//if (mousePos.x >= 700.0f && mousePos.x <= 1210.0f &&
	//	mousePos.y >= 480.0f && mousePos.y <= 570.0f)
	//{
	//	GetComponent<Image>().SetPosition({ 0,0.02,0 });
	//	GetComponent<Image>().SetAlpha(1);
	//	forcusNum = 0;
	//}
	//else if (mousePos.x >= 700.0f && mousePos.x <= 1210.0f &&
	//		 mousePos.y >= 571.0f && mousePos.y <= 658.0f)
	//{
	//	GetComponent<Image>().SetPosition({ 0,-0.15f,0 });
	//	GetComponent<Image>().SetAlpha(1);
	//	forcusNum = 1;
	//}
	//else
	//{
	//	GetComponent<Image>().SetAlpha(0);
	//	forcusNum = -1;
	//}
	if (Input::IsMouseButtonUp(0)&& forcusNum>=0)
	{
		((Play_ManagementPart_OutingUI*)pParent_)->SetCloseFlag(false);
		((Play_ManagementPart_OutingUI*)pParent_)->SetOutNumber(forcusNum);
		KillMe();
		//Outing(forcusNum);
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
		Instantiate<P_MP_SettlementUI>(pParent_);
		KillMe();
	}
}

void P_MP_OutingUI_ActionText::Release()
{
	
}
