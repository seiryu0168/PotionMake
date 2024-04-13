#pragma once
#include"../../Engine/GameObject/GameObject.h"

/// <summary>
/// �|�[�V��������̃A�j���[�V����
/// </summary>
class PotionCraftAnimation : public GameObject
{
public:
	PotionCraftAnimation(Object* parent);
	~PotionCraftAnimation();
	void Initialize() override;
	void Update() override;
	void InitAnimation(const std::vector<int> numList);
	void Release() override;
};

