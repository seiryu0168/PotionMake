#pragma once
#include"../../Engine/GameObject/GameObject.h"

/// <summary>
/// �|�[�V�����̃X�e�[�^�X��\������Q�[�W
/// </summary>
class PotionStatusGauge : public GameObject
{
public:
	PotionStatusGauge(Object* parent);
	~PotionStatusGauge();
	void Initialize() override;
	void Start() override;
	void Update() override;
	void Release() override;

};

