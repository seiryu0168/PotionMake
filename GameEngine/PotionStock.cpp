#include "PotionStock.h"

PotionStock::PotionStock(Object* parent)
	:GameObject(parent,"PotionStock")
{

}

PotionStock::~PotionStock()
{
}

void PotionStock::Initialize()
{
}

void PotionStock::Start()
{
}

void PotionStock::Update()
{
}

void PotionStock::SetPotionStatus_(int potionNum, std::string name, int sts0, int sts1, int sts2, int sts3, int sts4)
{
	potionNum_ = potionNum;
	potionName_ = name;
	potionStatus_.push_back(sts0);
	potionStatus_.push_back(sts1);
	potionStatus_.push_back(sts2);
	potionStatus_.push_back(sts3);
	potionStatus_.push_back(sts4);
}

void PotionStock::Release()
{
}
