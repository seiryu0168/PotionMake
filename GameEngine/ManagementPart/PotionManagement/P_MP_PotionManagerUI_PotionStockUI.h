#pragma once
#include "../../Engine/GameObject/GameObject.h"
/// <summary>
/// �|�[�V�����̍݌�UI
/// </summary>
class P_MP_PotionManagerUI_PotionStockUI : public GameObject
{
	std::vector<GameObject* > potionList_;
	XMFLOAT3 uiPos_;
public:
	XMFLOAT2 potionImageBasePos_;
	P_MP_PotionManagerUI_PotionStockUI(Object* parent);
	~P_MP_PotionManagerUI_PotionStockUI();
	void Initialize() override;
	void Start() override;
	void Update() override;
	void InputPotionData();
	void CreateBase();
	void CreatePotionMenu(int potionNum, const std::string& name, const XMFLOAT3& color);
	void ConfirmPotionManagement();
	void SetEnablePotionStock(bool isEnable);
	void Release() override;

};

