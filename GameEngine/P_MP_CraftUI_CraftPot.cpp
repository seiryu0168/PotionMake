#include "P_MP_CraftUI_CraftPot.h"
#include"Engine/Systems/ImageSystem.h"
#include"Engine/Systems/TextSystem.h"
#include"P_MP_CraftUI_PotionStatusUI.h"
#include"ResourceItem.h"
#include"ResourceItemSlot.h"
#include"InterSceneData.h"
#include"PlayerData.h"
#include"ResourceStatusData.h"
#include"P_MP_CraftUI_PrepareButton.h"
namespace
{
	std::string statusName = "�ؖh�����^";
}

P_MP_CraftUI_CraftPot::P_MP_CraftUI_CraftPot(Object* parent)
	:GameObject(parent,"P_MP_CraftUI_CraftPot"),
	standPosition_({-0.8f,0.5f})
{
}

P_MP_CraftUI_CraftPot::~P_MP_CraftUI_CraftPot()
{
}

void P_MP_CraftUI_CraftPot::Initialize()
{
	//Image potImage(this);
	//potImage.Load("Assets/Image/PreparePot03.png");
	//potImage.SetPosition({ -0.06f,0.05f,0 });
	//potImage.SetSize({ 0.5f,0.5f,0 });
	//AddComponent<Image>(potImage);

	XMFLOAT2 itemPos = { 0,0 };
	for (int i = 0; i < 12; i++)
	{
		GameObject* item = Instantiate<ResourceItemSlot>(this);
		item->GetComponent<Image>().SetPosition({ standPosition_.x+itemPos.x,standPosition_.y+itemPos.y,0 });
		XMFLOAT3 textBasePos = item->GetComponent<Image>().GetPositionAtPixel();
		item->GetComponent<Text>().SetPosition({ textBasePos.x + 10,textBasePos.y+15 });
		itemPos.x += 0.15f;
		if ((i + 1) % 4 == 0)
		{
			itemPos.x = 0;
			itemPos.y -= 0.27f;
		}
		objects_.push_back(item);
	}
	Instantiate<P_MP_CraftUI_PrepareButton>(this);
}

void P_MP_CraftUI_CraftPot::Start()
{
	potionStatusObject_ = (GameObject*)FindObject("P_MP_CraftUI_PotionStatusUI");
}

void P_MP_CraftUI_CraftPot::Update()
{
}

void P_MP_CraftUI_CraftPot::AddResourceData(int itemNum,std::string resourceName, std::string imageName)
{
	//�f�[�^�}�b�v�Ƀf�[�^������������
	if (dataMap_.find(itemNum) == dataMap_.end())
	{
		//�f�ރf�[�^���f�[�^�}�b�v�ɒǉ�
		ResourceData data{ resourceName,imageName,1 };
		dataMap_.insert({ itemNum, data });

		//�ǉ������f�ނ�\��
		DisplayResource(itemNum);
		
		//�f�ނ̃f�[�^���p�����[�^�ɔ��f
		((P_MP_CraftUI_PotionStatusUI*)potionStatusObject_)->ApplicationStatusData(CalcPotionStatus());
		return;
	}


	//�f�[�^�}�b�v�Ƀf�[�^����������
	//�f�ނ̐��𑝂₷
	dataMap_[itemNum].resourceCount_++;

	//�f�ނ̐����X�V
	for (GameObject* obj : objects_)
	{
		if (((ResourceItemSlot*)obj)->GetItemNumber() == itemNum)
		{
			((ResourceItemSlot*)obj)->AddCount(1);
			//�p�����[�^�ɔ��f
			((P_MP_CraftUI_PotionStatusUI*)potionStatusObject_)->ApplicationStatusData(CalcPotionStatus());
			break;
		}
	}
}

bool P_MP_CraftUI_CraftPot::SubResourceData(int itemNum)
{
	if (dataMap_.find(itemNum) == dataMap_.end())
		return false;

	//�f�ނ̐������炷
	dataMap_.find(itemNum)->second.resourceCount_--;
	
	//�����f�ނ̐���0�ɂȂ�����
	if (dataMap_.find(itemNum)->second.resourceCount_ <= 0)
	{
		//�Y������f�ނ̘g���f�t�H���g�ɖ߂�
		HiddenResource(itemNum);
		//�p�����[�^�ɔ��f
		((P_MP_CraftUI_PotionStatusUI*)potionStatusObject_)->ApplicationStatusData(CalcPotionStatus());
		//�f�[�^�}�b�v����폜
		dataMap_.erase(itemNum);
		return true;
	}
	//�f�ނ̐���0����Ȃ��ꍇ
	for (GameObject* obj : objects_)
	{
		//itemNum����v����z���X�V
		if (((ResourceItemSlot*)obj)->GetItemNumber() == itemNum)
		{
			((ResourceItemSlot*)obj)->SubCount(1);
			
			//�p�����[�^�ɔ��f
			((P_MP_CraftUI_PotionStatusUI*)potionStatusObject_)->ApplicationStatusData(CalcPotionStatus());
			break;
		}
	}
	return true;
}

