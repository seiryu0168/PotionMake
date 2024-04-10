#include "PotionCraftAnimationPot.h"
#include"Engine/Systems/ImageSystem.h"
#include"InterSceneData.h"
#include"ResourceStatusData.h"
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
	Image potImage(this);
	potImage.Load("Assets/Image/PreparePot06.png");
	AddComponent<Image>(potImage);
}

void PotionCraftAnimationPot::Start()
{
}

void PotionCraftAnimationPot::Update()
{
	time_ += 0.016f;
	if (time_ >= 3.0f)
	{
		pParent_->GetParent()->KillMe();
	}
}

void PotionCraftAnimationPot::InputResourceNumber(const std::vector<int> numList)
{
	ResourceStatusData* data = InterSceneData::GetData<ResourceStatusData>("ResourceData");
	XMFLOAT3 pos = { -0.1f,0.2f,0 };
	for (int num : numList)
	{
		Image resourceImage(this);
		resourceImage.Load("Assets/Image/" + data->resourceDataMap_[num].resourceImageName_);
		resourceImage.SetPosition(pos);
		resourceImage.SetSize({ 0.25f,0.25f,0 });
		AddComponent<Image>(resourceImage);
		pos.x += 0.1f;
	}

}

void PotionCraftAnimationPot::Release()
{
}
