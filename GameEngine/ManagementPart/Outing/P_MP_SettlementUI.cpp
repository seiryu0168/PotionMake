#include "P_MP_SettlementUI.h"
#include "P_MP_SettlementUI_PotionList.h"
#include "P_MP_SettlementUI_TotalGain.h"
#include "SettlementUI_EarningTransition.h"
#include "../../InterSceneData.h"
#include "../../Engine/DirectX_11/Input.h"
#include "../../Engine/ResourceManager/AudioManager.h"
#include "../../Engine/Systems/ImageSystem.h"
#include "../../Engine/Systems/TextSystem.h"
#include "../../InterSceneData.h"
#include "../../PlayerData.h"
#include "../../ResourceStatusData.h"
#include "../../CloseButton.h"
P_MP_SettlementUI::P_MP_SettlementUI(Object* parent)
	:GameObject(parent,"P_MP_SettlementUI"),
	fadeImageNum_(-1),
	time_(0),
	isClose_(false)
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
	
	//ポーションのデータから販売総額を計算
	for (PlayerData::PotionData& potionData : pData.potionDataList_)
	{
		if(potionData.isSale_)
		{
			
			totalGain += potionData.price_ * CalcSellCount(pData.newsPaperNumber_,potionData.topStatus_);
		}
	}
	//売り上げのデータを更新
	if(pData.gainList_.size()>=5)
	pData.gainList_.erase(pData.gainList_.begin());
	
	pData.gainList_.push_back(totalGain);
	pData.money_ += totalGain;
	//各データのUIを作成
	Instantiate<P_MP_SettlementUI_TotalGain>(this)->SetData(totalGain,"大盛況!");
	Instantiate<SettlementUI_EarningTransition>(this)->SetData(pData.gainList_);
	Instantiate<P_MP_SettlementUI_PotionList>(this)->CreateListUI(pData.potionDataList_);
	pData.newsPaperNumber_ = ++pData.newsPaperNumber_ % 4;
	

	//Instantiate<CloseButton>(this);

	Image okImage(this);
	okImage.Load("Assets/Image/ButtonImage01.png");
	okImage.SetPosition({ 0.8,-0.6,0 });
	okImage.SetLayer(2);
	okImageNum_ = AddComponent<Image>(okImage);

	XMFLOAT3 pos = okImage.GetPositionAtPixel();
	XMFLOAT3 size = okImage.GetSizeAtPixel();
	Text okText(this);
	okText.SetText("OK");
	okText.SetTextSize(90);
	okText.SetRect({ 0,0,size.x,size.y });
	okText.SetAlignmentType(ALIGNMENT_TYPE::CENTER_CENTER);
	okText.SetLayer(2);
	okText.SetPosition({ pos.x - size.x*0.5f,pos.y - size.y*0.5f });
	AddComponent<Text>(okText);

	Image fadeImage(this);
	fadeImage.Load("Assets/Image/PotionManagerUIBase1.png");
	fadeImage.SetSize({ 2,2,0 });
	fadeImage.SetLayer(2);
	fadeImage.SetColor(0);
	fadeImageNum_ = AddComponent<Image>(fadeImage);

	hAdio_OK_ = AudioManager::Load("Assets/Audio/Confirm29.wav");
}

void P_MP_SettlementUI::Start()
{
}

void P_MP_SettlementUI::Update()
{

	if(isClose_)
	{
		if (time_ <= 0.5f)
		{
			time_ += 0.016f;
			GetComponent<Image>(fadeImageNum_).SetAlpha( time_ / 0.5f);
			if (time_ >= 0.5f)
				KillMe();
		}
	}
	if (time_ <= 0.5f&& !isClose_)
	{
		time_ += 0.016f;
		GetComponent<Image>(fadeImageNum_).SetAlpha((0.5f - time_) / 0.5f);
	}

	if (GetComponent<Image>(okImageNum_).IsHitCursor() && Input::IsMouseButtonUp(0))
	{
		isClose_ = true;
		time_ = 0;
		AudioManager::Play(hAdio_OK_);
		//KillMe();
	}
}

void P_MP_SettlementUI::CreateResoultUI()
{

}

int P_MP_SettlementUI::CalcSellCount(int newsNum, int topStatus)
{
	ResourceStatusData::ResourceStatus rData = InterSceneData::GetData<ResourceStatusData>("ResourceData")->newsPaperList_[newsNum];
	int count = 5;
	//ポーションのステータスが需要のあるステータスと一致していたら販売数1.5倍
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
