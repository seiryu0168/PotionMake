#include "P_CP_CollectionedItemUI.h"
#include"Engine/Systems/ImageSystem.h"
P_CP_CollectionedItemUI::P_CP_CollectionedItemUI(Object* parent)
	:GameObject(parent,"P_CP_CollectionedItemUI"),
	uiPos_({0.5,0,0})
{
}

P_CP_CollectionedItemUI::~P_CP_CollectionedItemUI()
{
}

void P_CP_CollectionedItemUI::Initialize()
{
	CreateBase();
}

void P_CP_CollectionedItemUI::Start()
{
}

void P_CP_CollectionedItemUI::Update()
{
}

void P_CP_CollectionedItemUI::CreateBase()
{
	XMFLOAT3 windowSize;
	XMFLOAT3 imageRatio;
	Image uiBaseImage(this);
	uiBaseImage.Load("Assets/Image/UIBaseImage2.png");
	uiBaseImage.SetLayer(1);
	uiBaseImage.SetPosition({ uiPos_.x,uiPos_.y,0 });
	uiBaseImage.SetSize({ 16 * 0.7f,16 * 0.87f,0 });
	windowSize = uiBaseImage.GetSizeAtPixel();
	imageRatio = uiBaseImage.GetSize();
	AddComponent<Image>(uiBaseImage);

	windowSize = { windowSize.x / (Direct3D::GetScreenWidth()),
				   windowSize.y / (Direct3D::GetScreenHeight()),0 };
	Image uiWidthEdgeImage1(this);
	uiWidthEdgeImage1.Load("Assets/Image/UIEdge_Width.png");
	uiWidthEdgeImage1.SetLayer(1);
	uiWidthEdgeImage1.SetPosition({ uiPos_.x,uiPos_.y + windowSize.y * 0.95f,0 });
	uiWidthEdgeImage1.SetSize({ imageRatio.x * 0.95f,0.3f,0 });
	AddComponent<Image>(uiWidthEdgeImage1);
	Image uiWidthEdgeImage2(this);
	uiWidthEdgeImage2.Load("Assets/Image/UIEdge_Width.png");
	uiWidthEdgeImage2.SetLayer(1);
	uiWidthEdgeImage2.SetPosition({ uiPos_.x,uiPos_.y - windowSize.y * 0.95f,0 });
	uiWidthEdgeImage2.SetSize({ imageRatio.x * 0.95f,0.3f,0 });
	AddComponent<Image>(uiWidthEdgeImage2);

	Image uiHeightEdgeImage1(this);
	uiHeightEdgeImage1.Load("Assets/Image/UIEdge_Height.png");
	uiHeightEdgeImage1.SetLayer(1);
	uiHeightEdgeImage1.SetPosition({ uiPos_.x + windowSize.x * 0.95f,uiPos_.y,0 });
	uiHeightEdgeImage1.SetSize({ 0.3f,imageRatio.y * 0.95f,0 });
	AddComponent<Image>(uiHeightEdgeImage1);
	Image uiHeightEdgeImage2(this);
	uiHeightEdgeImage2.Load("Assets/Image/UIEdge_Height.png");
	uiHeightEdgeImage2.SetLayer(1);
	uiHeightEdgeImage2.SetPosition({ uiPos_.x - windowSize.x * 0.95f,uiPos_.y,0 });
	uiHeightEdgeImage2.SetSize({ 0.3f,imageRatio.y * 0.95f,0 });
	AddComponent<Image>(uiHeightEdgeImage2);

	Image uiCornerImage1(this);
	uiCornerImage1.Load("Assets/Image/UIEdge_Corner.png");
	uiCornerImage1.SetLayer(1);
	uiCornerImage1.SetPosition({ uiPos_.x + windowSize.x * 0.95f,uiPos_.y + windowSize.y * 0.951f,0 });
	uiCornerImage1.SetSize({ 0.3f,0.3f,0 });
	AddComponent<Image>(uiCornerImage1);

	Image uiCornerImage2(this);
	uiCornerImage2.Load("Assets/Image/UIEdge_Corner.png");
	uiCornerImage2.SetLayer(1);
	uiCornerImage2.SetPosition({ uiPos_.x + windowSize.x * 0.9495f,uiPos_.y - windowSize.y * 0.951f,0 });
	uiCornerImage2.SetSize({ 0.3f,0.3f,0 });
	uiCornerImage2.SetRotation({ 0,0,-90 });
	AddComponent<Image>(uiCornerImage2);

	Image uiCornerImage3(this);
	uiCornerImage3.Load("Assets/Image/UIEdge_Corner.png");
	uiCornerImage3.SetLayer(1);
	uiCornerImage3.SetPosition({ uiPos_.x - windowSize.x * 0.9505f,uiPos_.y - windowSize.y * 0.951f,0 });
	uiCornerImage3.SetSize({ 0.3f,0.3f,0 });
	uiCornerImage3.SetRotation({ 0,0,180 });
	AddComponent<Image>(uiCornerImage3);

	Image uiCornerImage4(this);
	uiCornerImage4.Load("Assets/Image/UIEdge_Corner.png");
	uiCornerImage4.SetLayer(1);
	uiCornerImage4.SetPosition({ uiPos_.x - windowSize.x * 0.95f,uiPos_.y + windowSize.y * 0.95f,0 });
	uiCornerImage4.SetSize({ 0.3f,0.3f,0 });
	uiCornerImage4.SetRotation({ 0,0,90 });
	AddComponent<Image>(uiCornerImage4);
}

void P_CP_CollectionedItemUI::Release()
{
}
