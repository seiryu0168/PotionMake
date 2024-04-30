#pragma once
#include"../../Engine/GameObject/GameObject.h"

/// <summary>
/// �|�[�V��������̃A�j���[�V�����Ɏg�����
/// </summary>
class PotionCraftAnimationPot : public GameObject
{
	std::vector<int> imageNum_;
	std::vector<XMFLOAT2> posList_;
	float time_;
	int hAudio_Bubble_;
public:
	PotionCraftAnimationPot(Object* parent);
	~PotionCraftAnimationPot();

	void Initialize() override;
	void Start() override;
	void Update() override;
	void InputResourceNumber(const std::vector<int> numList);
	void Release() override;
};

