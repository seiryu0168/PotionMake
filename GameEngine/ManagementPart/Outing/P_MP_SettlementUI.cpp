#include "P_MP_SettlementUI.h"
#include "P_MP_SettlementUI_PotionList.h"
#include "P_MP_SettlementUI_TotalGain.h"
#include "SettlementUI_EarningTransition.h"
#include "../../InterSceneData.h"
#include "../../Engine/Systems/ImageSystem.h"
#include "../../InterSceneData.h"
#include "../../PlayerData.h"
#include "../../ResourceStatusData.h"
#include "../../CloseButton.h"
P_MP_SettlementUI::P_MP_SettlementUI(Object* parent)
	:GameObject(parent,"P_MP_SettlementUI"),
	fadeImageNum_(-1),
	time_(0)
{
}

P_MP_SettlementUI::~P_MP_SettlementUI()
{
}

void P_MP_SettlementUI::Initialize()
{
	Image backImage(this);
	backImage.Load("Assets/Image/UIBaseImage2.png");
	//backImage.SetColor({ 0,0,0 });
	backImage.SetSize({ 32,20,0 });
	AddComponent<Image>(backImage);
	int totalGain = 0;
	PlayerData& pData = *InterSceneData::GetData<PlayerData>("Data01");
	ResourceStatusData::ResourceStatus rData = InterSceneData::GetData<ResourceStatusData>("ResourceData")->newsPaperList_[pData.newsPaperNumber_];
	for (PlayerData::PotionData& potionData : pData.potionDataList_)
	{
		if(potionData.isSale_)
		{
			
			totalGain += potionData.price_*CalcSellCount(pData.newsPaperNumber_,potionData.topStatus_);
		}
	}
	pData.gainList_.erase(pData.gainList_.begin());
	pData.gainList_.push_back(totalGain);
	Instantiate<P_MP_SettlementUI_TotalGain>(this)->SetData(totalGain,"ëÂê∑ãµ!");
	Instantiate<SettlementUI_EarningTransition>(this)->SetData(pData.gainList_);
	Instantiate<P_MP_SettlementUI_PotionList>(this)->CreateListUI(pData.potionDataList_);
	pData.newsPaperNumber_ = ++pData.newsPaperNumber_ % 4;
	

	Instantiate<CloseButton>(this);

	Image fadeImage(this);
	fadeImage.Load("Assets/Image/PotionManagerUIBase1.png");
	fadeImage.SetSize({ 2,2,0 });
	fadeImage.SetLayer(2);
	fadeImage.SetColor(0);
	fadeImageNum_ = AddComponent<Image>(fadeImage);
}

void P_MP_SettlementUI::Start()
{
}

void P_MP_SettlementUI::Update()
{
	if (time_ <= 0.5f)
	{
		time_ += 0.016f;
		GetComponent<Image>(fadeImageNum_).SetAlpha((0.5f - time_) / 0.5f);
	}
}

void P_MP_SettlementUI::CreateResoultUI()
{

}

int P_MP_SettlementUI::CalcSellCount(int newsNum, int topStatus)
{
	ResourceStatusData::ResourceStatus rData = InterSceneData::GetData<ResourceStatusData>("ResourceData")->newsPaperList_[newsNum];
	int count = 5;
	for (int i = 0; i < 5;i++)
	{
		int bit = 1 << i;
		if (topStatus & bit && rData.resourceNumber_ & bit)
		{
			count *= 1.5f;
		}
	}
	return count;
}

void P_MP_SettlementUI::Release()
{
	pParent_->KillMe();
}
