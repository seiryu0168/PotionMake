#pragma once
#include"Engine/GameObject/GameObject.h"
/// <summary>
/// �|�[�V�����̊e�p�����[�^��\������N���X
/// </summary>
class P_MP_CraftUI_PotionStatusUI : public GameObject
{
private:
	XMFLOAT2 uiPos_;
public:
	P_MP_CraftUI_PotionStatusUI(Object* parent);
	~P_MP_CraftUI_PotionStatusUI();
	void Initialize() override;
	void Start() override;
	void Update() override;
	void Release() override;
};

