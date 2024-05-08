#include "P_MP_CraftUI_ResourceStockUI.h"
#include "ResourceItem.h"
#include "P_MP_CraftUI_ProcessUI.h"
#include "ResourceMenuChangeButton.h"
#include "../../Engine/Systems/ImageSystem.h"
#include "../../Engine/Systems/TextSystem.h"
#include "../../Engine/ResourceManager/Audio.h"
#include "../../InterSceneData.h"
#include "../../PlayerData.h"
#include "../../ResourceStatusData.h"
P_MP_CraftUI_ResourceStockUI::P_MP_CraftUI_ResourceStockUI(Object* parent)
	:GameObject(parent,"P_MP_CraftUI_ResourceStockUI"),
	uiPos_({0,0,0})
{
}

P_MP_CraftUI_ResourceStockUI::~P_MP_CraftUI_ResourceStockUI()
{
}

void P_MP_CraftUI_ResourceStockUI::Initialize()
{
	//UI�̓y��ƂȂ�摜��p��
	uiPos_ = { 0.5f,-0.13f,0 };

	CreateBase();
	//UI�̃J�e�S����\��
	Text uiTitleText(this);
	uiTitleText.SetText("�f��");
	uiTitleText.SetPosition({ 1200,30 });
	AddComponent<Text>(uiTitleText);

	//�f�ނ̉摜���Z�[�u�f�[�^���Q�Ƃ��ĕ\��
	XMFLOAT2 itemPos = { -0.28f,0.62f };
	PlayerData* data = InterSceneData::GetData<PlayerData>("Data01");
	ResourceStatusData* rData = InterSceneData::GetData<ResourceStatusData>("ResourceData");
	for (int i = 0; i < 30; i++)
	{
		//���\�[�X�I�u�W�F�N�g�̐���
		GameObject* item = Instantiate<ResourceItem>(this);


		int resourceCount = 0;
		//�ԍ����Z�[�u�f�[�^�͈͓̔���������
		if (i < data->itemDataList_.size())
		{
			//�f�ނ̌�
			resourceCount = data->itemDataList_[i].itemCount_;
			//�摜��
			std::string imageName = rData->resourceDataMap_[data->itemDataList_[i].itemNum_].resourceImageName_;
			//�摜�ǂݍ���
			((ResourceItem*)item)->LoadItem(imageName, resourceCount);
			//�ʒu�ݒ�
			item->GetComponent<Image>().SetPosition({ uiPos_.x + itemPos.x,uiPos_.y + itemPos.y,0 });
			item->GetComponent<Image>(1).SetPosition({ uiPos_.x + itemPos.x,uiPos_.y + itemPos.y,0 });
			//�e�L�X�g�̈ʒu�ݒ�
			XMFLOAT3 textBasePos = item->GetComponent<Image>().GetPositionAtPixel();
			item->GetComponent<Text>().SetPosition({ textBasePos.x + 5,textBasePos.y + 10 });
			((ResourceItem*)item)->SetItemNum(rData->resourceDataMap_[data->itemDataList_[i].itemNum_].resourceNumber_);
			if (resourceCount > 0)
			{
				((ResourceItem*)item)->itemName_ = rData->resourceDataMap_[data->itemDataList_[i].itemNum_].resourceName_;
			}
		}
		else
		{
			((ResourceItem*)item)->LoadItem("ItemSlotImage.png", resourceCount);
			//�ʒu�ݒ�
			item->GetComponent<Image>().SetPosition({ uiPos_.x + itemPos.x,uiPos_.y + itemPos.y,0 });
		}
		itemPos.x += 0.14f;
		if ((i + 1) % 5 == 0)
		{
			itemPos.x = -0.28f;
			itemPos.y -= 0.25f;
		}
		resourceObjects_.push_back(item);
	}

	//���H���@�I��UI
	float posY = 0.5f;
	for (int i=0;i<rData->processDataMap_.size();i++)
	{
		ResourceStatusData::ResourceStatus pData = rData->processDataMap_[i];
		GameObject* processUI = Instantiate<P_MP_CraftUI_ProcessUI>(this);
		((P_MP_CraftUI_ProcessUI*)processUI)->CreateBase({ uiPos_.x,uiPos_.y + posY,0 });
		processUI->GetComponent<Image>().SetPosition({ uiPos_.x,uiPos_.y+posY,0 });
		//processUI->GetComponent<Image>().SetSize({ 1,0.3f,0 });
		((P_MP_CraftUI_ProcessUI*)processUI)->SetProcessImage(pData.resourceImageName_);
		((P_MP_CraftUI_ProcessUI*)processUI)->SetProcessData(pData.resourceName_);
		((P_MP_CraftUI_ProcessUI*)processUI)->SetProcessNumber(i);
		processObjects_.push_back(processUI);
		posY += -0.5f;
	}
	//UI�ύX�p�{�^��
	GameObject* changeButton = Instantiate<ResourceMenuChangeButton>(this);
	changeButton->GetComponent<Image>(0).SetPosition({ uiPos_.x + 0.423f,uiPos_.y+0.5f,0 });
	changeButton->GetComponent<Image>(1).SetPosition({ uiPos_.x + 0.423f,uiPos_.y,0 });

	ModeChange(ResourceMenuMode::ResourceSelect);
}

void P_MP_CraftUI_ResourceStockUI::Start()
{
}

void P_MP_CraftUI_ResourceStockUI::Update()
{
}

void P_MP_CraftUI_ResourceStockUI::CreateBase()
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

void P_MP_CraftUI_ResourceStockUI::ModeChange(ResourceMenuMode mode)
{
	//���[�h�ɂ���ĕ\��������̂�؂�ւ���
	mode_ = mode; 
	switch (mode_)
	{
	case ResourceMenuMode::ResourceSelect:
		for (int i = 0; i < resourceObjects_.size(); i++)
			((ResourceItem*)resourceObjects_[i])->ActiveUI(true);

		for(int i = 0; i < processObjects_.size(); i++)
			((P_MP_CraftUI_ProcessUI*)processObjects_[i])->ActiveUI(false);
		GetComponent<Text>().SetText("�f��");
		break;
	case ResourceMenuMode::ProcessSelect:
		for (int i = 0; i < processObjects_.size(); i++)
			((P_MP_CraftUI_ProcessUI*)processObjects_[i])->ActiveUI(true);

		for (int i = 0; i < resourceObjects_.size(); i++)
			((ResourceItem*)resourceObjects_[i])->ActiveUI(false);
		GetComponent<Text>().SetText("���H���@");
		break;
	default:
		break;
	}
}

void P_MP_CraftUI_ResourceStockUI::Release()
{
}
