#pragma once
#include"Engine/GameObject/GameObject.h"
class PotionCraftAnimationPot : public GameObject
{
	std::vector<int> imageNum_;
	float time_;
public:
	PotionCraftAnimationPot(Object* parent);
	~PotionCraftAnimationPot();

	void Initialize() override;
	void Start() override;
	void Update() override;
	void InputResourceNumber(const std::vector<int> numList);
	void Release() override;
};

