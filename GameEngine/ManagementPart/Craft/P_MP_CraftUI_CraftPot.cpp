#include "P_MP_CraftUI_CraftPot.h"
#include"../../Engine/Systems/ImageSystem.h"
#include"../../Engine/Systems/TextSystem.h"
#include"P_MP_CraftUI_PotionStatusUI.h"
#include"ResourceItem.h"
#include"ResourceItemSlot.h"
#include"../../InterSceneData.h"
#include"../../PlayerData.h"
#include"../../ResourceStatusData.h"
#include"Play_ManagementPart_CraftUI.h"
#include"P_MP_CraftUI_PrepareButton.h"
#include"../../InterSceneData.h"
#include"../../ResourceStatusData.h"
namespace
{
	std::string statusName = "筋防魔速運";
}

P_MP_CraftUI_CraftPot::P_MP_CraftUI_CraftPot(Object* parent)
	:GameObject(parent,"P_MP_CraftUI_CraftPot"),
	potionStatusObject_(nullptr),
	standPosition_({-0.84f,0.53f}),
	cost_(0),
	costLimit_(10)
{
}

P_MP_CraftUI_CraftPot::~P_MP_CraftUI_CraftPot()
{
}

void P_MP_CraftUI_CraftPot::Initialize()
{
	//素材を入れるための枠の画像を表示
	XMFLOAT2 itemPos = { 0,0 };
	for (int i = 0; i < 12; i++)
	{
		GameObject* item = Instantiate<ResourceItemSlot>(this);
		item->GetComponent<Image>().SetPosition({ standPosition_.x+itemPos.x,standPosition_.y+itemPos.y,0 });
		XMFLOAT3 textBasePos = item->GetComponent<Image>().GetPositionAtPixel();
		item->GetComponent<Text>().SetPosition({ textBasePos.x + 5,textBasePos.y+10 });
		itemPos.x += 0.16f;
		if ((i + 1) % 4 == 0)
		{
			itemPos.x = 0;
			itemPos.y -= 0.28f;
		}
		objects_.push_back(item);
	}

	Instantiate<P_MP_CraftUI_PrepareButton>(this);
	potionColorArray_ = InterSceneData::GetData<ResourceStatusData>("ResourceData")->statusColor_;
}

void P_MP_CraftUI_CraftPot::Start()
{
	potionStatusObject_ = (GameObject*)FindObject("P_MP_CraftUI_PotionStatusUI");
	potionStatusObject_->GetComponent<Text>().SetText(std::to_string(cost_) + "/" + std::to_string(costLimit_));
}

void P_MP_CraftUI_CraftPot::Update()
{
}

bool P_MP_CraftUI_CraftPot::AddResourceData(int itemNum,std::string resourceName, std::string imageName)
{
	if ((cost_+2) > costLimit_)
		return false;

	cost_ += 2;

	//データマップにデータが無かったら
	if (dataMap_.find(itemNum) == dataMap_.end())
	{
		//素材データをデータマップに追加
		ResourceData data{ resourceName,imageName,1 };
		dataMap_.insert({ itemNum, data });

		//追加した素材を表示
		DisplayResource(itemNum);
		
		//素材のデータをパラメータに反映
		((P_MP_CraftUI_PotionStatusUI*)potionStatusObject_)->SetStatusData(CalcPotionStatus(),std::to_string(cost_)+"/"+std::to_string(costLimit_));
		return true;
	}


	//データマップにデータがあったら
	//素材の数を増やす
	dataMap_[itemNum].resourceCount_++;

	//素材の数を更新
	for (GameObject* obj : objects_)
	{
		if (((ResourceItemSlot*)obj)->GetItemNumber() == itemNum)
		{
			((ResourceItemSlot*)obj)->AddCount(1);
			//パラメータに反映
			((P_MP_CraftUI_PotionStatusUI*)potionStatusObject_)->SetStatusData(CalcPotionStatus(), std::to_string(cost_) + "/" + std::to_string(costLimit_));
			break;
		}
	}
	return true;
}

bool P_MP_CraftUI_CraftPot::SubResourceData(int itemNum)
{
	if (dataMap_.find(itemNum) == dataMap_.end())
		return false;

	cost_ -= 2;
	//素材の数を減らす
	dataMap_.find(itemNum)->second.resourceCount_--;
	
	//もし素材の数が0になったら
	if (dataMap_.find(itemNum)->second.resourceCount_ <= 0)
	{
		//該当する素材の枠をデフォルトに戻す
		HiddenResource(itemNum);
		//パラメータに反映
		((P_MP_CraftUI_PotionStatusUI*)potionStatusObject_)->SetStatusData(CalcPotionStatus(), std::to_string(cost_) + "/" + std::to_string(costLimit_));
		//データマップから削除
		dataMap_.erase(itemNum);
		return true;
	}
	//素材の数が0じゃない場合
	for (GameObject* obj : objects_)
	{
		//itemNumが一致する奴を更新
		if (((ResourceItemSlot*)obj)->GetItemNumber() == itemNum)
		{
			((ResourceItemSlot*)obj)->SubCount(1);
			
			//パラメータに反映
			((P_MP_CraftUI_PotionStatusUI*)potionStatusObject_)->SetStatusData(CalcPotionStatus(), std::to_string(cost_) + "/" + std::to_string(costLimit_));
			break;
		}
	}
	return true;
}

bool P_MP_CraftUI_CraftPot::AddProcessData(int processNum)
{
	if((cost_ + 3) > costLimit_)
		return false;

	cost_ += 3;
	//加工方法の番号を追加
	ProcessData data;
	data.procssNum_ = processNum;
	processList_.push_back(data);
	//パラメータに反映
	((P_MP_CraftUI_PotionStatusUI*)potionStatusObject_)->SetStatusData(CalcPotionStatus(), std::to_string(cost_) + "/" + std::to_string(costLimit_));
	return true;
}

