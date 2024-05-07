#pragma once
#include "../../Engine/GameObject/GameObject.h"

/// <summary>
/// �I�񂾃|�[�V����������X���b�g
/// </summary>
class PotionSlot : public GameObject
{
	int potionNum_;
	int potionImageNum_;
public:
	PotionSlot(Object* parent);
	~PotionSlot();
	void Initialize() override;
	void Start() override;
	void Update() override;
	void SetPotion(int potionNum, const std::string& name, const XMFLOAT3& color);
	int GetPotionNumber() { return potionNum_; }
	void RemovePotion();
	void Release() override;
};

