#include "P_MP_CraftUI_PrepareUI.h"
#include "P_MP_CraftUI_CraftPot.h"
#include "../../Engine/Systems/ImageSystem.h"
#include "../../Engine/Systems/TextSystem.h"
P_MP_CraftUI_PrepareUI::P_MP_CraftUI_PrepareUI(Object* parent)
	:GameObject(parent,"P_MP_CraftUI_PrepareUI")
{
}

P_MP_CraftUI_PrepareUI::~P_MP_CraftUI_PrepareUI()
{
}

void P_MP_CraftUI_PrepareUI::Initialize()
{
	XMFLOAT2 imagePos = { -0.6,0.25f };
	XMFLOAT3 windowSize;
	Image uiBaseImage(this);
	uiBaseImage.Load("Assets/Image/UIBaseImage2.png");
	uiBaseImage.SetPosition({ imagePos.x,imagePos.y,0 });
	uiBaseImage.SetSize({ 16*0.7f,16*0.5f,0 });
	windowSize = uiBaseImage.GetSizeAtPixel();
	AddComponent<Image>(uiBaseImage);

	windowSize = { windowSize.x / (Direct3D::GetScreenWidth()),
				   windowSize.y / (Direct3D::GetScreenHeight()),0 };
	Image uiWidthEdgeImage1(this);
	uiWidthEdgeImage1.Load("Assets/Image/UIEdge_Width.png");
	uiWidthEdgeImage1.SetPosition({ imagePos.x,imagePos.y+ windowSize.y*0.9f,0 });
	uiWidthEdgeImage1.SetSize({ 11.1 * 0.95f,0.3f,0 });
	AddComponent<Image>(uiWidthEdgeImage1);
	Image uiWidthEdgeImage2(this);
	uiWidthEdgeImage2.Load("Assets/Image/UIEdge_Width.png");
	uiWidthEdgeImage2.SetPosition({ imagePos.x,imagePos.y- windowSize.y * 0.9f,0 });
	uiWidthEdgeImage2.SetSize({ 11.1*0.95f,0.3f,0 });
	AddComponent<Image>(uiWidthEdgeImage2);

	Image uiHeightEdgeImage1(this);
	uiHeightEdgeImage1.Load("Assets/Image/UIEdge_Height.png");
	uiHeightEdgeImage1.SetPosition({ imagePos.x + windowSize.x * 0.95f,imagePos.y,0 });
	uiHeightEdgeImage1.SetSize({0.3f,7,0 });
	AddComponent<Image>(uiHeightEdgeImage1);
	Image uiHeightEdgeImage2(this);
	uiHeightEdgeImage2.Load("Assets/Image/UIEdge_Height.png");
	uiHeightEdgeImage2.SetPosition({ imagePos.x - windowSize.x * 0.95f,imagePos.y,0 });
	uiHeightEdgeImage2.SetSize({ 0.3f,7,0 });
	AddComponent<Image>(uiHeightEdgeImage2);

	Image uiCornerImage1(this);
	uiCornerImage1.Load("Assets/Image/UIEdge_Corner.png");
	uiCornerImage1.SetPosition({ imagePos.x + windowSize.x * 0.95f,imagePos.y + windowSize.y*0.901f,0 });
	uiCornerImage1.SetSize({ 0.3f,0.3f,0 });
	AddComponent<Image>(uiCornerImage1);

	Image uiCornerImage2(this);
	uiCornerImage2.Load("Assets/Image/UIEdge_Corner.png");
	uiCornerImage2.SetPosition({ imagePos.x + windowSize.x * 0.9495f,imagePos.y - windowSize.y * 0.901f,0 });
	uiCornerImage2.SetSize({ 0.3f,0.3f,0 });
	uiCornerImage2.SetRotation({ 0,0,-90 });
	AddComponent<Image>(uiCornerImage2);

	Image uiCornerImage3(this);
	uiCornerImage3.Load("Assets/Image/UIEdge_Corner.png");
	uiCornerImage3.SetPosition({ imagePos.x - windowSize.x * 0.9505f,imagePos.y - windowSize.y * 0.901f,0 });
	uiCornerImage3.SetSize({ 0.3f,0.3f,0 });
	uiCornerImage3.SetRotation({ 0,0,180 });
	AddComponent<Image>(uiCornerImage3);

	Image uiCornerImage4(this);
	uiCornerImage4.Load("Assets/Image/UIEdge_Corner.png");
	uiCornerImage4.SetPosition({ imagePos.x - windowSize.x * 0.95f,imagePos.y + windowSize.y * 0.9f,0 });
	uiCornerImage4.SetSize({ 0.3f,0.3f,0 });
	uiCornerImage4.SetRotation({ 0,0,90 });
	AddComponent<Image>(uiCornerImage4);


	Instantiate<P_MP_CraftUI_CraftPot>(this);
}

void P_MP_CraftUI_PrepareUI::Start()
{
}

void P_MP_CraftUI_PrepareUI::Update()
{
}

void P_MP_CraftUI_PrepareUI::Release()
{
}
