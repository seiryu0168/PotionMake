#include "PotionCraftAnimationPot.h"
#include"../../Engine/Systems/ImageSystem.h"
#include"../../InterSceneData.h"
#include"../../ResourceStatusData.h"
#include"CraftSteam2D.h"
#include"FinishCraftUI.h"
PotionCraftAnimationPot::PotionCraftAnimationPot(Object* parent)
	:GameObject(parent,"PotionCraftAnimationPot"),
	time_(0)
{
}

PotionCraftAnimationPot::~PotionCraftAnimationPot()
{
}

void PotionCraftAnimationPot::Initialize()
{
	//��̉摜(��둤)
	Image potImage(this);
	potImage.Load("Assets/Image/PreparePot06.png");
	potImage.SetLayer(1);
	potImage.SetSize({ 2.3f,2.3f,0 });
	AddComponent<Image>(potImage);
	
	//��̉摜(�O��)
	Image potFrontImage(this);
	potFrontImage.Load("Assets/Image/CraftPot_Front.png");
	potFrontImage.SetSize({ 2.3f,2.3f,0 });
	potFrontImage.SetLayer(2);
	AddComponent<Image>(potFrontImage);

	//���C�I�u�W�F�N�g�̐���
	CraftSteam2D* smoke = Instantiate<CraftSteam2D>(this);
	smoke->SetSmokeParameter(3.0f, 0, 30, 0.1f, 0.6f, {-0.2f,0.2f});
	smoke->PlaySmoke();

}

void PotionCraftAnimationPot::Start()
{
}

void PotionCraftAnimationPot::Update()
{
	time_ += 0.016f;
	float diff = sinf(time_*4.0f) * 0.02f;
	if (diff < 0) diff *= -1;
	for (int i=0;i<imageNum_.size();i++)
	{
		GetComponent<Image>(imageNum_[i]).SetPosition({ posList_[i].x,posList_[i].y + diff,0 });
	}
	if (time_ >= 3.0f)
	{
		Instantiate<FinishCraftUI>(pParent_->GetParent());
		KillMe();
	}
}

void PotionCraftAnimationPot::InputResourceNumber(const std::vector<int> numList)
{
	ResourceStatusData* data = InterSceneData::GetData<ResourceStatusData>("ResourceData");
	XMFLOAT3 pos = { -0.1f,0.2f,0 };
	
	//�f�ޔԍ������Ƃɑf�ނ�\��
	for (int num : numList)
	{
		Image resourceImage(this);
		resourceImage.Load("Assets/Image/" + data->resourceDataMap_[num].resourceImageName_);
		resourceImage.SetPosition(pos);
		resourceImage.SetLayer(1);
		resourceImage.SetSize({ 0.25f,0.25f,0 });
		posList_.push_back({ pos.x,pos.y });
		imageNum_.push_back(AddComponent<Image>(resourceImage));
		pos.x += 0.1f;
	}

}

void PotionCraftAnimationPot::Release()
{
}
