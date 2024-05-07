#include "PotionCraftAnimation.h"
#include "PotionCraftAnimationPot.h"
#include "../../Engine/Systems/ImageSystem.h"
PotionCraftAnimation::PotionCraftAnimation(Object* parent)
	:GameObject(parent,"PotionCraftAnimation")
{
}

PotionCraftAnimation::~PotionCraftAnimation()
{
}

void PotionCraftAnimation::Initialize()
{
	
}

void PotionCraftAnimation::Update()
{
}

void PotionCraftAnimation::InitAnimation(const std::vector<int> numList)
{
	//�|�[�V��������̃A�j���[�V����
	PotionCraftAnimationPot* paPot = Instantiate<PotionCraftAnimationPot>(this);
	paPot->InputResourceNumber(numList);
}

void PotionCraftAnimation::Release()
{
}
