#pragma once
#include"Engine/GameObject/GameObject.h"
/// <summary>
/// �|�[�V�����̍݌�UI
/// </summary>
class P_MP_PotionManagerUI_PotionStockUI : public GameObject
{
public:
	P_MP_PotionManagerUI_PotionStockUI(Object* parent);
	~P_MP_PotionManagerUI_PotionStockUI();
	void Initialize() override;
	void Start() override;
	void Update() override;
	void Release() override;

};