bool P_MP_CraftUI_CraftPot::SubProcessData(int processNum)
{
	if ((cost_ + 3) > costLimit_)
		return false;

	cost_ -= 3;
	//加工方法の番号を削除
	for (auto itr = processList_.begin(); itr != processList_.end(); itr++)
	{
		if (itr->procssNum_ == processNum)
		{
			itr = processList_.erase(itr);
			//パラメータに反映
			((P_MP_CraftUI_PotionStatusUI*)potionStatusObject_)->SetStatusData(CalcPotionStatus(), std::to_string(cost_) + "/" + std::to_string(costLimit_));
			return true;
		}
	}
	return false;
}

void P_MP_CraftUI_CraftPot::DisplayResource(int itemNum)
{
	//追加された素材の表示
	for (int i = 0; i < objects_.size(); i++)
	{
		if (!((ResourceItemSlot*)objects_[i])->HaveItem())
		{
			((ResourceItemSlot*)objects_[i])->SetItem(dataMap_[itemNum].resourceName_,dataMap_[itemNum].imageName_, itemNum);
			return;
		}
	}
}

void P_MP_CraftUI_CraftPot::HiddenResource(int itemNum)
{
	//素材が無くなったら消す
	for (int i = 0; i < objects_.size(); i++)
	{
		if (((ResourceItemSlot*)objects_[i])->GetItemNumber() == itemNum)
		{
			((ResourceItemSlot*)objects_[i])->ItemEmpty();
			return;
		}
	}
}

void P_MP_CraftUI_CraftPot::CreatePotion()
{
	//何も素材が無かったら何もしない
	if (dataMap_.empty())
		return;

	//ポーションのステータスを計算
	std::vector<float> status = CalcPotionStatus();

	std::string potionName = "";
	bool isMax_ = false;
	//XMFLOAT3 color = { 0,0,0 };
	int maxStatus = 0;
	int lastStatus = 0;
	int level = 0;
	XMFLOAT3 potionColor = { 0,0,0 };
	//最も値が大きいステータスを探す
	for (int i = 4; i > -1; i--)
	{
		float colorRatio = 1.0f;
		for (int j = 0; j < 5; j++)
		{
			if ((int)status[j] == i)
			{
				maxStatus |= 1 << j;
				lastStatus = j;
				
				//色を足す
				potionColor.x += potionColorArray_[j].x * colorRatio;
				potionColor.y += potionColorArray_[j].y * colorRatio;
				potionColor.z += potionColorArray_[j].z * colorRatio;
				colorRatio *= 0.13f;
				isMax_ = true;
			}
		}
		if (isMax_)
		{
			level = i+1;
			break;
		}
	}

	//ポーションの名前を生成
	int statusCount = 0;
	for (int i = 0; i < lastStatus + 1; i++)
	{
		if (maxStatus & (1 << i))
		{
			statusCount++;
			std::string chr = { statusName[2 * i],statusName[(2 * i) + 1] };
			potionName += chr;// { statusName[2 * i], statusName[(2 * i) + 1] };

			if (i != lastStatus)
				potionName += "・";
		}
	}

	//ステータスによっては名前を変える
	if (statusCount >= 4)
		potionName = "万能ポーション Lv." + std::to_string(level) + "\n" + potionName;
	else
		potionName += "のポーション Lv." + std::to_string(level);

	PlayerData* data = InterSceneData::GetData<PlayerData>("Data01");
	std::vector<int> itemNumList_;
	//素材データ更新
	for (int i = 0; i < objects_.size(); i++)
	{
		int num = ((ResourceItemSlot*)objects_[i])->GetItemNumber();
		if (num != -1)
		{

			//PlayerData::ResourceData_
			auto rData = std::find_if(data->itemDataList_.begin(), data->itemDataList_.end(), [&](PlayerData::ResourceData_ value) {return value.itemNum_ == num; });
			rData->itemCount_ = rData->itemCount_ - dataMap_[num].resourceCount_;
			itemNumList_.push_back(num);
		}

	}

	//ポーションデータ更新
	PlayerData::PotionData pData;
	pData.potionName_	= potionName;
	pData.tier_			= level;
	pData.isSale_		= false;
	pData.price_		= 100 + (200 * level);
	pData.topStatus_    = maxStatus;
	pData.potionStatus_ = status;
	pData.potionColor_  = potionColor;

	//ソート
	data->SortResourceList();
	if (data->potionDataList_.size() < 30)
		data->potionDataList_.push_back(pData);
	((Play_ManagementPart_CraftUI*)pParent_->GetParent())->DisplayCraftProcess(itemNumList_);
}

std::vector<float> P_MP_CraftUI_CraftPot::CalcPotionStatus()
{
	std::vector<float> statusList = { 0,0,0,0,0 };
	ResourceStatusData* data = InterSceneData::GetData<ResourceStatusData>("ResourceData");
	//キーをもとに素材のパラメータの合計値を計算
	for (auto itr = dataMap_.begin(); itr != dataMap_.end();itr++)
	{
		statusList[0] += data->resourceDataMap_[itr->first].status00_ * itr->second.resourceCount_;
		statusList[1] += data->resourceDataMap_[itr->first].status01_ * itr->second.resourceCount_;
		statusList[2] += data->resourceDataMap_[itr->first].status02_ * itr->second.resourceCount_;
		statusList[3] += data->resourceDataMap_[itr->first].status03_ * itr->second.resourceCount_;
		statusList[4] += data->resourceDataMap_[itr->first].status04_ * itr->second.resourceCount_;
	}
	//加工によるパラメータの補正を反映
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
