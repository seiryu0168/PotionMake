#include "P_CP_CollectedItemUI.h"
#include"Engine/Systems/ImageSystem.h"
#include"Engine/Systems/TextSystem.h"
#include"PickupedItem.h"
#include"Player_CollectionPart.h"
#include"InterSceneData.h"
#include"ResourceStatusData.h"
#include"CloseButton.h"
P_CP_CollectedItemUI::P_CP_CollectedItemUI(Object* parent)
	:GameObject(parent,"P_CP_CollectedItemUI"),
	uiPos_({0.5,0,0})
{
}

P_CP_CollectedItemUI::~P_CP_CollectedItemUI()
{
}

void P_CP_CollectedItemUI::Initialize()
{
	CreateBase();
	Player_CollectionPart* player = (Player_CollectionPart*)FindObject("Player_CollectionPart");
	XMFLOAT2 pos = { -0.32f,0.56f };
	int stockCount = 0;
	ResourceStatusData* rData = InterSceneData::GetData<ResourceStatusData>("ResourceData");
	for (auto& itr : player->GetItem())
	{
		PickupedItem* item = Instantiate<PickupedItem>(this);
		item->SetItemData(itr.first,
						  rData->resourceDataMap_[itr.first].resourceName_,
						  itr.second,
						  rData->resourceDataMap_[itr.first].resourceImageName_,
						  { uiPos_.x + pos.x,uiPos_.y + pos.y,0 });
		itemNumList_.push_back(itr.first);
		pos.x += 0.16f;
		if ((stockCount+1) % 5 == 0)
		{
			pos.x = -0.32f;
			pos.y -= 0.28f;
		}
		stockCount++;
	}
	for (stockCount; stockCount < 25; stockCount++)
	{
		Image backImage(this);
		backImage.Load("Assets/Image/ItemBaseImage.png");
		backImage.SetPosition({ uiPos_.x + pos.x,uiPos_.y + pos.y,0 });
		AddComponent<Image>(backImage);
		pos.x += 0.16f;
		if ((stockCount + 1) % 5 == 0)
		{
			pos.x = -0.32f;
			pos.y -= 0.28f;
		}
	}
}

void P_CP_CollectedItemUI::Start()
{
}

void P_CP_CollectedItemUI::Update()
{
}

void P_CP_CollectedItemUI::CreateBase()
{
	XMFLOAT3 windowSize;
	XMFLOAT3 imageRatio;
	Image uiBaseImage(this);
	uiBaseImage.Load("Assets/Image/UIBaseImage2.png");
	uiBaseImage.SetPosition({ uiPos_.x,uiPos_.y,0 });
	uiBaseImage.SetSize({ 16 * 0.8f,16 * 0.8f,0 });
	windowSize = uiBaseImage.GetSizeAtPixel();
	imageRatio = uiBaseImage.GetSize();
	AddComponent<Image>(uiBaseImage);

	windowSize = { windowSize.x / (Direct3D::GetScreenWidth()),
				   windowSize.y / (Direct3D::GetScreenHeight()),0 };
	Image uiWidthEdgeImage1(this);
	uiWidthEdgeImage1.Load("Assets/Image/UIEdge_Width.png");
	uiWidthEdgeImage1.SetPosition({ uiPos_.x,uiPos_.y + windowSize.y * 0.95f,0 });
	uiWidthEdgeImage1.SetSize({ imageRatio.x * 0.95f,0.3f,0 });
	AddComponent<Image>(uiWidthEdgeImage1);
	Image uiWidthEdgeImage2(this);
	uiWidthEdgeImage2.Load("Assets/Image/UIEdge_Width.png");
	uiWidthEdgeImage2.SetPosition({ uiPos_.x,uiPos_.y - windowSize.y * 0.95f,0 });
	uiWidthEdgeImage2.SetSize({ imageRatio.x * 0.95f,0.3f,0 });
	AddComponent<Image>(uiWidthEdgeImage2);

	Image uiHeightEdgeImage1(this);
	uiHeightEdgeImage1.Load("Assets/Image/UIEdge_Height.png");
	uiHeightEdgeImage1.SetPosition({ uiPos_.x + windowSize.x * 0.95f,uiPos_.y,0 });
	uiHeightEdgeImage1.SetSize({ 0.3f,imageRatio.y * 0.95f,0 });
	AddComponent<Image>(uiHeightEdgeImage1);
	Image uiHeightEdgeImage2(this);
	uiHeightEdgeImage2.Load("Assets/Image/UIEdge_Height.png");
	uiHeightEdgeImage2.SetPosition({ uiPos_.x - windowSize.x * 0.95f,uiPos_.y,0 });
	uiHeightEdgeImage2.SetSize({ 0.3f,imageRatio.y * 0.95f,0 });
	AddComponent<Image>(uiHeightEdgeImage2);

	Image uiCornerImage1(this);
	uiCornerImage1.Load("Assets/Image/UIEdge_Corner.png");
	uiCornerImage1.SetPosition({ uiPos_.x + windowSize.x * 0.95f,uiPos_.y + windowSize.y * 0.951f,0 });
	uiCornerImage1.SetSize({ 0.3f,0.3f,0 });
	AddComponent<Image>(uiCornerImage1);

	Image uiCornerImage2(this);
	uiCornerImage2.Load("Assets/Image/UIEdge_Corner.png");
	uiCornerImage2.SetPosition({ uiPos_.x + windowSize.x * 0.9495f,uiPos_.y - windowSize.y * 0.951f,0 });
	uiCornerImage2.SetSize({ 0.3f,0.3f,0 });
	uiCornerImage2.SetRotation({ 0,0,-90 });
	AddComponent<Image>(uiCornerImage2);

	Image uiCornerImage3(this);
	uiCornerImage3.Load("Assets/Image/UIEdge_Corner.png");
	uiCornerImage3.SetPosition({ uiPos_.x - windowSize.x * 0.9505f,uiPos_.y - windowSize.y * 0.951f,0 });
	uiCornerImage3.SetSize({ 0.3f,0.3f,0 });
	uiCornerImage3.SetRotation({ 0,0,180 });
	AddComponent<Image>(uiCornerImage3);

	Image uiCornerImage4(this);
	uiCornerImage4.Load("Assets/Image/UIEdge_Corner.png");
	uiCornerImage4.SetPosition({ uiPos_.x - windowSize.x * 0.95f,uiPos_.y + windowSize.y * 0.95f,0 });
	uiCornerImage4.SetSize({ 0.3f,0.3f,0 });
	uiCornerImage4.SetRotation({ 0,0,90 });
	AddComponent<Image>(uiCornerImage4);
}

void P_CP_CollectedItemUI::SetSelectFlag(bool flag)
{
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
	{
		((PickupedItem*)itr->get())->SetCanSelect(false);
	}
}

void P_CP_CollectedItemUI::Release()
{
}
