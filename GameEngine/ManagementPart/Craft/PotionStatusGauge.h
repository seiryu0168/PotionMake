#pragma once
#include "../../Engine/GameObject/GameObject.h"

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
	void SetGauge(const std::string& iconName, const XMFLOAT3 pos, const XMFLOAT3& color);
	void Release() override;

};