void P_MP_CraftUI_CraftPot::AddProcessData(int processNum)
{
	ProcessData data;
	data.procssNum_ = processNum;
	processList_.push_back(data);
	//�p�����[�^�ɔ��f
	((P_MP_CraftUI_PotionStatusUI*)potionStatusObject_)->ApplicationStatusData(CalcPotionStatus());
}

void P_MP_CraftUI_CraftPot::SubProcessData(int processNum)
{
	for (auto itr = processList_.begin(); itr != processList_.end();itr++)
	{
		if (itr->procssNum_ == processNum)
		{
			itr = processList_.erase(itr);
			//�p�����[�^�ɔ��f
			((P_MP_CraftUI_PotionStatusUI*)potionStatusObject_)->ApplicationStatusData(CalcPotionStatus());
			return;
		}
	}
}

void P_MP_CraftUI_CraftPot::DisplayResource(int itemNum)
{
	for (int i = 0; i < objects_.size(); i++)
	{
		if (!((ResourceItemSlot*)objects_[i])->HaveItem())
		{
			((ResourceItemSlot*)objects_[i])->SetItem(dataMap_[itemNum].imageName_,itemNum);
			return;
		}
	}
}

void P_MP_CraftUI_CraftPot::HiddenResource(int itemNum)
{
	for (int i = 0; i < objects_.size(); i++)
	{
		if (((ResourceItemSlot*)objects_[i])->GetItemNumber()==itemNum)
		{
			((ResourceItemSlot*)objects_[i])->ItemEmpty();
			return;
		}
	}
}

void P_MP_CraftUI_CraftPot::CreatePotion()
{
	if (dataMap_.empty())
		return;

	PlayerData* data = InterSceneData::GetData<PlayerData>("Data01");
	std::vector<float> status = CalcPotionStatus();

	std::string potionName = "";
	bool isMax_ = false;
	//XMFLOAT3 color = { 0,0,0 };
	int maxStatus = 0;
	int lastStatus = 0;
	//�ł��l���傫���X�e�[�^�X��T��
	for (int i = 4; i > -1; i--)
	{
		float colorRatio = 1.0f;
		for (int j = 0; j < 5; j++)
		{
			if ((int)status[j] == i)
			{
				maxStatus |= 1<<j;
				lastStatus = j;
				//potionName += statusName[i];
				
				//colorRatio = 1/(PotionColorArray[j].x + PotionColorArray[j].y + PotionColorArray[j].z);

				////�F�𑫂�
				//potionColor_.x += PotionColorArray[j].x * colorRatio;
				//potionColor_.y += PotionColorArray[j].y * colorRatio;
				//potionColor_.z += PotionColorArray[j].z * colorRatio;
				//colorRatio *= 0.13f;
				isMax_ = true;
			}
		}
		if (isMax_)
			break;
	}

	int statusCount = 0;
	for (int i = 0; i < lastStatus+1; i++)
	{
		if (maxStatus & (1 << i))
		{
			statusCount++;
			std::string chr = { statusName[2 * i],statusName[(2 * i) + 1] };
			potionName += chr;
			// potionName += statusName[(2 * i) + 1];

			if (i != lastStatus)
				potionName += "�E";
		}
	}

	if (statusCount >= 4)
		potionName = "���\�|�[�V����" + potionName;
	else
		potionName += "�̃|�[�V����";

	PlayerData::PotionData pData;
	pData.potionName_ = potionName;
	pData.isSale_ = false;
	pData.potionStatus_ = status;
	data->potionDataList_.push_back(pData);
}

std::vector<float> P_MP_CraftUI_CraftPot::CalcPotionStatus()
{
	std::vector<float> statusList = { 0,0,0,0,0 };
	ResourceStatusData* data = InterSceneData::GetData<ResourceStatusData>("ResourceData");
	//�L�[�����Ƃɑf�ނ̃p�����[�^�̍��v�l���v�Z
	for (auto itr = dataMap_.begin(); itr != dataMap_.end();itr++)
	{
		statusList[0] += data->resourceDataMap_[itr->first].status00_ * itr->second.resourceCount_;
		statusList[1] += data->resourceDataMap_[itr->first].status01_ * itr->second.resourceCount_;
		statusList[2] += data->resourceDataMap_[itr->first].status02_ * itr->second.resourceCount_;
		statusList[3] += data->resourceDataMap_[itr->first].status03_ * itr->second.resourceCount_;
		statusList[4] += data->resourceDataMap_[itr->first].status04_ * itr->second.resourceCount_;
	}
	//���H�ɂ��p�����[�^�̕␳�𔽉f
	for (auto &process : processList_)
	{
		statusList[0] = statusList[0] * data->processDataMap_[process.procssNum_].status00_;
		statusList[1] = statusList[1] * data->processDataMap_[process.procssNum_].status01_;
		statusList[2] = statusList[2] * data->processDataMap_[process.procssNum_].status02_;
		statusList[3] = statusList[3] * data->processDataMap_[process.procssNum_].status03_;
		statusList[4] = statusList[4] * data->processDataMap_[process.procssNum_].status04_;
	}
	return statusList;
}


void P_MP_CraftUI_CraftPot::Release()
{
}
