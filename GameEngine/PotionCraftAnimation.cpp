#include "PotionCraftAnimation.h"
#include"Engine/Systems/ImageSystem.h"
#include"PotionCraftAnimationPot.h"
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
	PotionCraftAnimationPot* paPot = Instantiate<PotionCraftAnimationPot>(this);
	paPot->InputResourceNumber(numList);
}

void PotionCraftAnimation::Release()
{
}
