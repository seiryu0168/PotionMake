#pragma once
#include"Engine/GameObject/GameObject.h"
class PotionSlot : public GameObject
{
	int potionNum_;
public:
	PotionSlot(Object* parent);
	~PotionSlot();
	void Initialize() override;
	void Update() override;
	void Release() override;
};

