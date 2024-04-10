#include "P_MP_CraftUI_ResourceStockUI.h"
#include"ResourceItem.h"
#include"Engine/Systems/ImageSystem.h"
#include"Engine/Systems/TextSystem.h"
#include"InterSceneData.h"
#include"P_MP_CraftUI_ProcessUI.h"
#include"ResourceMenuChangeButton.h"
#include"PlayerData.h"
#include"ResourceStatusData.h"
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
	Image uiBaseImage(this);
	uiBaseImage.SetLayer(1);
	uiBaseImage.Load("Assets/Image/PotionManagerUIBase1.png");
	uiBaseImage.SetPosition(uiPos_);
	uiBaseImage.SetSize({ 0.7f,0.87f,0 });
	AddComponent<Image>(uiBaseImage);

	//UI�̃J�e�S����\��
	Text uiTitleText(this);
	uiTitleText.SetText("�f��");
	uiTitleText.SetPosition({ 1200,30 });
	AddComponent<Text>(uiTitleText);

	//�f�ނ̉摜���Z�[�u�f�[�^���Q�Ƃ��ĕ\��
	XMFLOAT2 itemPos = { -0.3f,0.68f };
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
			item->GetComponent<Text>().SetPosition({ textBasePos.x + 10,textBasePos.y + 15 });
			((ResourceItem*)item)->SetItemNum(rData->processDataMap_[data->itemDataList_[i].itemNum_].resourceNumber_);
			if (resourceCount > 0)
			{
				((ResourceItem*)item)->itemName_ = rData->resourceDataMap_[data->itemDataList_[i].itemNum_].resourceName_;
				//item->GetComponent<Image>().SetSize({ 128.0f / 512.0f,128.0f / 521.0f,0 });
			}
		}
		else
		{
			((ResourceItem*)item)->LoadItem("ItemSlotImage.png", resourceCount);
			//�ʒu�ݒ�
			item->GetComponent<Image>().SetPosition({ uiPos_.x + itemPos.x,uiPos_.y + itemPos.y,0 });
		}
		itemPos.x += 0.15f;
		if ((i + 1) % 5 == 0)
		{
			itemPos.x = -0.3f;
			itemPos.y -= 0.27f;
		}
		resourceObjects_.push_back(item);
	}

	//���H���@�I��UI
	float posY = 0.5f;
	for (int i = 0; i < 3; i++)
	{
		GameObject* processUI = Instantiate<P_MP_CraftUI_ProcessUI>(this);
		((P_MP_CraftUI_ProcessUI*)processUI)->SetProcessImage("Assets/Image/SelectImage4.png");
		processUI->GetComponent<Image>().SetSize({ 1,0.3f,0 });
		processUI->GetComponent<Image>().SetPosition({ uiPos_.x,uiPos_.y+posY,0 });
		((P_MP_CraftUI_ProcessUI*)processUI)->SetProcessNumber(i);
		processObjects_.push_back(processUI);
		posY += -0.5f;
	}
	//UI�ύX�p�{�^��
	GameObject* changeButton = Instantiate<ResourceMenuChangeButton>(this);
	changeButton->GetComponent<Image>(0).SetPosition({ uiPos_.x + 0.4f,uiPos_.y+0.5f,0 });
	changeButton->GetComponent<Image>(1).SetPosition({ uiPos_.x + 0.4f,uiPos_.y,0 });
	ModeChange(ResourceMenuMode::ResourceSelect);
	
}

void P_MP_CraftUI_ResourceStockUI::Start()
{
}

void P_MP_CraftUI_ResourceStockUI::Update()
{
}

void P_MP_CraftUI_ResourceStockUI::ModeChange(ResourceMenuMode mode)
{
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
