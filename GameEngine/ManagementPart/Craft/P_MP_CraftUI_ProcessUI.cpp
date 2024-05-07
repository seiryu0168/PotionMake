#include "P_MP_CraftUI_ProcessUI.h"
#include "P_MP_CraftUI_CraftPot.h"
#include "../../Engine/Systems/ImageSystem.h"
#include "../../Engine/Systems/TextSystem.h"
#include "../../Engine/DirectX_11/Input.h"

P_MP_CraftUI_ProcessUI::P_MP_CraftUI_ProcessUI(Object* parent)
	:GameObject(parent,"P_MP_CraftUI_ProcessUI"),
	craftPotObject_(nullptr),
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
	//左クリックしたら暗くし、右クリックしたら明るくする
	if (Input::IsMouseButtonDown(0)&&GetComponent<Image>().IsHitCursor()&&!isClicked_)
	{
		if (!((P_MP_CraftUI_CraftPot*)craftPotObject_)->AddProcessData(processNum_))
			return;
		GetComponent<Image>().SetColor({ 1,1,1 });	
		isClicked_ = !isClicked_;
	}
	else if (Input::IsMouseButtonDown(1) && GetComponent<Image>().IsHitCursor() && isClicked_)
	{
		if (!((P_MP_CraftUI_CraftPot*)craftPotObject_)->SubProcessData(processNum_))
			return;
		GetComponent<Image>().SetColor({ 0.7f,0.7f,0.7f });
		isClicked_ = !isClicked_;
	}
}

void P_MP_CraftUI_ProcessUI::SetProcessImage(std::string imageName)
{
	XMFLOAT3 pos = GetComponent<Image>().GetPosition();
	Image processImage(this);
	processImage.SetLayer(1);
	processImage.Load("Assets/Image/"+imageName);
	processImage.SetPosition({ pos.x - 0.2f,pos.y,0 });
	processImage.SetSize({ 0.2f,0.2f,0 });
	//processImage.SetColor({ 0.7f,0.7f,0.7f });
	AddComponent<Image>(processImage);

}

void P_MP_CraftUI_ProcessUI::SetProcessData(const std::string processName)
{
	name_ = processName;
	XMFLOAT3 pos = GetComponent<Image>().GetPositionAtPixel();
	Text processText(this);
	processText.SetText(name_);
	processText.SetColor({ 0,0,0,1 });
	processText.SetLayer(1);
	processText.SetPosition({ pos.x - 120,pos.y - 50 });
	AddComponent<Text>(processText);
}

void P_MP_CraftUI_ProcessUI::ActiveUI(bool isActive)
{
	for (int i=0;i<GetComponentList<Image>().size();i++)
	{
		GetComponent<Image>(i).SetDraw(isActive);
	}
	//GetComponent<Image>().SetDraw(isActive);
	GetComponent<Text>().isDraw_ = isActive;
}

void P_MP_CraftUI_ProcessUI::CreateBase(XMFLOAT3 uiPos)
{
	XMFLOAT3 windowSize;
	XMFLOAT3 imageRatio;
	Image uiBaseImage(this);
	uiBaseImage.Load("Assets/Image/UIBaseImage4.png");
	uiBaseImage.SetPosition({ uiPos.x,uiPos.y,0 });
	uiBaseImage.SetSize({ 8*1,8*0.3f,0 });
	uiBaseImage.SetColor(0.7f);
	uiBaseImage.SetLayer(1);
	windowSize = uiBaseImage.GetSizeAtPixel();
	imageRatio = uiBaseImage.GetSize();
	AddComponent<Image>(uiBaseImage);

	windowSize = { windowSize.x / (Direct3D::GetScreenWidth()),
				   windowSize.y / (Direct3D::GetScreenHeight()),0 };
	Image uiWidthEdgeImage1(this);
	uiWidthEdgeImage1.Load("Assets/Image/UIEdge_Width.png");
	uiWidthEdgeImage1.SetPosition({ uiPos.x,uiPos.y + windowSize.y ,0 });
	uiWidthEdgeImage1.SetSize({ imageRatio.x ,0.3f,0 });
	uiWidthEdgeImage1.SetLayer(1);
	AddComponent<Image>(uiWidthEdgeImage1);
	Image uiWidthEdgeImage2(this);
	uiWidthEdgeImage2.Load("Assets/Image/UIEdge_Width.png");
	uiWidthEdgeImage2.SetPosition({ uiPos.x,uiPos.y - windowSize.y ,0 });
	uiWidthEdgeImage2.SetSize({ imageRatio.x ,0.3f,0 });
	uiWidthEdgeImage2.SetLayer(1);
	AddComponent<Image>(uiWidthEdgeImage2);

	Image uiHeightEdgeImage1(this);
	uiHeightEdgeImage1.Load("Assets/Image/UIEdge_Height.png");
	uiHeightEdgeImage1.SetPosition({ uiPos.x + windowSize.x,uiPos.y,0 });
	uiHeightEdgeImage1.SetSize({ 0.3f,imageRatio.y ,0 });
	uiHeightEdgeImage1.SetLayer(1);
	AddComponent<Image>(uiHeightEdgeImage1);
	Image uiHeightEdgeImage2(this);
	uiHeightEdgeImage2.Load("Assets/Image/UIEdge_Height.png");
	uiHeightEdgeImage2.SetPosition({ uiPos.x - windowSize.x,uiPos.y,0 });
	uiHeightEdgeImage2.SetSize({ 0.3f,imageRatio.y ,0 });
	uiHeightEdgeImage2.SetLayer(1);
	AddComponent<Image>(uiHeightEdgeImage2);

	Image uiCornerImage1(this);
	uiCornerImage1.Load("Assets/Image/UIEdge_Corner.png");
	uiCornerImage1.SetPosition({ uiPos.x + windowSize.x,uiPos.y + windowSize.y ,0 });
	uiCornerImage1.SetSize({ 0.3f,0.3f,0 });
	uiCornerImage1.SetLayer(1);
	AddComponent<Image>(uiCornerImage1);

	Image uiCornerImage2(this);
	uiCornerImage2.Load("Assets/Image/UIEdge_Corner.png");
	uiCornerImage2.SetPosition({ uiPos.x + windowSize.x ,uiPos.y - windowSize.y ,0 });
	uiCornerImage2.SetSize({ 0.3f,0.3f,0 });
	uiCornerImage2.SetLayer(1);
	uiCornerImage2.SetRotation({ 0,0,-90 });
	AddComponent<Image>(uiCornerImage2);

	Image uiCornerImage3(this);
	uiCornerImage3.Load("Assets/Image/UIEdge_Corner.png");
	uiCornerImage3.SetPosition({ uiPos.x - windowSize.x ,uiPos.y - windowSize.y ,0 });
	uiCornerImage3.SetSize({ 0.3f,0.3f,0 });
	uiCornerImage3.SetLayer(1);
	uiCornerImage3.SetRotation({ 0,0,180 });
	AddComponent<Image>(uiCornerImage3);

	Image uiCornerImage4(this);
	uiCornerImage4.Load("Assets/Image/UIEdge_Corner.png");
	uiCornerImage4.SetPosition({ uiPos.x - windowSize.x ,uiPos.y + windowSize.y ,0 });
	uiCornerImage4.SetSize({ 0.3f,0.3f,0 });
	uiCornerImage4.SetLayer(1);
	uiCornerImage4.SetRotation({ 0,0,90 });
	AddComponent<Image>(uiCornerImage4);
}

void P_MP_CraftUI_ProcessUI::Release()
{
}
